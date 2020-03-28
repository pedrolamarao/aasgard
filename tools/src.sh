#!/bin/bash

# Settings

SRC=${HOME}/tools/src

mkdir -p ${SRC} 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

if [ ! -d ${SRC}/llvm-project-10.0.0 ]; then
    wget -c -P ${SRC} https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/llvm-project-10.0.0.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
    tar -C ${SRC} -xJf ${SRC}/llvm-project-10.0.0.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
fi

if [ ! -d ${SRC}/binutils-2.34 ]; then
    wget -c -P ${SRC} https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
    tar -C ${SRC} -xJf ${SRC}/binutils-2.34.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
fi

if [ ! -d ${SRC}/gdb-9.1 ]; then
    wget -c -P ${SRC} https://ftp.gnu.org/gnu/gdb/gdb-9.1.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
    tar -C ${SRC} -xJf ${SRC}/gdb-9.1.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
fi

if [ ! -d ${SRC}/grub-2.04 ]; then
    wget -c -P ${SRC} https://ftp.gnu.org/gnu/grub/grub-2.04.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
    tar -C ${SRC} -xJf ${SRC}/grub-2.04.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
fi

if [ ! -d ${SRC}/qemu-4.2.0 ]; then
    wget -c -P ${SRC} https://download.qemu.org/qemu-4.2.0.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
    tar -C ${SRC} -xJf ${SRC}/qemu-4.2.0.tar.xz
    if [ $? -ne 0 ]; then exit $?; fi
fi
