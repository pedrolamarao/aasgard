#!/bin/sh

# source
apt-get install  bzip2 wget xz-utils
if [ $? -ne 0 ]; then exit $?; fi

# build
apt-get install  bison file gcc g++ libexpat1-dev make texinfo
if [ $? -ne 0 ]; then exit $?; fi
