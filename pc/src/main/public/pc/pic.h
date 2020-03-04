// Copyright (C) 2020, 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


namespace pc
{
    enum class pic_buffering : std::uint8_t
    {
        none   = 0,
        slave  = 0x08,
        master = 0x0C,
    };

    enum class pic_read : std::uint8_t
    {
        ignore = 0,
        ir     = 2,
        is     = 3,
    };

    enum class pic_mask : std::uint8_t
    {
        ignore = 0,
        unset  = 0x20,
        set    = 0x30,
    };

    //! @brief PIC controller

    template <template <typename Value> typename Port>
    class pic
    {
    public:

        Port<std::uint8_t> _command;
        Port<std::uint8_t> _data;

    public:

        //! @brief Object
        //! @{

        constexpr
        pic (std::uint16_t base) : _command { base }, _data { std::uint8_t( base + 1 ) } {}

        static constexpr
        auto master () { return pic{0x20}; }

        static constexpr
        auto slave () { return pic{0xA0}; }

        //! @}

        //! @brief Initialization
        //! @{

        //! @brief Initialization command word 1 (ICW1) — initialize

        void icw1 (bool icw4, bool single, bool level)
        {
            std::uint8_t value = (icw4 ? 1 : 0) | (single ? 2 : 0) | (level ? 8 : 0) | 16;
            _command.write(value);
        }

        //! @brief Initialization command word 2 (ICW2) — interrupt offset

        void icw2 (std::uint8_t offset)
        {
            _data.write(offset);
        }

        //! @brief Initialization command word 3 (ICW3) — slave lines

        void icw3_master (std::uint8_t slaves)
        {
            _data.write(slaves);
        }

        //! @brief Initialization command word 3 (ICW3) — slave id

        void icw3_slave (std::uint8_t id)
        {
            std::uint8_t value = (id & 7);
            _data.write(value);
        }

        //! @brief Initialization command word 4 (ICW4) — miscellaneous

        void icw4 (bool x86, bool aeoi, pic_buffering buffering, bool sfnm)
        {
            std::uint8_t value = (x86 ? 1 : 0) | (aeoi ? 2 : 0) | (std::uint8_t(buffering) & 0x0C) | (sfnm ? 16 : 0);
            _data.write(value);
        }

        //! @}

        //! @brief Operation
        //! @{

        //! @brief Operational command word 1 (OCW1) — interrupt masking

        void ocw1 (std::uint8_t mask)
        {
            _data.write(mask);
        }

        //! @brief Operational command word 2 (OCW2) — end of interrupt

        void ocw2 (std::uint8_t level, bool eoi, bool specific, bool rotate)
        {
            std::uint8_t value = (level & 0x07) | (eoi ? 8 : 0) | (specific ? 16 : 0) | (rotate ? 32 : 0);
            _command.write(value);
        }

        //! @brief Operational command word 3 (OCW3) — register access

        void ocw3 (pic_read read, bool poll, pic_mask mask)
        {
            std::uint8_t value = (std::uint8_t(read) & 0x03) | (poll ? 4 : 0) | 8 | (std::uint8_t(mask) & 0x30);
            _command.write(value);
        }

        //! @}

        //! @brief Properties
        //! @{

        std::uint8_t in_service ()
        {
            ocw3(pic_read::is, true, pic_mask::ignore);
            // #XXX: wait? how?
            return _command.read();
        }

        std::uint8_t mask ()
        {
            return _data.read();
        }

        void mask (std::uint8_t value)
        {
            _data.write(value);
        }

        //! @}
    };
}
