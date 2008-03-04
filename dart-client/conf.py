#
#  Copyright (C) 2007 Troy Straszheim <troy@resophonic.com>
#
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#    http://www.boost.org/LICENSE_1_0.txt
#
#
#
#  Name of local directory that will contain build output
#
prefix = 'work'

#
#  Wait 1 minute between builds
#  Each build will trigger an svn update.  Go easy on the repository.   
#
interbuild_sleep = 60

#
#  Association source_tag => url of things to build/test.  The tags will be used as
#  local directory names.
#
boost_svn = 'http://svn.boost.org/svn/boost/sandbox-branches/boost-cmake/boost_1_34_0'
test_svn = 'http://svn.resophonic.com/pub/ctest-tiny'
urls = { 'boost_1_34_0' : boost_svn }

#
#  Variants to build/test:  map of boost_variant_tag => [cmake_arguments]
#  The boost_variant_tag will be used a as local directory name.
#
all_args = ['-DBUILD_TESTING:BOOL=ON']
build_variants = {
    'debug'  : all_args + ['-DBUILD_RELEASE:BOOL=OFF', '-DBUILD_DEBUG:BOOL=ON'],
    'release': all_args + ['-DBUILD_RELEASE:BOOL=ON', '-DBUILD_DEBUG:BOOL=OFF']
}

#
# calculates delta-time for nightly builds.  if last build happened
# today, return a negative delta
#
def nightly_dt(t):
    current_time = datetime.now()
    if current_time.date() > t.date():
        return current_time - t
    else: 
        return timedelta(0)

#
# For testing, return dt if t didn't happen this minute.
#
def minutely_dt(t):
    current_time = datetime.now()
    if current_time.replace(microsecond=0, second=0) > t:
        return current_time - t
    else:
        return timedelta(0)

#
# Straight delta-time for continuous builds 
#
def continuous_dt(t):
    current_time = datetime.now()
    return current_time - t

#
# Association of ctest variants to build: ctest_variant_tag => ([ctest_args], delta_fn)
#
# Where delta_fn returns the amount of time between now and its
# argument.  The build with the longest delta_t will be built next.
# This allows Nightly or weekly builds to return a negative delta
# (and therefore will not be built) when the actual dt is less than some
# threshold.
#
# Each ctest_variant_tag will be used as a local directory name.
#
ctest_variants = { 
    'continuous' : (['-D', 'Continuous'], continuous_dt),
    'nightly' : (['-D', 'Nightly'], nightly_dt)
    }

#
# You may need to customize these for your platform.  These are
# typical settings on unix.  
#
ctest = "ctest"  # path to ctest binary
cmake = "cmake"  # path to cmake binary
svn   = "svn"    # path to svn 

#
# Typical settings on windows:
#
# The escaped doublequotes around the name of the executables are necessary.
#
# cmake = "\"C:\\Program Files\???\cmake.exe\""
# ctest = "\"C:\\Program Files\???\ctest.exe\""
#
   
