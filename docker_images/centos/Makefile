all:
	docker build . -t gcc_amx
run:
	docker run -v $(PWD)/build-binaries/:/build-binaries/ gcc_amx:latest
