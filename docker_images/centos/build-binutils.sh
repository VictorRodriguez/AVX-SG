#!/bin/bash

FOLDER="binutils-gdb"
URL="https://sourceware.org/git/binutils-gdb.git"

if [ ! -d "$FOLDER" ] ; then
    git clone --depth 1 $URL $FOLDER
fi

# create the build directory
cd binutils-gdb/
mkdir build/
cd build

# build
../configure --prefix=/usr       \
             --enable-gold       \
             --enable-ld=default \
             --enable-plugins    \
             --enable-shared     \
             --disable-werror    \
             --enable-64-bit-bfd \
             --with-system-zlib  \
&& make tooldir=/usr -j		 \
&& make tooldir=/usr install

