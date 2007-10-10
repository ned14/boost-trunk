
This directory contains experimental port of Boost.Build V2 to Python.
The explanations why this is needed, and some guidelines can be found
in the doc/Overview.txt file. Unless you're interested in working on that
port, you probably should not read this document.

To try the port, you need this:

1. Get yourself a fresh version of bjam. In the build.jam file,
   find the
  
       HAVE_PYTHON = 0 ;

   line and change it to

       HAVE_PYTHON = 1 ;

   You might want to edit Python location too. Rebuild bjam with

       ./build.sh --debug

       (The '--debug' option is required, bjam will crash without it)

   and place the binary in PATH (don't forget that debug binary is built
   to a different directory.

2. Get yourself up-to-date version of Python port:

       cvs up -r BOOST_BUILD_PYTHON python

3. Get top-level module for Python port:

       cvs up -r BOOST_BUILD_PYTHON pybb.jam

4. Go to python/tests/bjam/make and run

       bjam --build-system=pybb


     