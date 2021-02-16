#!/bin/bash

if [ -d "/src" ]
then
    echo "Directory /src exists."
else
    echo "Error: Directory /src does not exists."
	REPO=https://github.com/VictorRodriguez/AVX-SG.git
	git clone $REPO src/
fi

cd /src/ && make && make clean && make amx
cp -rf /src/build/* /build-binaries/

