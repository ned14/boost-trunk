#!/bin/bash

# This script create a nightly tarball of Boost.Build V2
# and updates the web site.

# Create the packages
cd /tmp
rm -rf boost-build
cvs -d :ext:vladimir_prus@cvs.sourceforge.net:/cvsroot/boost co -P -d  boost-build boost/tools/build
cd boost-build/v2
./roll.sh
cd ..
scp boost-build.zip boost-build.tar.bz2 vladimir_prus@shell.sf.net:/home/groups/b/bo/boost/htdocs/boost-build2
