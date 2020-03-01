// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/cpuid.h>

namespace
{
    using namespace multiboot2;

    struct
    {
        header_prologue prologue;
        end_request     end;
    }
    constexpr request [[gnu::used, gnu::section(".multiboot2")]] =
    {
        { architecture_type::x86, sizeof(request), },
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
//!
//! @see start.S

extern "C"
[[gnu::fastcall]]
void main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
    if (! x86::has_cpuid()) {
        _test_result = 10;
        return;
    }

    x86::cpuid cpuid_0 { 0 };
    if (cpuid_0.a() == 0) {
        _test_result = 20;
        return;
    }

    x86::cpuid cpuid_1 { 1 };
    if (cpuid_0.a() == 0) {
        _test_result = 30;
        return;
    }

    _test_result = 0;
    return;
}
