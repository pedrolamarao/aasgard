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
