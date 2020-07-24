// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace x86
{
  //! True if cpuid is supported

  auto has_cpuid () -> bool ;

  //! CPU identification information

  class cpuid
  {
  public:

    constexpr
    cpuid () ;

    //! @pre has_cpuid()
    //! @pre id <= cpuid(0).a()

    cpuid (ps::size4 id, ps::size4 extra) ;

    //! @pre has_cpuid()
    //! @pre id <= cpuid(0).a()

    cpuid (ps::size4 id) ;

    constexpr
    auto a () const -> ps::size4 ;

    constexpr
    auto b () const -> ps::size4 ;

    constexpr
    auto c () const -> ps::size4 ;

    constexpr
    auto d () const -> ps::size4 ;

  private:

    ps::size4 eax;
    ps::size4 ebx;
    ps::size4 ecx;
    ps::size4 edx;

  };

  class cpuid_1
  {
      cpuid _cpuid;

  public:

      //! @brief Object
      //! @{

      cpuid_1 ();

      //! @}

      //! @brief Properties
      //! @{

      auto has_local_apic () const -> bool;

      auto has_msr () const -> bool;

      //! @}

  };
}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
	[[gnu::fastcall]]
    bool __has_cpuid ();

    extern "C"
	[[gnu::fastcall]]
    void __read_cpuid (ps::size4 leaf, ps::size4 extra, cpuid & out);

  }

  inline
  auto has_cpuid () -> bool
  {
    return internal::__has_cpuid();
  }

  inline constexpr
  cpuid::cpuid () : eax(), ebx(), ecx(), edx()
  {

  }

  inline
  cpuid::cpuid (ps::size4 id, ps::size4 extra) : eax(0), ebx(0), ecx(0), edx(0)
  {
    internal::__read_cpuid(id, extra, (* this));
  }

  inline
  cpuid::cpuid (ps::size4 id) : cpuid(id, 0)
  {

  }

  inline constexpr
  auto cpuid::a () const -> ps::size4
  {
    return eax;
  }

  inline constexpr
  auto cpuid::b () const -> ps::size4
  {
    return ebx;
  }

  inline constexpr
  auto cpuid::c () const -> ps::size4
  {
    return ecx;
  }

  inline constexpr
  auto cpuid::d () const -> ps::size4
  {
    return edx;
  }

  inline
  cpuid_1::cpuid_1 () : _cpuid { 1 } { }

  inline
  auto cpuid_1::has_local_apic () const -> bool
  {
      return (_cpuid.d() & (1 << 11)) != 0;
  }

  inline
  auto cpuid_1::has_msr () const -> bool
  {
      return (_cpuid.d() & (1 << 5)) != 0;
  }
}
