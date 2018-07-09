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

def gen_foo(function,complexity):
    f = open('foo.h','w')
    if function == "add":
        instr = "+"
    else:
        instr = "+"

    if complexity == 5:
        f.write("extern float a[256];\n")
        f.write("extern float b[256];\n")
        f.write("extern float c[256];\n")
        f.write("extern void foo(){\n")
        f.write("    for (int i=0; i<256; i++){\n")
        f.write("        a[i] = b[i] "+ instr + " c[i];\n")
        f.write("    }\n")
        f.write("}\n")
    if complexity == 10:
        f.write("extern float a[256];\n")
        f.write("extern float b[256];\n")
        f.write("extern float c[256];\n")
        f.write("extern float d[256];\n")
        f.write("extern void foo(){\n")
        f.write("    for (int i=0; i<256; i++){\n")
        f.write("        a[i] = b[i] "+ instr + " c[i];\n")
        f.write("        d[i] = a[i] "+ instr + " c[i];\n")
        f.write("        d[i] = b[i] "+ instr + " c[i];\n")
        f.write("        d[i] = c[i] "+ instr + " c[i];\n")
        f.write("        d[i] = d[i] "+ instr + " c[i];\n")
        f.write("    }\n")
        f.write("}\n")

def main():
    cmd = ""
    function = "add"
    arch = "haswell"
    loops = 1000000
    delay = 0
    complexity = 5

    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--function", \
            help="Aritmetic function to stress",dest='function')
    parser.add_argument("-b", "--build", \
            help="build benchmark",action='store_true')
    parser.add_argument("-a", "--architecture", \
            help="Architecture (haswell/skylake/icelake",dest='arch')
    parser.add_argument("-l", "--loops", \
            help="# loops to repeat the workload",dest='loops')
    parser.add_argument("-d", "--delay", \
            help="delay between workload ( in useconds)",dest='delay')
    parser.add_argument("-c", "--complexity", \
            help="Complexity of benchmark ( how \
            much you want to stress the CPU) ",dest='complexity')
    args = parser.parse_args()

    if args.function:
        if args.function in supported_funtions:
            function = args.function
        else:
            print_help()
            sys.exit(-1)
    if args.arch:
        if args.arch in supported_archs:
            arch = args.arch
        else:
            print_help()
            sys.exit(-1)
    if args.loops:
        loops=args.loops
    if args.delay:
        delay=args.delay
    if args.complexity and args.build:
        complexity = int(args.complexity)
        gen_foo(function,complexity)
        cmd = "make"
        os.system(cmd)

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

    # if you want to run a script of binary before the bench 
    # cmd = "./binary"
    # os.system(cmd)

    os.system(cmd)
if __name__ == "__main__":
    main()
