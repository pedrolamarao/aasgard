// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/port.h>

#include <pc/cmos.h>


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
    unsigned int _test_result = 0xFF;
}

//! Multiboot2 entry point

extern "C"
[[gnu::fastcall]]
void main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
    if (magic != multiboot2::information_magic) {
        _test_result = 1;
        return;
    }

    pc::cmos<x86::port> cmos;

    // CMOS RTC year

    if (cmos.read(0x09, false) != 01) {
    	_test_result = 2;
    	return;
    }

    // CMOS RTC month

    if (cmos.read(0x08, false) != 02) {
    	_test_result = 3;
    	return;
    }

    // CMOS RTC day of month

    if (cmos.read(0x07, false) != 03) {
    	_test_result = 4;
    	return;
    }

    // CMOS RTC hour

    if (cmos.read(0x04, false) != 04) {
    	_test_result = 5;
    	return;
    }

    // CMOS RTC minute

    if (cmos.read(0x02, false) != 05) {
    	_test_result = 6;
    	return;
    }

    _test_result = 0;
    return;
}

//! @}
