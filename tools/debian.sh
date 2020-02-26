#!/bin/sh

# source
apt-get install  bzip2 wget xz-utils
if [ $? -ne 0 ]; then exit $?; fi

# build
apt-get install  bison file flex gcc g++ libexpat1-dev libfreetype6-dev make pkg-config python texinfo unifont
if [ $? -ne 0 ]; then exit $?; fi
