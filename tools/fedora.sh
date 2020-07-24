#!/bin/sh

echo Installing Fedora tools...

dnf install \
 texinfo \
 gmp-devel \
 mpfr-devel \
 libmpc-devel \
 java-latest-openjdk-devel \
 freetype-devel \
 unifont-fonts \
 glib2-devel \
 pixman-devel \
 xorriso \
 expat-devel

