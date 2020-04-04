#include <psys/integer.h>

static_assert(sizeof(ps::size1) == 1, "unexpected size of size1");
static_assert(sizeof(ps::size2) == 2, "unexpected size of size2");
static_assert(sizeof(ps::size4) == 4, "unexpected size of size4");
static_assert(sizeof(ps::size8) == 8, "unexpected size of size8");

static_assert(sizeof(ps::integer1) == 1, "unexpected size of integer1");
static_assert(sizeof(ps::integer2) == 2, "unexpected size of integer2");
static_assert(sizeof(ps::integer4) == 4, "unexpected size of integer4");
static_assert(sizeof(ps::integer8) == 8, "unexpected size of integer8");
