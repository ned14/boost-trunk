#!/usr/bin/python

# Test staging

from BoostBuild import Tester
t = Tester()

t.write("project-root.jam", "import gcc ;")

t.write(
    "Jamfile", 
"""
lib a : a.cpp ;
stage dist : a a.h auxilliary/1 ;
""")

t.write(
    "a.cpp",
"""
int
#ifdef _WIN32
__declspec(dllexport)
#endif
must_export_something;
""")

t.write("a.h", "")
t.write("auxilliary/1", "")

t.run_build_system()
t.expect_addition(["dist/a.dll", "dist/a.h", "dist/1"])

# Test the <location> property
t.write("Jamfile", """
lib a : a.cpp ;
stage dist : a 
    : <variant>debug:<location>ds <variant>release:<location>rs
    ;
""")

t.run_build_system()
t.expect_addition("ds/a.dll")

t.run_build_system("release")
t.expect_addition("rs/a.dll")

# Test the <location> property in subprojects. 
# Thanks to Kirill Lapshin for bug report.

t.write("project-root.jam", """
path-constant DIST : dist ;
""")

t.write("Jamfile", "build-project d ;")

t.write(
    "d/Jamfile",
"""
exe a : a.cpp ;
stage dist : a : <location>$(DIST) ;
""")

t.write("d/a.cpp", "int main() { return 0;}\n")

t.run_build_system()
t.expect_addition("dist/a.exe")

t.rm("dist")
t.run_build_system(subdir="d")
t.expect_addition("dist/a.exe")


t.cleanup()
