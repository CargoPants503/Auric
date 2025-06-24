#pragma once

//#include <SDK/SDK.h>
#include <SDK/TypeInfo.h>

#include <cstdint>
#include <optional>
#include <unordered_set>

namespace Kyber
{
struct DataContext
{
    const void* bus;
    const void* data;
    const void* exposed;

    DataContext(const void* bus = 0, const void* data = 0, const void* exposed = 0)
        : bus(bus)
        , data(data)
        , exposed(exposed)
    {}
};
} // namespace Kyber