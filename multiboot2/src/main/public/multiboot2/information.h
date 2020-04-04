// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace multiboot2
{
  //! @brief Multiboot2 information magic number

  constexpr ps::size4 information_magic = 0x36d76289;

  //! @brief Multiboot2 information list alignment

  constexpr unsigned information_alignment = 8;

  //! @brief Multiboot2 information list

  struct alignas(information_alignment) information_list
  {
    ps::size4 size;
    ps::size4 reserved;
  };

  //! @brief Multiboot2 information item type

  enum class information_type : ps::size4
  {
    end              = 0,
    command_line     = 1,
    loader_name      = 2,
    modules          = 3,
    basic_memory     = 4,
    boot_device      = 5,
    memory_map       = 6,
    vbe              = 7,
    framebuffer      = 8,
    elf_symbols      = 9,
    apm              = 10,
    efi32            = 11,
    efi64            = 12,
    smbios           = 13,
    acpi_old         = 14,
    acpi_new         = 15,
    network          = 16,
  };

  namespace internal
  {
    struct information_item;
  }

  auto begin (information_list & list) -> internal::information_item * ;

  auto end (information_list & list) -> internal::information_item * ;

  auto next (internal::information_item * item) -> internal::information_item * ;

  //! @brief Multiboot2 end information list

  struct end_information
  {
    information_type type;
    ps::size4    size;
  };

  //! @brief Multiboot2 command line information

  struct command_line_information
  {
    information_type type;
    ps::size4    size;

    char command [];
  };

  //! @brief Multiboot2 loader name information

  struct loader_name_information
  {
    information_type type;
    ps::size4    size;

    char name [];
  };

  //! @brief Multiboot2 modules information

  struct modules_information
  {
    information_type type;
    ps::size4    size;

    ps::size4 start;
    ps::size4 end;
    char          command [];
  };

  //! @brief Multiboot2 basic memory information

  struct basic_memory_information
  {
    information_type type;
    ps::size4    size;

    ps::size4 lower;
    ps::size4 upper;
  };

  //! @brief Multiboot2 boot device information

  struct boot_device_information
  {
    information_type type;
    ps::size4    size;

    ps::size4 device;
    ps::size4 partition;
    ps::size4 sub_partition;
  };

  //! @brief Multiboot2 memory map information

  struct memory_map_information
  {
    information_type type;
    ps::size4    size;

    ps::size4 entry_size;
    ps::size4 entry_version;
  };

  //! @brief Multiboot2 ELF symbols information

  struct elf_symbols_information
  {
    information_type type;
    ps::size4    size;

    ps::size2 num;
    ps::size2 entsize;
    ps::size2 shndx;
    ps::size2 reserved;
  };

  //! @brief Multiboot2 APM information

  struct apm_information
  {
    information_type type;
    ps::size4    size;

    ps::size2 version;
    ps::size2 cseg;
    ps::size2 offset;
    ps::size2 cseg_16;
    ps::size2 dseg;
    ps::size2 flags;
    ps::size2 cseg_len;
    ps::size2 cseg_16_len;
    ps::size2 dseg_len;
  };

  //! @brief Multiboot2 VBE information

  struct vbe_information
  {
    information_type type;
    ps::size4    size;

    ps::size2 mode;
    ps::size2 interface_seg;
    ps::size2 interface_off;
    ps::size2 interface_len;
    ps::size2 control_info;
    ps::size2 mode_info;
  };

  //! @brief Multiboot2 framebuffer information

  struct framebuffer_information
  {
    information_type type;
    ps::size4    size;

    ps::size8 address;
    ps::size4 pitch;
    ps::size4 width;
    ps::size4 height;
    ps::size1  bpp;
    ps::size4 framebuffer_type;
    ps::size1  reserved;
  };

  //! @brief Multiboot2 EFI32 information

  struct efi32_information
  {
    information_type type;
    ps::size4    size;

    ps::size4 pointer;
  };

  //! @brief Multiboot2 EFI64 information

  struct efi64_information
  {
    information_type type;
    ps::size4    size;

    ps::size8 pointer;
  };

  //! @brief Multiboot2 SMBIOS information

  struct smbios_information
  {
    information_type type;
    ps::size4    size;

    ps::size1 major;
    ps::size1 minor;
    ps::size1 reserved [6];
    ps::size1 tables   [];
  };

  //! @brief Multiboot2 ACPI information

  struct acpi_information
  {
    information_type type;
    ps::size4    size;

    ps::size1 rsdp [];
  };

  //! @brief Multiboot2 network information

  struct network_information
  {
    information_type type;
    ps::size4    size;

    ps::size1 dhcpack [];
  };

}

//! Inline definitions

namespace multiboot2
{

  namespace internal
  {
    struct information_item
    {
      information_type type;
      ps::size4    size;
    };
  }

  inline
  auto begin (information_list & list) -> internal::information_item *
  {
    auto const base = reinterpret_cast<char *>(& list);
    auto const first = base + 8;
    return reinterpret_cast<internal::information_item *>(first);
  }

  inline
  auto end (information_list & list) -> internal::information_item *
  {
    auto const base = reinterpret_cast<char *>(& list);
    auto const last = base + list.size;
    return reinterpret_cast<internal::information_item *>(last);
  }

  inline
  auto next (internal::information_item * item) -> internal::information_item *
  {
    auto const base = reinterpret_cast<char *>(item);
    auto const successor = base + ((item->size + 7) & ~7);
    return reinterpret_cast<internal::information_item *>(successor);
  }

}
