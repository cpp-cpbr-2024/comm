#pragma once

#include <cstdint>
#include <optional>
#include <vector>

class Socket
{
public:
    virtual ~Socket() {}
    virtual bool send(std::vector<uint8_t> data) = 0;
    virtual std::optional<std::vector<uint8_t>> recv() = 0;
};