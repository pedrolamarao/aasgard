// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

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
    unsigned char _test_result = 1;
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    pc::cmos<x86::port> cmos;
    
    // Note: CMOS RTC values must be fixed by the system emulator
    
    auto status_B = cmos.read(0x0B, false);
    
    // CMOS RTC time format
    
    auto format_24 = (status_B & 0x02) == 0x02;
    
    if (! format_24) {
    	_test_result = 2;
    	return;
    }
    
    // CMOS RTC date format
    
    auto format_Binary = (status_B & 0x04) == 0x04;

    if (format_Binary) {
    	_test_result = 3;
    	return;
    }

    // CMOS RTC year

    if (cmos.read(0x09, false) != 0x20) {
    	_test_result = 10;
    	return;
    }

    // CMOS RTC month

    if (cmos.read(0x08, false) != 0x07) {
    	_test_result = 11;
    	return;
    }

    // CMOS RTC day of month

    if (cmos.read(0x07, false) != 0x24) {
    	_test_result = 12;
    	return;
    }

    // CMOS RTC hour

    if (cmos.read(0x04, false) != 0x22) {
    	_test_result = 20;
    	return;
    }

    // CMOS RTC minute

    if (cmos.read(0x02, false) != 0x46) {
    	_test_result = 21;
    	return;
    }

    _test_result = 0;
    return;
}

//! @}
