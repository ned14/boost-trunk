#!/usr/bin/python

# Copyright 2003 Dave Abrahams 
# Copyright 2003 Vladimir Prus 
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt) 

from BoostBuild import Tester, List
t = Tester()

# Test that top-level project can affect build dir
t.write("project-root.jam", "")
t.write("Jamfile", """

exe a : a.cpp ;
exe b : b.cpp ;
exe c : c.cpp ;

alias bin1 : a ;
alias bin2 : a b ;

alias src : s.cpp ;
exe hello : hello.cpp src ;

""")
t.write("a.cpp", "int main() { return 0; }\n")
t.copy("a.cpp", "b.cpp")
t.copy("a.cpp", "c.cpp")
t.copy("a.cpp", "hello.cpp")
t.write("s.cpp", "")

# Check that targets to which "bin1" refers are updated,
# and only those.
t.run_build_system("bin1")
t.ignore("*.tds")
t.expect_addition(List("bin/$toolset/debug/") * "a.exe a.obj")
t.expect_nothing_more()

# Try again with "bin2"
t.run_build_system("bin2")
t.ignore("*.tds")
t.expect_addition(List("bin/$toolset/debug/") * "b.exe b.obj")
t.expect_nothing_more()

# Try building everything, making sure 'hello' target is
# created
t.run_build_system()
t.ignore("*.tds")
t.expect_addition("bin/$toolset/debug/hello.exe")

# Regression test.
# Check if usage requirements are propagated via "alias"
           
t.write("l.cpp", """ 
void
#if defined(_WIN32)
__declspec(dllexport)
#endif
foo() {}

""")

t.write("Jamfile", """ 
lib l : l.cpp : : : <define>WANT_MAIN ;
alias la : l ;
exe main : main.cpp la ; 
""")

t.write("main.cpp", """ 
#ifdef WANT_MAIN
int main() { return 0; }
#endif

""")

t.write("project-root.jam", "")

t.run_build_system()

t.cleanup()
