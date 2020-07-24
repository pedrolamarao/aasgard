// Copyright (C) 2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/cpuid.h>


namespace x86
{
	struct apic_location
	{
		ps::size4 value;
		ps::size4 unused0;
		ps::size4 unused1;
		ps::size4 unused2;
	};

	struct apic_r_location : public apic_location
	{
		constexpr explicit operator ps::size4 () const { return value; }
	};

	struct apic_w_location : public apic_location
	{
		auto operator= (ps::size4 x) -> apic_w_location & { value = x; return *this; }
	};

	struct apic_rw_location : public apic_location
	{
		constexpr explicit operator ps::size4 () const { return value; }

		auto operator= (ps::size4 x) -> apic_rw_location & { value = x; return *this; }
	};

	struct apic_memory_map
	{
		apic_location reserved_00;
		apic_location reserved_01;
		apic_r_location id;
		apic_r_location version;
		apic_location reserved_02;
		apic_location reserved_03;
		apic_location reserved_04;
		apic_location reserved_05;
		apic_location task_priority;
		apic_location arbitration_priority;
		apic_location processor_priority;
		apic_location eoi;
		apic_location remote_read;
		apic_location logical_destination;
		apic_location destination_format;
		apic_location spurious_interrupt_vector;
	};

	constexpr inline
	auto has_apic (cpuid const &) -> bool
	{
		return false;
	}

	constexpr inline
	auto is_apic_enabled (ps::size8 location) -> bool
	{
		return false;
	}

	constexpr inline
	auto get_apic_memory_map (ps::size8 location) -> apic_memory_map *
	{
		return nullptr;
	}
}
