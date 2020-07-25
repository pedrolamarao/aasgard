// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Multiboot 2 request

namespace
{
    using namespace multiboot2;

    struct request_type
    {
        header_prologue prologue;
        end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constexpr request_type request =
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
void main ( ps::size4 magic, multiboot2::information_list * response )
{
    if (magic == 0) {
        _test_result = 10;
        return;
    }
    
    if (response == 0) {
        _test_result = 20;
        return;
    }

    if (magic != multiboot2::information_magic) {
        _test_result = 30;
        return;
    }

    _test_result = 0;
    return;
}
