#pragma once
#include <memory>
#include "serializer.hpp"
#include "../net/socket.hpp"

template <typename DataType>
class Publisher
{
public:
    bool publish(const std::vector<DataType>& data)
    {
        auto serialized = byte_serializer::serialize_vector(data);
        return _socket->send(serialized);
    }

protected:
    Publisher(std::unique_ptr<Socket>&& socket)
        : _socket(std::move(socket)) {}

    virtual ~Publisher() = default;

    std::unique_ptr<Socket> _socket;
};