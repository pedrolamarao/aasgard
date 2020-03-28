// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


//! Declarations

namespace multiboot2
{
  //! @brief Multiboot2 information magic number

  constexpr std::uint32_t information_magic = 0x36d76289;

  //! @brief Multiboot2 information list alignment

  constexpr unsigned information_alignment = 8;

  //! @brief Multiboot2 information list

  struct alignas(information_alignment) information_list
  {
    std::uint32_t size;
    std::uint32_t reserved;
  };

  //! @brief Multiboot2 information item type

  enum class information_type : std::uint32_t
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
    std::uint32_t    size;
  };

  //! @brief Multiboot2 command line information

  struct command_line_information
  {
    information_type type;
    std::uint32_t    size;

    char command [];
  };

  //! @brief Multiboot2 loader name information

  struct loader_name_information
  {
    information_type type;
    std::uint32_t    size;

    char name [];
  };

  //! @brief Multiboot2 modules information

  struct modules_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint32_t start;
    std::uint32_t end;
    char          command [];
  };

  //! @brief Multiboot2 basic memory information

  struct basic_memory_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint32_t lower;
    std::uint32_t upper;
  };

  //! @brief Multiboot2 boot device information

  struct boot_device_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint32_t device;
    std::uint32_t partition;
    std::uint32_t sub_partition;
  };

  //! @brief Multiboot2 memory map information

  struct memory_map_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint32_t entry_size;
    std::uint32_t entry_version;
  };

  //! @brief Multiboot2 ELF symbols information

  struct elf_symbols_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint16_t num;
    std::uint16_t entsize;
    std::uint16_t shndx;
    std::uint16_t reserved;
  };

  //! @brief Multiboot2 APM information

  struct apm_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint16_t version;
    std::uint16_t cseg;
    std::uint16_t offset;
    std::uint16_t cseg_16;
    std::uint16_t dseg;
    std::uint16_t flags;
    std::uint16_t cseg_len;
    std::uint16_t cseg_16_len;
    std::uint16_t dseg_len;
  };

  //! @brief Multiboot2 VBE information

  struct vbe_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint16_t mode;
    std::uint16_t interface_seg;
    std::uint16_t interface_off;
    std::uint16_t interface_len;
    std::uint16_t control_info;
    std::uint16_t mode_info;
  };

  //! @brief Multiboot2 framebuffer information

  struct framebuffer_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint64_t address;
    std::uint32_t pitch;
    std::uint32_t width;
    std::uint32_t height;
    std::uint8_t  bpp;
    std::uint32_t framebuffer_type;
    std::uint8_t  reserved;
  };

  //! @brief Multiboot2 EFI32 information

  struct efi32_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint32_t pointer;
  };

  //! @brief Multiboot2 EFI64 information

  struct efi64_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint64_t pointer;
  };

  //! @brief Multiboot2 SMBIOS information

  struct smbios_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint8_t major;
    std::uint8_t minor;
    std::uint8_t reserved [6];
    std::uint8_t tables   [];
  };

  //! @brief Multiboot2 ACPI information

  struct acpi_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint8_t rsdp [];
  };

  //! @brief Multiboot2 network information

  struct network_information
  {
    information_type type;
    std::uint32_t    size;

    std::uint8_t dhcpack [];
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
      std::uint32_t    size;
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
