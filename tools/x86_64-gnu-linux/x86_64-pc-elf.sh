#!/bin/bash

# Settings

HOST=x86_64-pc-linux-gnu
TARGET=x86_64-pc-elf

SRC=${HOME}/src
OBJ=${HOME}/obj/${HOST}/${TARGET}
PREFIX=/opt/${TARGET}
TMP=${HOME}/tmp/${HOST}

MFLAGS=-j1

# Prepare

echo Building tools host ${HOST} target ${TARGET}...

rm -rf ${TMP}/${PREFIX}
rm -rf ${OBJ}
mkdir -p ${OBJ}

# binutils

echo Building binutils...

mkdir -p ${OBJ}/binutils \
 1>${OBJ}/binutils.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/binutils CFLAGS=-O2 CXXFLAGS=-O2 \
 ${SRC}/binutils-2.34/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-sysroot \
 1>${OBJ}/binutils.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/binutils \
 make ${MFLAGS} \
 1>${OBJ}/binutils.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/binutils DESTDIR=${TMP} \
 make install \
 1>${OBJ}/binutils.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

# GCC

echo Building gcc...

mkdir -p ${OBJ}/gcc \
  1>${OBJ}/gcc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gcc CFLAGS=-O2 CXXFLAGS=-O2 PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 ${SRC}/gcc-9.2.0/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --enable-languages=c,c++ --without-headers \
 1>${OBJ}/gcc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gcc PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make ${MFLAGS} all-gcc all-target-libgcc \
 1>${OBJ}/gcc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gcc DESTDIR=${TMP} PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make install-gcc install-target-libgcc \
 1>${OBJ}/gcc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

# GDB

echo Building gdb...

mkdir -p ${OBJ}/gdb \
 1>${OBJ}/gdb.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gdb CFLAGS=-O2 CXXFLAGS=-O2 PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 ${SRC}/gdb-9.1/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} \
 1>${OBJ}/gdb.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gdb PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make ${MFLAGS} \
 1>${OBJ}/gdb.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/gdb DESTDIR=${TMP} \
 make install \
 1>${OBJ}/gdb.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

# GRUB pc

echo Building grub pc...

mkdir -p ${OBJ}/grub-pc \
 1>${OBJ}/grub.pc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-pc CFLAGS=-O2 CXXFLAGS=-O2 PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 ${SRC}/grub-2.04/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-platform=pc \
 1>${OBJ}/grub.pc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-pc PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make ${MFLAGS} \
 1>${OBJ}/grub.pc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-pc DESTDIR="${TMP}" \
 make install \
 1>${OBJ}/grub.pc.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

# GRUB efi

echo Building grub efi...

mkdir -p ${OBJ}/grub-efi \
 1>${OBJ}/grub.efi.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-efi CFLAGS=-O2 CXXFLAGS=-O2 PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 ${SRC}/grub-2.04/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-platform=efi \
 1>${OBJ}/grub.efi.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-efi PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make ${MFLAGS} \
 1>${OBJ}/grub.efi.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-efi DESTDIR="${TMP}" \
 make install \
 1>${OBJ}/grub.efi.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

# GRUB qemu

echo Building grub qemu...

mkdir -p ${OBJ}/grub-qemu \
 1>${OBJ}/grub.qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-qemu CFLAGS=-O2 CXXFLAGS=-O2 PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 ${SRC}/grub-2.04/configure --prefix=${PREFIX} --host=${HOST} --target=${TARGET} --with-platform=qemu \
 1>${OBJ}/grub.qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-qemu PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make ${MFLAGS} \
 1>${OBJ}/grub.qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/grub-qemu DESTDIR="${TMP}" \
 make install \
 1>${OBJ}/grub.qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

# QEMU

echo Building qemu...

mkdir -p ${OBJ}/qemu \
 1>${OBJ}/qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/qemu CFLAGS=-O2 CXXFLAGS=-O2 PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 ${SRC}/qemu-4.2.0/configure --prefix=${PREFIX} --host=${HOST} --target-list=x86_64-softmmu --disable-user --enable-plugins \
 1>${OBJ}/qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/qemu PATH="${TMP}/${PREFIX}/bin:${PATH}" \
 make ${MFLAGS} \
 1>${OBJ}/qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

env -C ${OBJ}/qemu DESTDIR="${TMP}" \
 make install \
 1>${OBJ}/qemu.log 2>&1
if [ $? -ne 0 ]; then exit $?; fi

echo Success!
