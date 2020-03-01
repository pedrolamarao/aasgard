#!/bin/bash

# Settings

SRC=${HOME}/src

# Download

rm -rf ${SRC}

mkdir ${SRC} 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

wget -c -P ${SRC} https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

wget -c -P ${SRC} https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

wget -c -P ${SRC} https://ftp.gnu.org/gnu/gdb/gdb-9.1.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

wget -c -P ${SRC} https://ftp.gnu.org/gnu/grub/grub-2.04.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

wget -c -P ${SRC} https://download.qemu.org/qemu-4.2.0.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

# Inflate

tar -C ${SRC} -xJf ${SRC}/binutils-2.34.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

tar -C ${SRC} -xJf ${SRC}/gcc-9.2.0.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

tar -C ${SRC} -xJf ${SRC}/gdb-9.1.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

tar -C ${SRC} -xJf ${SRC}/grub-2.04.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

tar -C ${SRC} -xJf ${SRC}/qemu-4.2.0.tar.xz
if [ $? -ne 0 ]; then exit $?; fi

# Miscellaneous

env -C ${SRC}/gcc-9.2.0 contrib/download_prerequisites
