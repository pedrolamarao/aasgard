#include <multiboot2/header.h>

#include <gtest/gtest.h>

namespace
{
    TEST(header, checksum)
    {
        using namespace multiboot2;

        struct
        {
            header_prologue prologue;
            end_request     end;
        }
        constexpr request =
        {
            { architecture_type::x86, sizeof(request), },
            { },
        };

        ASSERT_EQ(request.prologue.checksum, -(std::uint32_t)(0xe85250d6 + sizeof(request)));
    }
}
