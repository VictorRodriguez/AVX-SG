FROM gcc:11.1.0 AS builder
RUN mkdir /devel
ADD ./src /devel/src
ADD ./Makefile /devel
ADD ./run-all.sh /devel
RUN cd /devel && make

FROM centos:latest
COPY --from=builder /devel/build /devel/build/
CMD cd /devel/build && ./run-tests.sh
