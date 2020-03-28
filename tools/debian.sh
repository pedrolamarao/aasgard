#!/bin/sh

echo Installing Debian tools...

apt install --no-install-recommends \
 bison bzip2 \
 clang-8 cmake \
 file flex \
 libexpat1-dev libfreetype6-dev libglib2.0-dev libpixman-1-dev lld-8 \
 make \
 openjdk-11-jdk-headless \
 pkg-config python \
 texinfo \
 unifont \
 wget \
 xz-utils
if [ $? -ne 0 ]; then exit $?; fi

echo Installing Debian alternatives...

update-alternatives \
 --install /usr/bin/clang   clang   /usr/bin/clang-8    10 \
 --slave   /usr/bin/clang++ clang++ /usr/bin/clang++-8     \
 --slave   /usr/bin/lld     lld     /usr/bin/lld-8
if [ $? -ne 0 ]; then exit $?; fi
