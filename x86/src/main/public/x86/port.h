// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>

//! @brief Declarations

namespace x86
{
  //! @brief I/O port

  template <typename I>
  class port
  {
  public:

    std::uint16_t const address;

    //! @brief Constructor for port at address
    //!
    //! @param address  port address

    constexpr explicit port (std::uint16_t address);

    //! @brief Read from port

    auto read () -> I;

    //! @brief Write to port
    //!
    //! @param value  value to write

    void write (I value);
  };
}


#include <cstdint>


//! @brief Inline definitions

namespace x86
{
  namespace internal
  {
    inline void __port_read (std::uint16_t port, std::uint8_t & value) { asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port) ); }
    inline void __port_read (std::uint16_t port, std::uint16_t & value) { asm volatile ("inw %1, %0" : "=a"(value) : "Nd"(port) ); }
    inline void __port_read (std::uint16_t port, std::uint32_t & value) { asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port) ); }
    inline void __port_write (std::uint16_t port, std::uint8_t value) { asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port) ); }
    inline void __port_write (std::uint16_t port, std::uint16_t value) { asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port) ); }
    inline void __port_write (std::uint16_t port, std::uint32_t value) { asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port) ); }
  }


  template <typename I>
  constexpr
  port<I>::port (std::uint16_t a) : address(a)
  { }

  template <typename I>
  auto port<I>::read () -> I
  {
    I value;
    internal::__port_read(address, value);
    return value;
  }

  template <typename I>
  void port<I>::write (I value)
  {
    internal::__port_write(address, value);
  }
}
