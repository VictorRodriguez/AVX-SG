#!/bin/bash

set -e

INSTALLDIR=$(pwd)"/install-dir"
mkdir -p $INSTALLDIR

FOLDER="gcc"
URL="https://gitlab.com/x86-gcc/gcc/-/archive/master/gcc-master.tar.gz"

if [ ! -d "$FOLDER" ] ; then
    wget $URL
	tar -xvf gcc-master.tar.gz
	mv gcc-master $FOLDER
fi


# download the prerequisites
cd gcc/
#patch -p1 < ../amx-runtime.patch
./contrib/download_prerequisites

# create the build directory
cd ..
mkdir gcc-build
cd gcc-build

# build
../gcc/configure			\
    --prefix=${INSTALLDIR}		\
    --enable-shared			\
    --with-system-zlib			\
    --enable-threads=posix		\
    --enable-__cxa_atexit		\
    --enable-clocale=gnu		\
    --disable-multilib			\
    --disable-multiarch			\
    --enable-languages="c"		\
&& make -j				\
&& make install

# Notes
#
#   --enable-shared --enable-threads=posix --enable-__cxa_atexit:
#       These parameters are required to build the C++ libraries to published standards.
#
#   --enable-clocale=gnu:
#       This parameter is a failsafe for incomplete locale data.
#
#   --disable-multilib:
#       This parameter ensures that files are created for the specific
#       architecture of your computer.
#        This will disable building 32-bit support on 64-bit systems where the
#        32 bit version of libc is not installed and you do not want to go
#        through the trouble of building it. Diagnosis: "Compiler build fails
#        with fatal error: gnu/stubs-32.h: No such file or directory"
#
#   --with-system-zlib:
#       Uses the system zlib instead of the bundled one. zlib is used for
#       compressing and uncompressing GCC's intermediate language in LTO (Link
#       Time Optimization) object files.
#
#   --enable-languages=all
#   --enable-languages=c,c++,fortran,go,objc,obj-c++:
#       This command identifies which languages to build. You may modify this
#       command to remove undesired language
