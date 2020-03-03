// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>


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

// IA32 IDT

namespace
{
    using gate_descriptor = x86::interrupt_gate_descriptor;

    gate_descriptor interrupt_descriptor_table [256] __attribute__((aligned(8), section(".idt"))) =
    { };

    extern "C"
    void __interrupt_service_routine ();
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
    if (magic != multiboot2::information_magic) {
        _test_result = 10;
        return;
    }

    x86::set_global_descriptor_table(global_descriptor_table);
    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, __interrupt_service_routine, interrupt_gate_access(true, 0) };
    }

    x86::set_interrupt_descriptor_table(interrupt_descriptor_table, 256);
    std::uint64_t idt = x86::get_interrupt_descriptor_table();

    // #TODO document this assert
    if ((256 * sizeof(interrupt_gate_descriptor)) != (idt & 0xFFFF)) {
        _test_result = 20;
        return;
    }

    // #TODO document this assert
    if (std::uint32_t(& interrupt_descriptor_table) != ((idt >> 16) & 0xFFFFFFFF)) {
        _test_result = 30;
        return;
    }

    x86::interrupt<0>();

    _test_result = 40;
    return;
}
