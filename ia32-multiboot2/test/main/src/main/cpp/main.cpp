// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>


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

extern "C"
[[gnu::fastcall]]
void main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
    if (magic != 0x36D76289) {
    	_test_result = 1;
    	return;
    }

    _test_result = 0;
    return;
}
