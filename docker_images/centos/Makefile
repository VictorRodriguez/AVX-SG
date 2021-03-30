all:
	docker build . -t gcc_amx
run:
	docker run -v $(PWD)/build-binaries/:/build-binaries/ gcc_amx:latest
run-local:
	docker run  -v /home/centos/devel/AVX-SG/:/src -v $(PWD)/build-binaries/:/build-binaries/ marceline.zpn.intel.com/gcc_amx:v0.1
