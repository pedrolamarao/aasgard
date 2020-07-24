#!/bin/bash

# General settings

TOOLS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"    
PREFIX=${TOOLS}/usr
SRC=${TOOLS}/src
OBJ=${TOOLS}/obj

PATH=${PREFIX}/bin:${PATH}

# Build settings

CFLAGS=-O2
CXXFLAGS=-O2
MFLAGS=-j12

echo Building...

mkdir -p ${OBJ}

echo Building GNU Binutils i686-pc-none-elf...

if [ ! -d ${OBJ}/binutils-i686-pc-none-elf ]; then
    
    mkdir -p ${OBJ}/binutils-i686-pc-none-elf \
        1>${OBJ}/binutils-i686-pc-none-elf.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/binutils-i686-pc-none-elf \
        ${SRC}/binutils-2.34/configure --prefix=${PREFIX} --target=i686-pc-elf --with-sysroot --disable-nls \
        1>${OBJ}/binutils-i686-pc-none-elf.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/binutils-i686-pc-none-elf \
    make ${MFLAGS} \
    1>${OBJ}/binutils-i686-pc-none-elf.log 2>&1 ||
    exit $? 

env -C ${OBJ}/binutils-i686-pc-none-elf \
    make install \
    1>${OBJ}/binutils-i686-pc-none-elf.log 2>&1 ||
    exit $?

echo Building GNU Binutils x86_64-pc-none-elf...

if [ ! -d ${OBJ}/binutils-x86_64-pc-none-elf ]; then
    
    mkdir -p ${OBJ}/binutils-x86_64-pc-none-elf \
        1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/binutils-x86_64-pc-none-elf \
        ${SRC}/binutils-2.34/configure --prefix=${PREFIX} --target=x86_64-pc-elf --with-sysroot --disable-nls \
        1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/binutils-x86_64-pc-none-elf \
    make ${MFLAGS} \
    1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1 ||
    exit $? 

env -C ${OBJ}/binutils-x86_64-pc-none-elf \
    make install \
    1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1 ||
    exit $?
    
echo Building GNU GCC i686-pc-none-elf...

if [ ! -d ${OBJ}/gcc-i686-pc-none-elf ]; then
    
    mkdir -p ${OBJ}/gcc-i686-pc-none-elf \
        1>${OBJ}/gcc-i686-pc-none-elf.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/gcc-i686-pc-none-elf \
        ${SRC}/gcc-10.2.0/configure --prefix=${PREFIX} --target=i686-pc-elf --without-headers --enable-languages=c,c++ --disable-nls --disable-bootstrap \
        1>${OBJ}/gcc-i686-pc-none-elf.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/gcc-i686-pc-none-elf \
    make all-gcc all-target-libgcc ${MFLAGS} \
    1>${OBJ}/gcc-i686-pc-none-elf.log 2>&1 ||
    exit $? 

env -C ${OBJ}/gcc-i686-pc-none-elf \
    make install-gcc install-target-libgcc  \
    1>${OBJ}/gcc-i686-pc-none-elf.log 2>&1 ||
    exit $?
    
echo Building GNU GCC x86_64-pc-none-elf...

if [ ! -d ${OBJ}/gcc-x86_64-pc-none-elf ]; then
    
    mkdir -p ${OBJ}/gcc-x86_64-pc-none-elf \
        1>${OBJ}/gcc-x86_64-pc-none-elf.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/gcc-x86_64-pc-none-elf \
        ${SRC}/gcc-10.2.0/configure --prefix=${PREFIX} --target=x86_64-pc-elf --without-headers --enable-languages=c,c++ --disable-nls --disable-bootstrap \
        1>${OBJ}/gcc-x86_64-pc-none-elf.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/gcc-x86_64-pc-none-elf \
    make all-gcc all-target-libgcc ${MFLAGS} \
    1>${OBJ}/gcc-x86_64-pc-none-elf.log 2>&1 ||
    exit $? 

env -C ${OBJ}/gcc-x86_64-pc-none-elf \
    make install-gcc install-target-libgcc  \
    1>${OBJ}/gcc-x86_64-pc-none-elf.log 2>&1 ||
    exit $?

echo Building GNU GDB i686-pc-none-elf...

if [ ! -d ${OBJ}/gdb-i686-pc-none-elf ]; then
    
    mkdir -p ${OBJ}/gdb-i686-pc-none-elf \
        1>${OBJ}/gdb-i686-pc-none-elf.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/gdb-i686-pc-none-elf \
        ${SRC}/gdb-9.2/configure --prefix=${PREFIX} --target=i686-pc-elf --with-expat \
        1>${OBJ}/gdb-i686-pc-none-elf.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/gdb-i686-pc-none-elf \
    make ${MFLAGS} \
    1>${OBJ}/gdb-i686-pc-none-elf.log 2>&1 ||
    exit $? 

