#
# Copyright (C) 2005 The Trustees of Indiana University 
# Author: Douglas Gregor
#
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
import re
import smtplib
import os
import time
import string
import datetime
import sys

# Retrieve the issues email from MetaComm, trying a few times in case
# something wonky is happening.
# Returns the list of failing libraries
def get_issues_email():
    got_issues = False
    print 'Retrieving issues email...'
    for x in range(30):
        if not ('--no-get' in sys.argv):
            # Update issues-email.txt
            os.system('curl -O http://engineering.meta-comm.com/boost-regression/CVS-HEAD/developer/issues-email.txt')

        # Determine the set of libraries that have unresolved failures
        failing_libraries = {}
        library_regex = re.compile('\|(.*)\|')
            
        for line in file('issues-email.txt', 'r'):
            if line.count('Report time') > 0:
                got_issues = True
                
            m = library_regex.match(line)
            if m:
                failing_libraries[m.group(1)] = ""
                
        if got_issues:
            break

        time.sleep (30)

    return failing_libraries
   
# Parses the file $BOOST_ROOT/libs/maintainers.txt to create a hash
# mapping from the library name to the list of maintainers.
def get_library_maintainers():
  maintainers = {}
  lib_maintainer_regex = re.compile('(\S+)\s*(.*)')
  name_email_regex = re.compile('\s*(\w*(\s*\w+)+)\s*<\s*(\S*(\s*\S+)+)\S*>')
  at_regex = re.compile('\s*-\s*at\s*-\s*')
  for line in file('../../../libs/maintainers.txt', 'r'):
      m = lib_maintainer_regex.match (line)
      if m:
         lib = m.group(1)
         maintainers[lib] = list()
         for person in re.split('\s*,\s*', m.group(2)):
             nmm = name_email_regex.match(person)
             if nmm:
                name = nmm.group(1)
                email = nmm.group(3)
                email = at_regex.sub('@', email)
                maintainers[lib].append((name, email))  
  return maintainers

# Send a message to "person" (a maintainer of a library that is
# failing).
# maintainers is the result of get_library_maintainers()
def send_individualized_message (person, maintainers):

  print ('Message for ' + person[0] + ' <' + person[1] + '>' + ' contains:')
    
  # Build the message header
  message = """From: Douglas Gregor <dgregor@cs.indiana.edu>
To: """
  message += person[0] + ' <' + person[1] + '>'
  message += """
Reply-To: boost@lists.boost.org
Subject: Regressions in your Boost libraries as of """
  message += str(datetime.date.today())
  message += """

You are receiving this report because one or more of the libraries you
maintain has regression test failures that are not accounted for.
A full version of the report is sent to the Boost developer's mailing
list.

Detailed report:
"""
  # There are several states we could be in:
  #   0 Initial state. Eat everything up to the "NNN failures in MMM
  #     libraries" line
  #   1 Suppress output within this library
  #   2 Forward output within this library
  state = 0
 
  failures_in_lib_regex = re.compile('\d+ failur.*\d+ librar')
  lib_failures_regex = re.compile('  (\S+) \((\d+)\)')
  lib_start_regex = re.compile('\|(\S+)\|')
  general_pass_regex = re.compile('  http://')
  for line in file('issues-email.txt', 'r'):
    if state == 0:
        lfm = lib_failures_regex.match(line)
        if lfm:
            # Pass the line through if the current person is a
            # maintainer of this library
            if person in maintainers[lfm.group(1)]:
                message += line
                print line,
                
        elif failures_in_lib_regex.match(line):
            message += "\nThere are failures in these libraries you maintain:\n"
        elif general_pass_regex.match(line):
            message += line
            
    lib_start = lib_start_regex.match(line)
    if lib_start:
        if state == 0:
            message += '\n'
            
        if person in maintainers[lib_start.group(1)]:
            message += line
            state = 2
        else:
            state = 1
    else:
        if state == 1:
            pass
        elif state == 2:
            message += line

  if '--debug' in sys.argv:
      print '-----------------Message text----------------'
      print message
  else:
      print
      
  if '--send' in sys.argv:
      print "Sending..."
      smtp = smtplib.SMTP('milliways.osl.iu.edu')
      smtp.sendmail(from_addr = 'Douglas Gregor <dgregor@cs.indiana.edu>',
                    to_addrs = person[1],
                    msg = message)
      print "Done."


# Send a message to the developer's list
def send_boost_developers_message(maintainers, failing_libraries):
  to_line = 'boost@lists.boost.org'
  from_line = 'Douglas Gregor <dgregor@cs.indiana.edu>'

  message = """From: Douglas Gregor <dgregor@cs.indiana.edu>
To: boost@lists.boost.org
Reply-To: boost@lists.boost.org
Subject: Boost regression notification ("""

  message += str(datetime.date.today())
  message += ")"

  message += """

"""

  for line in file('issues-email.txt', 'r'):
      # Right before the detailed report, put out a warning message if
      # any libraries with failures to not have maintainers listed.
      if line.startswith('Detailed report:'):
          missing_maintainers = False
          for lib in failing_libraries:
              if maintainers[lib] == list():
                  missing_maintainers = True

          if missing_maintainers:
              message += """WARNING: The following libraries have failing regression tests but do
not have a maintainer on file. Once a maintainer is found, add an
entry to libs/maintainers.txt to eliminate this message.
"""

              for lib in failing_libraries:
                  if maintainers[lib] == list():
                      message += '  ' + lib + '\n'
              message += '\n'
              
      message += line
      
  if '--send' in sys.argv:
      print 'Sending notification email...'
      smtp = smtplib.SMTP('milliways.osl.iu.edu')
      smtp.sendmail(from_addr = from_line, to_addrs = to_line, msg = message)
      print 'Done.'

  if '--debug' in sys.argv:
      print "----------Boost developer's message text----------"
      print message

###############################################################################
# Main program                                                                #
###############################################################################

maintainers = get_library_maintainers()
failing_libraries = get_issues_email()

# Compute the set of maintainers that should receive notification        
cc_list = {}
for lib in failing_libraries:
    for maintainer in maintainers[lib]:
           cc_list[maintainer] = {}

# Send out individualized e-mail for each maintainer
for maintainer in cc_list:
  send_individualized_message(maintainer, maintainers)

send_boost_developers_message(maintainers, failing_libraries)

if not ('--send' in sys.argv):
    print 'Chickening out and not sending any e-mail.'
    print 'Use --send to actually send e-mail.'
