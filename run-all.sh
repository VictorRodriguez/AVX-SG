#!/bin/bash

avx2_flag=false
avx512_flag=false

run_basic(){
for file in $patern
do
    echo
    ./$file 
    RET=$?
    if [ $RET -ne 0 ]
    then
        echo BASIC TEST $file FAIL
        exit -1
    else
        echo BASIC TEST $file PASS
    fi
done
}

run_benchmark(){
CPUs=$(($(grep -c ^processor /proc/cpuinfo)-1))
for file in $patern
do
    echo
    echo Running $file in $CPUs CPUs
    for cpu in $(seq 0 $CPUs)
    do 
        #use this line if you want to modify loops and delay
        #./$file -l 1000000 -d 1000 &
        # if you want default use this one
        ./$file &
        PID=$!
        echo PID = $PID , CPU = $cpu
        taskset -cp $cpu $!
    done
    wait $PID
done
}

#Check that platform support benchmarks

grep avx2 /proc/cpuinfo &> /dev/null
RET=$?
if [ $RET -eq 0 ]
then
    patern=build/basic_add_avx2
    run_basic
    avx2_flag=true
fi

grep avx512 /proc/cpuinfo &> /dev/null
RET=$?
if [ $RET -eq 0 ]
then
    patern=build/basic_add_avx512
    run_basic
    avx512_flag=true
fi


if $avx2_flag ; then
    patern=build/stress_add_avx2
    run_benchmark
fi

if $avx512_flag ; then
    patern=build/stress_add_avx512
    run_benchmark
fi
