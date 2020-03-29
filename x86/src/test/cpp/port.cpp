#include <x86/port.h>

#include <gtest/gtest.h>

namespace
{
    TEST(port, smoke)
    {
        x86::port<std::uint8_t> port8 { 0x00 };
        x86::port<std::uint16_t> port16 { 0x00 };
        x86::port<std::uint32_t> port32 { 0x00 };
    }
}
