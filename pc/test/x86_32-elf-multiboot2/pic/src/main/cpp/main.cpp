// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>
#include <x86/port.h>

#include <pc/pic.h>


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

//! x86 protected-mode GDT

namespace
{
    [[gnu::aligned(8)]]
    constexpr x86::segment_descriptor global_descriptor_table [5] =
    {
        { },
        { 0, 0xFFFFFFFF, x86::code_segment_access(true, false, 0), x86::segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, x86::data_segment_access(true, false, 0), x86::segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, x86::code_segment_access(true, false, 3), x86::segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, x86::data_segment_access(true, false, 3), x86::segment_granularity(false, true, true) },
    };
}

//! x86 protected-mode IDT

namespace
{
    [[gnu::aligned(8)]]
    x86::interrupt_gate_descriptor interrupt_descriptor_table [256] =
    { };

    extern "C"
    void __interrupt_service_routine ();
}

//! Test result

extern "C"
{
    [[gnu::used]]
    unsigned char _test_result = 1;
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    asm volatile ("cli");

    // gdt

    x86::set_global_descriptor_table(global_descriptor_table);
    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

    // idt

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, __interrupt_service_routine, x86::interrupt_gate_access(true, 0) };
    }
    x86::set_interrupt_descriptor_table(interrupt_descriptor_table, 256);

    // pic

    auto master = pc::pic<x86::port>::master();
    auto slave  = pc::pic<x86::port>::slave();

    master._command.write(0x11);
    slave._command.write(0x11);
    master._data.write(0x20);
    slave._data.write(0x28);
    master._data.write(4);
    slave._data.write(2);
    master._data.write(1);
    slave._data.write(1);
    master._data.write(0);
    slave._data.write(0);

    asm volatile ("sti");

    // Assumes hardware is noisy

    return;
}
