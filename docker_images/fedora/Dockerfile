FROM    fedora:latest
MAINTAINER  Victor Rodriguez

ENV http_proxy addr:port
ENV https_proxy addr:port

RUN INSTALL_PKGS="gcc gcc-c++ gcc-gfortran gdb make" && \
    dnf install -y --setopt=tsflags=nodocs $INSTALL_PKGS && \
    rpm -V $INSTALL_PKGS && \
    dnf clean all -y
