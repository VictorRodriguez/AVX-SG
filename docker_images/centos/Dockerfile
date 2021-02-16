FROM centos:latest AS builder

RUN yum install wget gcc zlib-devel  autogen-libopts -y
RUN dnf install langpacks-en glibc-all-langpacks -y
RUN yum install dnf-plugins-core -y && yum config-manager --set-enabled powertools
RUN dnf install texinfo -y
RUN wget http://mirror.centos.org/centos/7/os/x86_64/Packages/autogen-5.18-5.el7.x86_64.rpm
RUN rpm -ivh autogen-5.18-5.el7.x86_64.rpm --nodeps
RUN yum group install "Development Tools" -y
COPY build-gcc.sh /
COPY build-binutils.sh /
RUN ./build-gcc.sh
RUN yum install gmp-devel -y
RUN ./build-binutils.sh

FROM centos:latest
RUN yum install git -y
RUN mkdir -p /install-dir
COPY --from=builder /usr/ /usr/
COPY --from=builder /install-dir /install-dir

COPY build-src.sh /
CMD ./build-src.sh
