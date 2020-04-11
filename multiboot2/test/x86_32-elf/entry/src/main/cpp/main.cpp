// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! _start symbol

extern "C"
{
    extern ps::size4 _start;
}

//! Multiboot 2 request

namespace
{
    using namespace multiboot2;

    struct request_type
    {
        header_prologue        prologue;
        entry_address_request  address;
        end_request            end;
    };

    [[gnu::used, gnu::section(".text")]]
    constexpr request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { tag_type::entry, 0, sizeof(entry_address_request), 0x1000 + sizeof(request) },
        { },
    };
}

//! Test result

extern "C"
{
	unsigned char _test_result = 0xFF;
}
