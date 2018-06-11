# AVX benchmark


AVX benchmkar stress Advanced Vector Extensions instructions in x86\_64 CPUs

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes. See deployment for notes on
how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them:

* C compiler ( GCC if possible ) that suport upt to icelake flags
* Linux/Unix system


### Building

A step by step series of examples that tell you how to get a development env
running


```
    make
```


```
    make clean
```

## Running the tests


To run full benchmark:

```
    ./avx_bench
```

Help : 

```
 ./avx_bench -h
usage: avx_bench [-h] [-f FUNCTION] [-a ARCH] [-l LOOPS] [-d DELAY]

optional arguments:
  -h, --help            show this help message and exit
  -f FUNCTION, --function FUNCTION
                        Aritmetic function to stress
  -a ARCH, --architecture ARCH
                        Architecture (haswell/skylake/icelake
  -l LOOPS, --loops LOOPS
                        # loops to repeat the workload
  -d DELAY, --delay DELAY
                        delay between workload ( in useconds)
 
```

Examples: 

```
    ./avx_bench -f add -l 1000000000
    ./avx_bench -f add -l 1000 -d 10000
```

## Contributing

Please read
[CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for
details on our code of conduct, and the process for submitting pull requests to
us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available,
see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Victor Rodriguez** 

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