env -C ${OBJ}/gdb-i686-pc-none-elf \
    make install \
    1>${OBJ}/gdb-i686-pc-none-elf.log 2>&1 ||
    exit $? 

echo Building GNU GDB x86_64-pc-none-elf...

if [ ! -d ${OBJ}/gdb-x86_64-pc-none-elf ]; then
    
    mkdir -p ${OBJ}/gdb-x86_64-pc-none-elf \
        1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/gdb-x86_64-pc-none-elf \
        ${SRC}/gdb-9.2/configure --prefix=${PREFIX} --target=x86_64-pc-elf --with-expat \
        1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/gdb-x86_64-pc-none-elf \
    make ${MFLAGS} \
    1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1 ||
    exit $? 

env -C ${OBJ}/gdb-x86_64-pc-none-elf \
    make install \
    1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1 ||
    exit $? 

echo Building GNU GRUB i386-pc...

if [ ! -d ${OBJ}/grub-i386-pc ]; then
    
    mkdir -p ${OBJ}/grub-i386-pc \
        1>${OBJ}/grub-i386-pc.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/grub-i386-pc \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=i386 --with-platform=pc --disable-werror \
        1>${OBJ}/grub-i386-pc.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/grub-i386-pc \
    make ${MFLAGS} \
    1>${OBJ}/grub-i386-pc.log 2>&1 ||
    exit $? 

env -C ${OBJ}/grub-i386-pc \
    make install \
    1>${OBJ}/grub-i386-pc.log 2>&1 ||
    exit $? 

echo Building GNU GRUB i386-efi...

if [ ! -d ${OBJ}/grub-i386-efi ]; then
    
    mkdir -p ${OBJ}/grub-i386-efi \
        1>${OBJ}/grub-i386-efi.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/grub-i386-efi \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=i386 --with-platform=efi --disable-werror \
        1>${OBJ}/grub-i386-efi.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/grub-i386-efi \
    make ${MFLAGS} \
    1>${OBJ}/grub-i386-efi.log 2>&1 ||
    exit $? 

env -C ${OBJ}/grub-i386-efi \
    make install \
    1>${OBJ}/grub-i386-efi.log 2>&1 ||
    exit $? 

echo Building GNU GRUB i386-qemu...

if [ ! -d ${OBJ}/grub-i386-qemu ]; then
    
    mkdir -p ${OBJ}/grub-i386-qemu \
        1>${OBJ}/grub-i386-qemu.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/grub-i386-qemu \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=i386 --with-platform=qemu --disable-werror \
        1>${OBJ}/grub-i386-qemu.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/grub-i386-qemu \
    make ${MFLAGS} \
    1>${OBJ}/grub-i386-qemu.log 2>&1 ||
    exit $? 

env -C ${OBJ}/grub-i386-qemu \
    make install \
    1>${OBJ}/grub-i386-qemu.log 2>&1 ||
    exit $? 

echo Building GNU GRUB x86_64-efi...

if [ ! -d ${OBJ}/grub-x86_64-efi ]; then

    mkdir -p ${OBJ}/grub-x86_64-efi \
        1>${OBJ}/grub-x86_64-efi.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/grub-x86_64-efi \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=x86_64 --with-platform=efi --disable-werror \
        1>${OBJ}/grub-x86_64-efi.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/grub-x86_64-efi \
    make ${MFLAGS} \
    1>${OBJ}/grub-x86_64-efi.log 2>&1 ||
    exit $? 

env -C ${OBJ}/grub-x86_64-efi \
    make install \
    1>${OBJ}/grub-x86_64-efi.log 2>&1 ||
    exit $? 

echo Building QEMU...

if [ ! -d ${OBJ}/qemu ]; then

    mkdir -p ${OBJ}/qemu \
        1>${OBJ}/qemu.log 2>&1 ||
        exit $? 
    
    env -C ${OBJ}/qemu \
        ${SRC}/qemu-5.0.0/configure --prefix=${PREFIX} --enable-plugins --enable-kvm \
        1>${OBJ}/qemu.log 2>&1 ||
        exit $? 

fi

env -C ${OBJ}/qemu \
    make ${MFLAGS} \
    1>${OBJ}/qemu.log 2>&1 ||
    exit $? 

env -C ${OBJ}/qemu \
    make install \
    1>${OBJ}/qemu.log 2>&1 ||
    exit $? 

echo Finish!
