// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace acpi
{

  //! Root System Description Pointer

  struct root_system_description_pointer
  {
    // since revision 0
    char     signature [8];
    ps::size1  checksum;
    char     oem_id [6];
    ps::size1  revision;
    ps::size4 address;

    // since revision 1
    ps::size4 length;
    ps::size8 extended_address;
    ps::size1  extended_checksum;
    ps::size1  reserved [3];
  };

  constexpr
  auto revision ( root_system_description_pointer const & x ) -> ps::size1 ;

  auto is_valid ( root_system_description_pointer const & x ) -> bool ;

  struct narrow_root_system_description ;

  auto narrow_address ( root_system_description_pointer const & x) -> narrow_root_system_description const * ;

  struct wide_root_system_description ;

  auto wide_address ( root_system_description_pointer const & x ) -> wide_root_system_description const * ;

  //! System Description

  struct system_description
  {
    char     signature [4];
    ps::size4 length;
    ps::size1  revision;
    ps::size1  checksum;
    char     oem_id [6];
    char     oem_table_id [8];
    ps::size4 oem_revision;
    ps::size4 creator_id;
    ps::size4 creator_revision;
  };

  auto revision ( system_description const & x ) -> ps::size1 ;

  auto is_valid ( system_description const & x ) -> bool ;

  //! Root System Description with narrow pointers

  struct narrow_root_system_description
  {
    system_description header;

    ps::size4 pointers [];
  };

  auto is_valid ( narrow_root_system_description const & x ) -> bool ;

  auto begin ( narrow_root_system_description const & x ) -> ps::size4 const * ;

  auto end ( narrow_root_system_description const & x ) -> ps::size4 const * ;

  //! Root System Description with wide pointers

  struct wide_root_system_description
  {
    system_description header;

    ps::size8 pointers [];
  };

  auto is_valid ( wide_root_system_description const & x ) -> bool ;

  auto begin ( wide_root_system_description const & x ) -> ps::size8 const * ;

  auto end ( wide_root_system_description const & x ) -> ps::size8 const * ;

  //! Generic memory address

  struct generic_address
  {
    ps::size1  space;
    ps::size1  width;
    ps::size1  offset;
    ps::size1  access;
    ps::size8 address;
  };

  //! Fixed System Description

  struct fixed_system_description
  {
      system_description base;

      ps::size4 FirmwareCtrl;
      ps::size4 Dsdt;
      ps::size1  Reserved;
      ps::size1  PreferredPowerManagementProfile;
      ps::size2 SCI_Interrupt;
      ps::size4 SMI_CommandPort;
      ps::size1  AcpiEnable;
      ps::size1  AcpiDisable;
      ps::size1  S4BIOS_REQ;
      ps::size1  PSTATE_Control;
      ps::size4 PM1aEventBlock;
      ps::size4 PM1bEventBlock;
      ps::size4 PM1aControlBlock;
      ps::size4 PM1bControlBlock;
      ps::size4 PM2ControlBlock;
      ps::size4 PMTimerBlock;
      ps::size4 GPE0Block;
      ps::size4 GPE1Block;
      ps::size1  PM1EventLength;
      ps::size1  PM1ControlLength;
      ps::size1  PM2ControlLength;
      ps::size1  PMTimerLength;
      ps::size1  GPE0Length;
      ps::size1  GPE1Length;
      ps::size1  GPE1Base;
      ps::size1  CStateControl;
      ps::size2 WorstC2Latency;
      ps::size2 WorstC3Latency;
      ps::size2 FlushSize;
      ps::size2 FlushStride;
      ps::size1  DutyOffset;
      ps::size1  DutyWidth;
      ps::size1  DayAlarm;
      ps::size1  MonthAlarm;
      ps::size1  Century;

      // since ACPI 2.0

      ps::size2        BootArchitectureFlags;
      ps::size1         Reserved2;
      ps::size4        Flags;
      generic_address ResetReg;
      ps::size1         ResetValue;
      ps::size1         Reserved3[3];
      ps::size8        X_FirmwareControl;
      ps::size8        X_Dsdt;
      generic_address X_PM1aEventBlock;
      generic_address X_PM1bEventBlock;
      generic_address X_PM1aControlBlock;
      generic_address X_PM1bControlBlock;
      generic_address X_PM2ControlBlock;
      generic_address X_PMTimerBlock;
      generic_address X_GPE0Block;
      generic_address X_GPE1Block;
  };

  //! Multiple APIC system description

  struct apic_system_description
  {
    system_description base;

    ps::size4 local_apic_address;
    ps::size4 flags;
  };

  enum class apic_structure_type : ps::size1
  {
    local_apic             = 0,
    io_apic                = 1,
    input_source_override  = 2,
    non_maskable_interrupt = 3,
    local_apic_nmi         = 4
  };

  struct apic_description
  {
    ps::size1 type;
    ps::size1 length;
  };

  struct local_apic_description
  {
    apic_description base;

    ps::size1  processor;
    ps::size1  id;
    ps::size4 flags;
  };

  struct io_apic_description
  {
    apic_description base;

    ps::size1  id;
    ps::size1  reserved0;
    ps::size4 address;
    ps::size4 system_vector_base;
  };

  struct input_source_override_description
  {
    apic_description base;

    ps::size1  bus;
    ps::size1  source;
    ps::size4 global_system_interrupt_vector;
    ps::size2 flags;
  };

  struct nmi_source_description
  {
    apic_description base;

    ps::size2 flags;
    ps::size4 global_system_interrupt_vector;
  };

  struct local_apic_nmi_description
  {
    apic_description base;

    ps::size1  processor;
    ps::size2 flags;
    ps::size1  pin;
  };

}


