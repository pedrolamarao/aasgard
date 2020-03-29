#include <pc/pic.h>

#include <gtest/gtest.h>

namespace
{
    template <typename Size>
    class port
    {
    public:

        static_assert(sizeof(Size) == 1, "unexpected size");

        port (std::uint16_t address)
        {
        }

        Size read (Size)
        {

        }

        void write (Size value)
        {

        }

    };

    TEST(pic, smoke)
    {
        pc::pic<port> pic { 0 };
    }
}
