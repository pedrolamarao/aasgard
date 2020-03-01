// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>


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

// IA32 GDT

namespace
{
    using namespace x86;

    constexpr segment_descriptor global_descriptor_table [5] [[gnu::aligned(8), gnu::section(".gdt")]] =
    {
        { },
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
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
[[gnu::fastcall]]
void main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
    x86::load_global_descriptor_table(global_descriptor_table);
    // #XXX: verify

    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));
    // #XXX: verify

    std::uint64_t gdt { 0xFFFFFFFFFFFFFFFF };
    x86::internal::__store_global_descriptor_table(gdt);

    if (((5 * sizeof(segment_descriptor)) - 1) != (gdt & 0xFFFF)) {
        _test_result = 30;
        return;
    }

    if (std::uint32_t(& global_descriptor_table) != ((gdt >> 16) & 0xFFFFFFFF)) {
        _test_result = 40;
        return;
    }

    _test_result = 0;
    return;
}
