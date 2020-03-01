// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


//! Declarations

namespace x86
{
  //! Interrupt gate descriptor
  //!
  //! Element of interrupt descriptor tables.

  class interrupt_gate_descriptor
  {
  public:

    constexpr
    interrupt_gate_descriptor ();

    constexpr
    interrupt_gate_descriptor ( std::uint16_t segment, std::uint32_t address, std::uint8_t access );

    constexpr
    interrupt_gate_descriptor ( std::uint16_t segment, void (* address) (), std::uint8_t access );

  private:

    std::uint16_t _offset_lower;
    std::uint16_t _segment;
    std::uint8_t  _unused;
    std::uint8_t  _type;
    std::uint16_t _offset_upper;

  };

  static_assert(sizeof(interrupt_gate_descriptor) == 8, "unexpected size of interrupt_gate_descriptor");

  //! Computes access field for interrupt gate descriptors

  constexpr
  auto interrupt_gate_access ( bool is_32bit, std::uint8_t privilege, bool is_present ) -> std::uint8_t ;

  //! Computes access field for interrupt gate descriptors

  constexpr
  auto interrupt_gate_access ( bool is_32bit, std::uint8_t privilege ) -> std::uint8_t ;

  //! Loads the interrupt descriptor table register

  void load_interrupt_descriptor_table ( interrupt_gate_descriptor const * table, std::uint32_t count );

  template <unsigned N>
  void load_interrupt_descriptor_table ( interrupt_gate_descriptor const (& table) [N] );

  //! Enable interrupts on this processor

  void enable_interrupts ();

  //! Disables interrupts on this processor

  void disable_interrupts ();

}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
    [[gnu::fastcall]]
    void __load_interrupt_descriptor_table ( std::uint32_t base, std::uint16_t limit );

    extern "C"
    void __store_interrupt_descriptor_table ( std::uint64_t & gdtr );

    extern "C"
    [[gnu::fastcall]]
    void __enable_interrupts ();

    extern "C"
    [[gnu::fastcall]]
    void __disable_interrupts ();

  }

  inline constexpr
  interrupt_gate_descriptor::interrupt_gate_descriptor () :
    _offset_lower(0),
    _segment(0),
    _unused(0),
    _type(0),
    _offset_upper(0)
  { }

  inline constexpr
  interrupt_gate_descriptor::interrupt_gate_descriptor ( std::uint16_t segment, std::uint32_t address, std::uint8_t access ) :
    _offset_lower(address & 0xFFFF),
    _segment(segment),
    _unused(0),
    _type(access),
    _offset_upper(address >> 16)
  {

  }

  inline constexpr
  interrupt_gate_descriptor::interrupt_gate_descriptor ( std::uint16_t segment, void (* address) (), std::uint8_t access ) :
    _offset_lower((std::uint32_t)(address) & 0xFFFF),
    _segment(segment),
    _unused(0),
    _type(access),
    _offset_upper((std::uint32_t)(address) >> 16)
  {

  }

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, std::uint8_t privilege, bool is_present ) -> std::uint8_t
  {
    return ((is_present ? 1 : 0) << 7)
         | (privilege << 5)
         | (0 << 4)
         | ((is_32bit ? 1 : 0) << 3)
         | (1 << 2)
         | (1 << 1)
         | (0)
         ;
  }

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, std::uint8_t privilege ) -> std::uint8_t
  {
    return (1 << 7)
         | (privilege << 5)
         | (0 << 4)
         | ((is_32bit ? 1 : 0) << 3)
         | (1 << 2)
         | (1 << 1)
         | (0)
         ;
  }

  inline
  std::uint64_t get_interrupt_descriptor_table ()
  {
      std::uint64_t result;
      internal::__store_interrupt_descriptor_table(result);
      return result;
  }

  inline
  void set_interrupt_descriptor_table ( interrupt_gate_descriptor const * table, std::uint32_t count )
  {
    internal::__load_interrupt_descriptor_table(std::uint32_t(table), count * sizeof(interrupt_gate_descriptor));
  }

  template <unsigned N>
  inline
  void set_interrupt_descriptor_table ( interrupt_gate_descriptor const (& table) [N] )
  {
    internal::__load_interrupt_descriptor_table(std::uint32_t(table), N * sizeof(interrupt_gate_descriptor));
  }

  inline
  void enable_interrupts ()
  {
    internal::__enable_interrupts();
  }

  inline
  void disable_interrupts ()
  {
    internal::__disable_interrupts();
  }

}
