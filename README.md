# Advanced Vector Extensions (AVX) basic


Advanced Vector Extensions (AVX) are extensions to the x86 instruction set architecture for microprocessors for SIMD technology. This tutorial shows how to use the AVX instructions from the instructions from the C code prespective

The code include examples for: 
  * SSE technology
  * AVX2 technology
  * AVX-512 technology

## How to build these examples

``` make ```

## How to build these static

Create static binary which runs across multiple distros

``` make static```

## How to clean

``` make clean```

## How to assign a cpu to run an example : 

``` ./add & taskset -cp 0 <PID> ```

## How to run all examples in all CPUs available:

``` ./run-all.sh ```

If you want to kill all the processes running in the system, you can use: 

``` pkill -f build/<file> ```

instead of kill -9 <PID>
