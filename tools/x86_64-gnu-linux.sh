#!/bin/bash

# Settings

HOST=x86_64-pc-linux-gnu
TARGET=i686-pc-elf

SRC=${HOME}/src
OBJ=${HOME}/obj/${HOST}/${TARGET}
PREFIX=/opt/${TARGET}
TMP=${HOME}/tmp/${HOST}

CFLAGS=-O2
MFLAGS=-j5

rm -rf ${OBJ}

# Binutils

mkdir -p ${OBJ}/binutils 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/binutils ${SRC}/binutils-2.34/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-sysroot
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/binutils make ${MFLAGS}
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/binutils DESTDIR=${TMP} make install
if [ $? -ne 0 ]; then exit $?; fi

# GCC

mkdir -p ${OBJ}/gcc 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gcc PATH="${TMP}/${PREFIX}/bin:${PATH}" ${SRC}/gcc-9.2.0/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --enable-languages=c,c++ --without-headers
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gcc PATH="${TMP}/${PREFIX}/bin:${PATH}" make ${MFLAGS} all-gcc all-target-libgcc
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gcc DESTDIR=${TMP} PATH="${TMP}/${PREFIX}/bin:${PATH}" make install-gcc install-target-libgcc
if [ $? -ne 0 ]; then exit $?; fi

# GDB

mkdir -p ${OBJ}/gdb 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gdb PATH="${TMP}/${PREFIX}/bin:${PATH}" ${SRC}/gdb-9.1/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET}
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gdb PATH="${TMP}/${PREFIX}/bin:${PATH}" make ${MFLAGS}
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gdb DESTDIR=${TMP} make install
if [ $? -ne 0 ]; then exit $?; fi

# GRUB i386-pc

mkdir -p ${OBJ}/grub-pc 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-pc PATH="${TMP}/${PREFIX}/bin:${PATH}" ${SRC}/grub-2.04/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-platform=pc
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-pc PATH="${TMP}/${PREFIX}/bin:${PATH}" make ${MFLAGS}
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-pc DESTDIR="${TMP}" make install
if [ $? -ne 0 ]; then exit $?; fi

# GRUB i386-efi

mkdir -p ${OBJ}/grub-efi 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-efi PATH="${TMP}/${PREFIX}/bin:${PATH}" ${SRC}/grub-2.04/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-platform=efi
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-efi PATH="${TMP}/${PREFIX}/bin:${PATH}" make ${MFLAGS}
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-efi DESTDIR="${TMP}" make install
if [ $? -ne 0 ]; then exit $?; fi

# GRUB i386-qemu

mkdir -p ${OBJ}/grub-qemu 2>/dev/null
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-qemu PATH="${TMP}/${PREFIX}/bin:${PATH}" ${SRC}/grub-2.04/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-platform=qemu
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-qemu PATH="${TMP}/${PREFIX}/bin:${PATH}" make ${MFLAGS}
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-qemu DESTDIR="${TMP}" make install
if [ $? -ne 0 ]; then exit $?; fi
