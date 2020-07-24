// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace x86
{

  //! Segment selector

  class segment_selector
  {
  public:

    constexpr
    segment_selector ( ps::size2 index, bool is_ldt, ps::size1 privilege );

  private:

    friend void reload_segment_registers (segment_selector, segment_selector);

    ps::size2 word;

  };

  static_assert(sizeof(segment_selector) == 2, "unexpected size of segment_selector");


  //! Segment descriptor
  //!
  //! Element of global and local descriptor tables.

  class segment_descriptor
  {
  public:

    constexpr
    segment_descriptor () ;

    constexpr
    segment_descriptor ( ps::size4 base, ps::size4 limit, ps::size1 access, ps::size1 granularity ) ;

  private:

    ps::size2 _limit_lower;
    ps::size2 _base_lower;
    ps::size1  _base_middle;
    ps::size1  _access;
    ps::size1  _granularity;
    ps::size1  _base_upper;

  };

  static_assert(sizeof(segment_descriptor) == 8, "unexpected size of segment descriptor");


  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege, bool present ) -> ps::size1 ;

  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //!
  //! @post data_segment_access(true, may_write, expand_down, privilege, true)

  constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege ) -> ps::size1 ;

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  constexpr
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege, bool present ) -> ps::size1 ;

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //!
  //! @post code_segment_access(true, may_read, conforming, privilege, true)

  constexpr
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege ) -> ps::size1 ;

  //! Computes granularity field for code or data segments
  //!
  //! @param is_long      true if 64-bit addressing
  //! @param is_32bit     true if 32-bit addressing
  //! @param is_4kb       true if limit unit is 4kb
  //!
  //! @post segment_granularity(0, false, is_long, is_32bit, is_4kb)

  constexpr
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> ps::size1 ;

  //! Loads the global descriptor table register
  //!
  //! @param table  array of descriptors
  //! @param count  count of descriptors in array

  void load_global_descriptor_table ( segment_descriptor * table, ps::size2 count );

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

  void reload_segment_registers ( ps::size2 code, ps::size2 data );

}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
	[[gnu::fastcall]]
    void __load_global_descriptor_table ( ps::size4 base, ps::size2 size );

    extern "C"
    void __store_global_descriptor_table ( ps::size8 & gdtr );

    extern "C"
	[[gnu::fastcall]]
    void __reload_segment_registers ( ps::size4 code, ps::size4 data );

  }

  inline constexpr
  segment_selector::segment_selector (ps::size2 index, bool is_ldt, ps::size1 privilege) :
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
  segment_descriptor::segment_descriptor ( ps::size4 base, ps::size4 limit, ps::size1 access, ps::size1 granularity ) :
    _limit_lower(limit & 0xFFFF),
    _base_lower(base & 0xFFFF),
    _base_middle((base >> 16) & 0xFF),
    _access(access),
    _granularity((granularity & 0xFFF0) | (limit & 0xF)),
    _base_upper((base >> 24) & 0xFF)
  {

  }

  inline constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege, bool present ) -> ps::size1
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
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege ) -> ps::size1
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
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege, bool present ) -> ps::size1
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
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege ) -> ps::size1
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
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> ps::size1
  {
    return (is_4kb ? 0x01 : 0x00) << 7
         | (is_32bit ? 0x01 : 0x00) << 6
         | (is_long ? 0x01 : 0x00) << 5
         | (0)
         ;
  }

  inline
  ps::size8 get_global_descriptor_table ()
  {
      ps::size8 result;
      internal::__store_global_descriptor_table(result);
      return result;
  }

  inline
  void set_global_descriptor_table ( segment_descriptor const * table, ps::size2 count )
  {
    internal::__load_global_descriptor_table(ps::size4(table), ((count * sizeof(segment_descriptor)) - 1));
  }

  template <unsigned N>
  inline
  void set_global_descriptor_table ( segment_descriptor const (& table) [N] )
  {
    internal::__load_global_descriptor_table(ps::size4(table), ((N * sizeof(segment_descriptor)) - 1));
  }

  inline
  void reload_segment_registers ( segment_selector code, segment_selector data )
  {
    internal::__reload_segment_registers(code.word, data.word);
  }

}
