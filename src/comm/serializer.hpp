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

    template <typename T>
    std::vector<uint8_t> serialize_vector(const std::vector<T>& vec)
    {
        std::vector<uint8_t> data;
        for (const auto& obj : vec)
        {
            auto serialized = serialize(obj);
            data.insert(data.end(), serialized.begin(), serialized.end());
        }
        return data;
    }

    template <typename T>
    std::optional<std::vector<T>> deserialize_vector(const std::vector<uint8_t>& data)
    {
        if (data.size() % sizeof(T) != 0)
        {
            return std::nullopt;
        }

        std::vector<T> vec;
        for (size_t i = 0; i < data.size(); i += sizeof(T))
        {
            auto deserialized = deserialize<T>(std::vector<uint8_t>(data.begin() + i, data.begin() + i + sizeof(T)));
            if (!deserialized.has_value())
            {
                return std::nullopt;
            }
            vec.push_back(deserialized.value());
        }
        return vec;
    }
};