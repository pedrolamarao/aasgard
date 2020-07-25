// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>


//! Multiboot2 minimal request for ELF program

namespace
{
    struct request_type
    {
        multiboot2::header_prologue prologue;
        multiboot2::end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constexpr request_type request =
    {
        { multiboot2::architecture_type::x86, sizeof(request), },
        { },
    };
}

//! Test result

extern "C"
{
    [[gnu::used]]
    unsigned char _test_result = 0xFF;
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    // multiboot2

    if (magic != multiboot2::information_magic) {
        _test_result = 10;
        return;
    }

    // cpuid

    if (! x86::has_cpuid()) {
        _test_result = 20;
        return;
    }

    x86::cpuid_1 cpuid_1;

    // msr

    if (! cpuid_1.has_msr()) {
        _test_result = 30;
        return;
    }

    if (! cpuid_1.has_local_apic()) {
        _test_result = 40;
        return;
    }

    auto value = x86::read_msr(0x1B);
    if ((value & 0xFFFFFFFFFFFF0000) != 0x00000000FEE00000) {
        _test_result = 50;
        return;
    }

    _test_result = 0;
    return;
}
