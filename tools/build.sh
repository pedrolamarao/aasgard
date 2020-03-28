#!/bin/bash

# Settings

PREFIX=${HOME}/tools
SRC=${PREFIX}/src
OBJ=${PREFIX}/obj

export AR=llvm-ar-8
export CC=clang
export CFLAGS=-O2 
export CXX=clang++
export CXXFLAGS=-O2
export LD=lld
export LDFLAGS=-flto
export NM=llvm-nm-8
export RANLIB=llvm-ranlib-8

export BUILD_AR=$AR
export BUILD_CC=$CC
export BUILD_CFLAGS=$CFLAGS
export BUILD_CXX=$CXX
export BUILD_CXXFLAGS=$CXXFLAGS
export BUILD_LD=$LD
export BUILD_LDFLAGS=$LDFLAGS
export BUILD_NM=$NM
export BUILD_RANLIB=$RANLIB

export BUILD_AR=$AR
export BUILD_CC=$CC
export BUILD_CFLAGS=$CFLAGS
export BUILD_CXX=$CXX
export BUILD_CXXFLAGS=$CXXFLAGS
export BUILD_LD=$LD
export BUILD_LDFLAGS=$LDFLAGS
export BUILD_NM=$NM
export BUILD_RANLIB=$RANLIB

export MFLAGS=-j6

echo Building tools...

mkdir -p ${OBJ}

if [ ! -d ${OBJ}/llvm ]; then

    echo Building LLVM...

    mkdir -p ${OBJ}/llvm \
        1>${OBJ}/llvm.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    cmake \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="${PREFIX}" -DLLVM_ENABLE_PROJECTS="clang;lld" \
        -B "${OBJ}/llvm" "${SRC}/llvm-project-10.0.0/llvm" \
        1>${OBJ}/llvm.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/llvm \
        make ${MFLAGS} \
        1>${OBJ}/llvm.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/llvm \
        make install \
        1>${OBJ}/llvm.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/binutils-x86_64-pc-none-elf ]; then

    echo Building GNU Binutils x86_64-pc-none-elf...
    
    mkdir -p ${OBJ}/binutils-x86_64-pc-none-elf \
        1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/binutils-x86_64-pc-none-elf \
        ${SRC}/binutils-2.34/configure --prefix=${PREFIX} --target=x86_64-pc-elf \
        1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/binutils-x86_64-pc-none-elf \
        make ${MFLAGS} \
        1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/binutils-x86_64-pc-none-elf \
        make install \
        1>${OBJ}/binutils-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/gdb-x86_64-pc-none-elf ]; then

    echo Building GNU GDB x86_64-pc-none-elf...
    
    mkdir -p ${OBJ}/gdb-x86_64-pc-none-elf \
        1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/gdb-x86_64-pc-none-elf \
        ${SRC}/gdb-9.1/configure --prefix=${PREFIX} --target=x86_64-pc-elf \
        1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/gdb-x86_64-pc-none-elf \
        make ${MFLAGS} \
        1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/gdb-x86_64-pc-none-elf \
        make install \
        1>${OBJ}/gdb-x86_64-pc-none-elf.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/grub-i386-pc ]; then

    echo Building GNU GRUB i386-pc...
    
    mkdir -p ${OBJ}/grub-i386-pc \
        1>${OBJ}/grub-i386-pc.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-pc \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=i386 --with-platform=pc \
        1>${OBJ}/grub-i386-pc.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-pc \
        make ${MFLAGS} \
        1>${OBJ}/grub-i386-pc.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-pc \
        make install \
        1>${OBJ}/grub-i386-pc.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/grub-i386-efi ]; then

    echo Building GNU GRUB i386-efi...
    
    mkdir -p ${OBJ}/grub-i386-efi \
        1>${OBJ}/grub-i386-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-efi \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=i386 --with-platform=efi \
        1>${OBJ}/grub-i386-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-efi \
        make ${MFLAGS} \
        1>${OBJ}/grub-i386-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-efi \
        make install \
        1>${OBJ}/grub-i386-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/grub-i386-qemu ]; then

    echo Building GNU GRUB i386-qemu...
    
    mkdir -p ${OBJ}/grub-i386-qemu \
        1>${OBJ}/grub-i386-qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-qemu \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=i386 --with-platform=qemu \
        1>${OBJ}/grub-i386-qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-qemu \
        make ${MFLAGS} \
        1>${OBJ}/grub-i386-qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-i386-qemu \
        make install \
        1>${OBJ}/grub-i386-qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/grub-x86_64-efi ]; then

    echo Building GNU GRUB x86_64-efi...
    
    mkdir -p ${OBJ}/grub-x86_64-efi \
        1>${OBJ}/grub-x86_64-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-x86_64-efi \
        ${SRC}/grub-2.04/configure --prefix=${PREFIX} --target=x86_64 --with-platform=efi \
        1>${OBJ}/grub-x86_64-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-x86_64-efi \
        make ${MFLAGS} \
        1>${OBJ}/grub-x86_64-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/grub-x86_64-efi \
        make install \
        1>${OBJ}/grub-x86_64-efi.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

if [ ! -d ${OBJ}/qemu ]; then

    echo Building QEMU...
    
    mkdir -p ${OBJ}/qemu \
        1>${OBJ}/qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/qemu \
        ${SRC}/qemu-4.2.0/configure --prefix=${PREFIX} --disable-user --enable-plugins \
        1>${OBJ}/qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/qemu \
        make ${MFLAGS} \
        1>${OBJ}/qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi
    
    env -C ${OBJ}/qemu \
        make install \
        1>${OBJ}/qemu.log 2>&1
    if [ $? -ne 0 ]; then exit $?; fi

fi

echo Finish!
