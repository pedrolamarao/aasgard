// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


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
    interrupt_gate_descriptor ( ps::size2 segment, ps::size4 address, ps::size1 access );

    interrupt_gate_descriptor ( ps::size2 segment, void (* address) (), ps::size1 access );

    auto offset_lower () const { return _offset_lower; }

    auto segment () const { return _segment; }

    auto unused () const { return _unused; }

    auto type () const { return _type; }

    auto offset_upper () const { return _offset_upper; }

  private:

    ps::size2 _offset_lower;
    ps::size2 _segment;
    ps::size1  _unused;
    ps::size1  _type;
    ps::size2 _offset_upper;

  };

  static_assert(sizeof(interrupt_gate_descriptor) == 8, "unexpected size of interrupt_gate_descriptor");

  //! Computes access field for interrupt gate descriptors

  constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege, bool is_present ) -> ps::size1 ;

  //! Computes access field for interrupt gate descriptors

  constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege ) -> ps::size1 ;

  //! Loads the interrupt descriptor table register

  void load_interrupt_descriptor_table ( interrupt_gate_descriptor const * table, ps::size4 count );

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
    void __load_interrupt_descriptor_table ( ps::size4 base, ps::size2 limit );

    extern "C"
    void __store_interrupt_descriptor_table ( ps::size8 & gdtr );

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
  interrupt_gate_descriptor::interrupt_gate_descriptor ( ps::size2 segment, ps::size4 address, ps::size1 access ) :
    _offset_lower(address & 0xFFFF),
    _segment(segment),
    _unused(0),
    _type(access),
    _offset_upper(address >> 16)
  {

  }

  inline
  interrupt_gate_descriptor::interrupt_gate_descriptor ( ps::size2 segment, void (* address) (), ps::size1 access ) :
    _offset_lower((ps::size4)(address) & 0xFFFF),
    _segment(segment),
    _unused(0),
    _type(access),
    _offset_upper((ps::size4)(address) >> 16)
  {

  }

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege, bool is_present ) -> ps::size1
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
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege ) -> ps::size1
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
  ps::size8 get_interrupt_descriptor_table ()
  {
      ps::size8 result;
      internal::__store_interrupt_descriptor_table(result);
      return result;
  }

  inline
  void set_interrupt_descriptor_table ( interrupt_gate_descriptor const * table, ps::size4 count )
  {
    internal::__load_interrupt_descriptor_table(ps::size4(table), count * sizeof(interrupt_gate_descriptor));
  }

  template <unsigned N>
  inline
  void set_interrupt_descriptor_table ( interrupt_gate_descriptor const (& table) [N] )
  {
    internal::__load_interrupt_descriptor_table(ps::size4(table), N * sizeof(interrupt_gate_descriptor));
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

  template <int N>
  inline
  void interrupt ()
  {
      __asm__ ("int %0\n" : : "N"(N) : "cc", "memory");
  }
}
