// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>

namespace pc
{
    //! @brief RTC status A

    class rtc_status_a
    {
        const std::uint8_t _value;

    public:

        constexpr
        rtc_status_a (std::uint8_t value) :
            _value { value }
        {
        }

        constexpr
        bool update_in_progress () const
        {
            return (_value & 0x80) != 0;
        }

        constexpr
        std::uint8_t frequency_divider () const
        {
            return (_value & 0x70) >> 4;
        }

        constexpr
        std::uint8_t rate_frequency () const
        {
            return (_value & 0x0F);
        }
    };

    //! @brief RTC status B

    class rtc_status_b
    {
        const std::uint8_t _value;

    public:

        constexpr
        rtc_status_b (std::uint8_t value) :
            _value { value }
        {
        }

        constexpr
        bool abort_in_progress () const
        {
            return (_value & 0x80) != 0;
        }

        constexpr
        bool periodic_interrupt () const
        {
            return (_value & 0x40) != 0;
        }

        constexpr
        bool alarm_interrupt () const
        {
            return (_value & 0x20) != 0;
        }

        constexpr
        bool update_interrupt () const
        {
            return (_value & 0x10) != 0;
        }

        constexpr
        bool square_wave () const
        {
            return (_value & 0x08) != 0;
        }

        constexpr
        bool binary_data () const
        {
            return (_value & 0x04) != 0;
        }

        constexpr
        bool hour_mode () const
        {
            return (_value & 0x02) != 0;
        }

        constexpr
        bool daylight_mode () const
        {
            return (_value & 0x01) != 0;
        }
    };

    //! @brief CMOS controller interface

    template <template <typename Value> typename Port>
    class cmos
    {
        Port<std::uint8_t> _command;
        Port<std::uint8_t> _data;

    public:

        //! @brief Object
        //! @{

        cmos () : _command { 0x70 }, _data { 0x71 } { }

        //! @}

        //! @brief CMOS Registers
        //! @{

        std::uint8_t read (std::uint8_t index, bool nmi)
        {
            _command.write((nmi ? 0x80 : 0) | (index & 0x7F));
            // #XXX: wait? how?
            return _data.read();
        }

        void write (std::uint8_t index, bool nmi, std::uint8_t value)
        {
            _command.write((nmi ? 0x80 : 0) | (index & 0x7F));
            // #XXX: wait? how?
            _data.write(value & 0x7F);
        }

        //! @}
    };
}
