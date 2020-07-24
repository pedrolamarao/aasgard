// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

//! @brief Declarations

namespace x86
{
  //! @brief I/O port

  template <typename I>
  class port
  {
  public:

    ps::size2 const address;

    //! @brief Constructor for port at address
    //!
    //! @param address  port address

    constexpr explicit port (ps::size2 address);

    //! @brief Read from port

    auto read () -> I;

    //! @brief Write to port
    //!
    //! @param value  value to write

    void write (I value);
  };
}


//! @brief Inline definitions

namespace x86
{
  namespace internal
  {
    inline void __port_read (ps::size2 port, ps::size1 & value) { asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port) ); }
    inline void __port_read (ps::size2 port, ps::size2 & value) { asm volatile ("inw %1, %0" : "=a"(value) : "Nd"(port) ); }
    inline void __port_read (ps::size2 port, ps::size4 & value) { asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port) ); }
    inline void __port_write (ps::size2 port, ps::size1 value) { asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port) ); }
    inline void __port_write (ps::size2 port, ps::size2 value) { asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port) ); }
    inline void __port_write (ps::size2 port, ps::size4 value) { asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port) ); }
  }


  template <typename I>
  constexpr
  port<I>::port (ps::size2 a) : address(a)
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
