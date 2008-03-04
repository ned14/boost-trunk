# Simple Python script that acts as a bridge to any other Python
# script. It first sets sys.path to the first argument, then runs the
# script specified by the second argument. All remaining arguments are
# passed to the script.
import sys
sys.argv[0] = sys.argv[2]
sys.path.insert(0, sys.argv[1])
script_file = open(sys.argv[2], "r")
sys.argv.pop(1)
sys.argv.pop(1)
exec(script_file)
