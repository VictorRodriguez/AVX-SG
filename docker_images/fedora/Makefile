IMAGE_NAME ?= "fedora-gcc:latest"
TMP_MOUNT ?= /tmp/results

build:
	docker build -t $(IMAGE_NAME) .
run:
	docker run -v $(TMP_MOUNT):/results -it $(IMAGE_NAME) /bin/bash

