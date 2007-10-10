# Status: being written afresh by Vladimir Prus

# Copyright 2007 Vladimir Prus 
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt) 

# This file is supposed to implement error reporting for Boost.Build.
# Experience with jam version has shown that printing full backtrace
# on each error is buffling. Further, for errors printed after parsing --
# during target building, the stacktrace does not even mention what
# target is being built.

# This module implements explicit contexts -- where other code can
# communicate which projects/targets are being built, and error
# messages will show those contexts. For programming errors,
# Python assertions are to be used.

class Errors:

    def __call__(self, message):
        # FIXME: add 'error' to each line.
        raise Exception(message)
