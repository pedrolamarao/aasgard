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

  enum class msr : std::uint32_t
  {
    IA32_APIC_BASE   = 0x1B,
    IA32_MISC_ENABLE = 0x1A0
  };

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (std::uint32_t id) -> std::uint64_t ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (std::uint32_t id, std::uint32_t value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (std::uint32_t id, std::uint64_t value);

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (msr id) -> std::uint64_t ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, std::uint32_t value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, std::uint64_t value);

}

//! Inline definitions

namespace x86
{

  namespace internal
  {
    void read_msr ( std::uint32_t id, std::uint32_t & low, std::uint32_t & high )
    {
        asm volatile ("rdmsr" : "=a"(low), "=d"(high) : "c"(id));
    }

    void write_msr ( std::uint32_t id, std::uint32_t low, std::uint32_t high )
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
  auto read_msr (std::uint32_t id) -> std::uint64_t
  {
      std::uint32_t low, high;
      internal::read_msr(id, low, high);
      return (std::uint64_t{high} << 32) | low;
  }

  inline
  void write_msr (std::uint32_t id, std::uint32_t value)
  {
      internal::write_msr(id, value, 0);
  }

  inline
  void write_msr (std::uint32_t id, std::uint64_t value)
  {
      std::uint32_t low = value & 0xFFFFFFFF;
      std::uint32_t high = value >> 32;
      internal::write_msr(id, low, high);
  }

  inline
  auto read_msr (msr id) -> std::uint64_t
  {
    return read_msr((std::uint32_t)(id));
  }

  inline
  void write_msr (msr id, std::uint32_t value)
  {
    write_msr((std::uint32_t)(id), value);
  }

  inline
  void write_msr (msr id, std::uint64_t value)
  {
    write_msr((std::uint32_t)(id), value);
  }

}
