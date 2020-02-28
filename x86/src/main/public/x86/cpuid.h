// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


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

    cpuid (std::uint32_t id, std::uint32_t extra) ;

    //! @pre has_cpuid()
    //! @pre id <= cpuid(0).a()

    cpuid (std::uint32_t id) ;

    constexpr
    auto a () -> std::uint32_t ;

    constexpr
    auto b () -> std::uint32_t ;

    constexpr
    auto c () -> std::uint32_t ;

    constexpr
    auto d () -> std::uint32_t ;

  private:

    std::uint32_t eax;
    std::uint32_t ebx;
    std::uint32_t ecx;
    std::uint32_t edx;

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
    void __read_cpuid (std::uint32_t leaf, std::uint32_t extra, cpuid & out);

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
  cpuid::cpuid (std::uint32_t id, std::uint32_t extra) : eax(0), ebx(0), ecx(0), edx(0)
  {
    internal::__read_cpuid(id, extra, (* this));
  }

  inline
  cpuid::cpuid (std::uint32_t id) : cpuid(id, 0)
  {

  }

  inline constexpr
  auto cpuid::a () -> std::uint32_t
  {
    return eax;
  }

  inline constexpr
  auto cpuid::b () -> std::uint32_t
  {
    return ebx;
  }

  inline constexpr
  auto cpuid::c () -> std::uint32_t
  {
    return ecx;
  }

  inline constexpr
  auto cpuid::d () -> std::uint32_t
  {
    return edx;
  }

}