//! Inline procedure definitions

namespace acpi
{
  inline constexpr
  auto revision ( root_system_description_pointer const & x ) -> ps::size1
  {
    return x.revision;
  }

  inline
  auto is_valid_r0 ( root_system_description_pointer const & x ) -> bool
  {
    ps::size1 sum = 0;
    ps::size1 const * i = (ps::size1 const *)(& x);
    ps::size1 const * e = i + 20;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid_r1 ( root_system_description_pointer const & x ) -> bool
  {
    ps::size1 sum = 0;
    ps::size1 const * i = (ps::size1 const *)(& x);
    ps::size1 const * e = i + 36;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid ( root_system_description_pointer const & x ) -> bool
  {
    if (revision(x) == 0) return is_valid_r0(x);
    else                  return is_valid_r1(x);
  }

  inline
  auto narrow_address ( root_system_description_pointer const & x) -> narrow_root_system_description const *
  {
    return (narrow_root_system_description const *)((char*){0} + x.address);
  }

  inline
  auto wide_address ( root_system_description_pointer const & x) -> wide_root_system_description const *
  {
    return (wide_root_system_description const *)(x.extended_address);
  }


  inline
  auto is_valid ( system_description const & x ) -> bool
  {
    ps::size1 sum = 0;
    ps::size1 const * i = (ps::size1 const *)(& x);
    ps::size1 const * e = i + x.length;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid ( narrow_root_system_description const & x ) -> bool
  {
    return is_valid(x.header);
  }

  inline
  auto is_valid ( wide_root_system_description const & x ) -> bool
  {
    return is_valid(x.header);
  }

  inline
  auto begin ( narrow_root_system_description const & x ) -> ps::size4 const *
  {
    return x.pointers;
  }

  inline
  auto end ( narrow_root_system_description const & x ) -> ps::size4 const *
  {
    auto const count = (x.header.length - sizeof(acpi::system_description)) / sizeof(ps::size4);
    return x.pointers + count;
  }

  inline
  auto begin ( wide_root_system_description const & x ) -> ps::size8 const *
  {
    return x.pointers;
  }

  inline
  auto end ( wide_root_system_description const & x ) -> ps::size8 const *
  {
    auto const count = (x.header.length - sizeof(acpi::system_description)) / sizeof(ps::size8);
    return x.pointers + count;
  }

}

