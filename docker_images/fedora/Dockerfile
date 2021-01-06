FROM    fedora:latest
MAINTAINER  Victor Rodriguez

RUN INSTALL_PKGS="git gcc gcc-c++ gcc-gfortran gdb make" && \
    dnf install -y --setopt=tsflags=nodocs $INSTALL_PKGS && \
    rpm -V $INSTALL_PKGS && \
    dnf clean all -y && \
    git clone --depth=1 https://github.com/VictorRodriguez/avx-basics.git
