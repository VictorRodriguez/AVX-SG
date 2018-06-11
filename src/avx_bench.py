#!/usr/bin/python3
import argparse
import os
import sys


supported_funtions = []
supported_funtions.append("add")
supported_archs = []
supported_archs.append("sse")
supported_archs.append("haswell")
supported_archs.append("skylake-avx512")
supported_archs.append("icelake-server")

def print_help():
    print()
    
    print("Supported functions:")
    print(supported_funtions)
    print()

    print("Supported archs:")
    print(supported_archs)
    print()

def main():
    cmd = ""
    function = "add"
    arch = "haswell"
    loops = 1000000
    delay = 0

    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--function", \
            help="Aritmetic function to stress",dest='function')
    parser.add_argument("-a", "--architecture", \
            help="Architecture (haswell/skylake/icelake",dest='arch')
    parser.add_argument("-l", "--loops", \
            help="# loops to repeat the workload",dest='loops')
    parser.add_argument("-d", "--delay", \
            help="delay between workload ( in useconds)",dest='delay')
    args = parser.parse_args()

    if args.function:
        if args.function in supported_funtions:
            function = args.function
        else:
            print("1")
            print_help()
            sys.exit(-1)
    if args.arch:
        if args.arch in supported_archs:
            arch = args.arch
        else:
            print("2")
            print_help()
            sys.exit(-1)
    if args.loops:
        loops=args.loops
    if args.delay:
        delay=args.delay

    if (os.path.isfile("add-march-sse")):
        cmd = "./"
    elif (os.path.isfile("src/add-march-sse")):
        cmd = "src/"
    else:
        print("No binaries to run")
        print("Please run make")
        sys.exit(-1)

    cmd = cmd + function + "-" + "march" + "-" + arch + " -l " + str(loops) \
            + " -d " + str(delay)
    print("CMD = " + cmd)

    os.system(cmd)
if __name__ == "__main__":
    main()
