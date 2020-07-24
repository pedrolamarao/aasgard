#pragma once

#include <x86/cpuid.h>

//! Declarations

namespace x86
{

  //! True if model specific registers are supported
  //! @pre x = cpuid(1)

  constexpr
  auto has_msr (cpuid x) -> bool ;

  //! True if model specific registers are supported
  //! @pre has_cpuid()

  auto has_msr () -> bool ;

  //! Model specific registers

  enum class msr : ps::size4
  {
    IA32_APIC_BASE   = 0x1B,
    IA32_MISC_ENABLE = 0x1A0
  };

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (ps::size4 id) -> ps::size8 ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (ps::size4 id, ps::size4 value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (ps::size4 id, ps::size8 value);

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (msr id) -> ps::size8 ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, ps::size4 value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, ps::size8 value);

}

//! Inline definitions

namespace x86
{

  namespace internal
  {
    void read_msr ( ps::size4 id, ps::size4 & low, ps::size4 & high )
    {
        asm volatile ("rdmsr" : "=a"(low), "=d"(high) : "c"(id));
    }

    void write_msr ( ps::size4 id, ps::size4 low, ps::size4 high )
    {
        asm volatile ("wrmsr" : : "a"(low), "d"(high), "c"(id));
    }
  }

  inline constexpr
  auto has_msr (cpuid x) -> bool
  {
    return (x.d() & 0b10000) != 0 ;
  }

  inline
  auto has_msr () -> bool
  {
    return has_msr(cpuid(1));
  }

  inline
  auto read_msr (ps::size4 id) -> ps::size8
  {
      ps::size4 low, high;
      internal::read_msr(id, low, high);
      return (ps::size8{high} << 32) | low;
  }

  inline
  void write_msr (ps::size4 id, ps::size4 value)
  {
      internal::write_msr(id, value, 0);
  }

  inline
  void write_msr (ps::size4 id, ps::size8 value)
  {
      ps::size4 low = value & 0xFFFFFFFF;
      ps::size4 high = value >> 32;
      internal::write_msr(id, low, high);
  }

  inline
  auto read_msr (msr id) -> ps::size8
  {
    return read_msr((ps::size4)(id));
  }

  inline
  void write_msr (msr id, ps::size4 value)
  {
    write_msr((ps::size4)(id), value);
  }

  inline
  void write_msr (msr id, ps::size8 value)
  {
    write_msr((ps::size4)(id), value);
  }

}
