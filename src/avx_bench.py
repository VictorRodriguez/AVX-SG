#!/usr/bin/python
from __future__ import absolute_import
import argparse
import os
import sys
from io import open


supported_funtions = []
supported_funtions.append(u"add")
supported_archs = []
supported_archs.append(u"sse")
supported_archs.append(u"haswell")
supported_archs.append(u"skylake-avx512")
supported_archs.append(u"icelake-server")

def print_help():
    print
    
    print u"Supported functions:"
    print supported_funtions
    print

    print u"Supported archs:"
    print supported_archs
    print

def gen_foo(function,complexity):
    f = open(u'foo.h',u'w')
    if function == u"add":
        instr = u"+"
    else:
        instr = u"+"

    if complexity == 5:
        f.write(u"extern float a[256];\n")
        f.write(u"extern float b[256];\n")
        f.write(u"extern float c[256];\n")
        f.write(u"extern void foo(){\n")
        f.write(u"    for (int i=0; i<256; i++){\n")
        f.write(u"        a[i] = b[i] "+ instr + u" c[i];\n")
        f.write(u"    }\n")
        f.write(u"}\n")
    if complexity == 10:
        f.write(u"extern float a[256];\n")
        f.write(u"extern float b[256];\n")
        f.write(u"extern float c[256];\n")
        f.write(u"extern float d[256];\n")
        f.write(u"extern void foo(){\n")
        f.write(u"    for (int i=0; i<256; i++){\n")
        f.write(u"        a[i] = b[i] "+ instr + u" c[i];\n")
        f.write(u"        d[i] = a[i] "+ instr + u" c[i];\n")
        f.write(u"        d[i] = b[i] "+ instr + u" c[i];\n")
        f.write(u"        d[i] = c[i] "+ instr + u" c[i];\n")
        f.write(u"        d[i] = d[i] "+ instr + u" c[i];\n")
        f.write(u"    }\n")
        f.write(u"}\n")

def main():
    cmd = u""
    function = u"add"
    arch = u"haswell"
    loops = 1000000
    delay = 0
    complexity = 5

    parser = argparse.ArgumentParser()
    parser.add_argument(u"-f", u"--function", \
            help=u"Aritmetic function to stress",dest=u'function')
    parser.add_argument(u"-b", u"--build", \
            help=u"build benchmark",action=u'store_true')
    parser.add_argument(u"-a", u"--architecture", \
            help=u"Architecture (haswell/skylake/icelake",dest=u'arch')
    parser.add_argument(u"-l", u"--loops", \
            help=u"# loops to repeat the workload",dest=u'loops')
    parser.add_argument(u"-d", u"--delay", \
            help=u"delay between workload ( in useconds)",dest=u'delay')
    parser.add_argument(u"-c", u"--complexity", \
            help=u"Complexity of benchmark ( how \
            much you want to stress the CPU) ",dest=u'complexity')
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
        cmd = u"make"
        os.system(cmd)

    if (os.path.isfile(u"add-march-sse")):
        cmd = u"./"
    elif (os.path.isfile(u"src/add-march-sse")):
        cmd = u"src/"
    else:
        print u"No binaries to run"
        print u"Please run make"
        sys.exit(-1)

    cmd = cmd + function + u"-" + u"march" + u"-" + arch + u" -l " + unicode(loops) \
            + u" -d " + unicode(delay)
    print u"CMD = " + cmd

    # if you want to run a script of binary before the bench 
    # cmd = "./binary"
    # os.system(cmd)

    os.system(cmd)
if __name__ == u"__main__":
    main()
