FROM ubuntu:22.04

WORKDIR /workspace

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        libopenmpi-dev \
        openmpi-bin \
        libgtest-dev \
        git \
        && apt-get clean \
        && cd /usr/src/gtest && cmake . && make && cp lib/*.a /usr/lib

COPY . .