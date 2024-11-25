#pragma once

#include <cstdint>
#include <cstddef>
#include <optional>
#include <vector>

namespace byte_serializer
{
    template <typename T>
    std::vector<uint8_t> serialize(const T& obj)
    {
        std::vector<uint8_t> data(sizeof(T));
        std::copy(reinterpret_cast<const uint8_t*>(&obj), reinterpret_cast<const uint8_t*>(&obj) + sizeof(T), data.begin());
        return data;
    }

    template <typename T>
    std::optional<T> deserialize(const std::vector<uint8_t>& data)
    {
        if (data.size() != sizeof(T))
        {
            return std::nullopt;
        }

        T obj;
        std::copy(data.begin(), data.end(), reinterpret_cast<uint8_t*>(&obj));
        return obj;
    }
};