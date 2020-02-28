// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


//! Declarations

namespace x86
{

  //! Segment selector

  class segment_selector
  {
  public:

    constexpr
    segment_selector ( std::uint16_t index, bool is_ldt, std::uint8_t privilege );

  private:

    friend void reload_segment_registers (segment_selector, segment_selector);

    std::uint16_t word;

  };

  static_assert(sizeof(segment_selector) == 2, "unexpected size of segment_selector");


  //! Segment descriptor
  //!
  //! Element of global and local descriptor tables.

  [[gnu::packed]]
  class segment_descriptor
  {
  public:

    constexpr
    segment_descriptor () ;

    constexpr
    segment_descriptor ( std::uint32_t base, std::uint32_t limit, std::uint8_t access, std::uint8_t granularity ) ;

  private:

    std::uint16_t _limit_lower;
    std::uint16_t _base_lower;
    std::uint8_t  _base_middle;
    std::uint8_t  _access;
    std::uint8_t  _granularity;
    std::uint8_t  _base_upper;

  };

  static_assert(sizeof(segment_descriptor) == 8, "unexpected size of segment descriptor");


  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  constexpr
  auto data_segment_access ( bool may_write, bool expand_down, std::uint8_t privilege, bool present ) -> std::uint8_t ;

  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //!
  //! @post data_segment_access(true, may_write, expand_down, privilege, true)

  constexpr
  auto data_segment_access ( bool may_write, bool expand_down, std::uint8_t privilege ) -> std::uint8_t ;

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  constexpr
  auto code_segment_access ( bool may_read, bool conforming, std::uint8_t privilege, bool present ) -> std::uint8_t ;

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //!
  //! @post code_segment_access(true, may_read, conforming, privilege, true)

  constexpr
  auto code_segment_access ( bool may_read, bool conforming, std::uint8_t privilege ) -> std::uint8_t ;

  //! Computes granularity field for code or data segments
  //!
  //! @param is_long      true if 64-bit addressing
  //! @param is_32bit     true if 32-bit addressing
  //! @param is_4kb       true if limit unit is 4kb
  //!
  //! @post segment_granularity(0, false, is_long, is_32bit, is_4kb)

  constexpr
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> std::uint8_t ;

  //! Loads the global descriptor table register
  //!
  //! @param table  array of descriptors
  //! @param count  count of descriptors in array

  void load_global_descriptor_table ( segment_descriptor * table, std::uint16_t count );

  //! Loads the global descriptor table register
  //!
  //! @param table  array of descriptors

  template <unsigned N>
  void load_global_descriptor_table ( segment_descriptor const (& table) [N] );

  //! Loads segment registers with new selectors
  //!
  //! @param code  index of descriptor on global descriptor table
  //! @param data  index of descriptor on global descriptor table
  //!
  //! @post load code in CD then data in DS, ES, FS, GS and SS

  void reload_segment_registers ( std::uint16_t code, std::uint16_t data );

}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
	[[gnu::fastcall]]
    void __load_global_descriptor_table ( std::uint32_t base, std::uint16_t size );

    extern "C"
	[[gnu::fastcall]]
    void __store_global_descriptor_table ( std::uint64_t & gdtr );

    extern "C"
	[[gnu::fastcall]]
    void __reload_segment_registers ( std::uint32_t code, std::uint32_t data );

  }

  inline constexpr
  segment_selector::segment_selector (std::uint16_t index, bool is_ldt, std::uint8_t privilege) :
    word((index << 3) | ((is_ldt ? 1 : 0) << 2) | (privilege & 3))
  { }

  inline constexpr
  segment_descriptor::segment_descriptor ( ) :
    _limit_lower(0),
    _base_lower(0),
    _base_middle(0),
    _access(0),
    _granularity(0),
    _base_upper(0)
  { }

  inline constexpr
  segment_descriptor::segment_descriptor ( std::uint32_t base, std::uint32_t limit, std::uint8_t access, std::uint8_t granularity ) :
    _limit_lower(limit & 0xFFFF),
    _base_lower(base & 0xFFFF),
    _base_middle((base >> 16) & 0xFF),
    _access(access),
    _granularity((granularity & 0xFFF0) | (limit & 0xF)),
    _base_upper((base >> 24) & 0xFF)
  {

  }

  inline constexpr
  auto data_segment_access ( bool may_write, bool expand_down, std::uint8_t privilege, bool present ) -> std::uint8_t
  {
    return (present ? 0x01 : 0x00) << 7
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x00) << 3
         | (expand_down ? 0x01 : 0x00) << 2
         | (may_write ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto data_segment_access ( bool may_write, bool expand_down, std::uint8_t privilege ) -> std::uint8_t
  {
    return (1 << 7)
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x00) << 3
         | (expand_down ? 0x01 : 0x00) << 2
         | (may_write ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto code_segment_access ( bool may_read, bool conforming, std::uint8_t privilege, bool present ) -> std::uint8_t
  {
    return (present ? 0x01 : 0x00) << 7
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x01) << 3
         | (conforming ? 0x01 : 0x00) << 2
         | (may_read ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto code_segment_access ( bool may_read, bool conforming, std::uint8_t privilege ) -> std::uint8_t
  {
    return (1 << 7)
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x01) << 3
         | (conforming ? 0x01 : 0x00) << 2
         | (may_read ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> std::uint8_t
  {
    return (is_4kb ? 0x01 : 0x00) << 7
         | (is_32bit ? 0x01 : 0x00) << 6
         | (is_long ? 0x01 : 0x00) << 5
         | (0)
         ;
  }

  inline
  void load_global_descriptor_table ( segment_descriptor const * table, std::uint16_t count )
  {
    internal::__load_global_descriptor_table(std::uint32_t(table), ((count * sizeof(segment_descriptor)) - 1));
  }

  template <unsigned N>
  inline
  void load_global_descriptor_table ( segment_descriptor const (& table) [N] )
  {
    internal::__load_global_descriptor_table(std::uint32_t(table), ((N * sizeof(segment_descriptor)) - 1));
  }

  inline
  void reload_segment_registers ( segment_selector code, segment_selector data )
  {
    internal::__reload_segment_registers(code.word, data.word);
  }

}
