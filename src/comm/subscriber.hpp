#pragma once
#include <atomic>
#include <memory>
#include <thread>
#include "serializer.hpp"
#include "../net/socket.hpp"

template <typename DataType>
class Subscriber
{
public:
    void set_on_receive(std::function<void(const std::vector<DataType>&)> callback)
    {
        _callback = callback;
    }

    void start()
    {
        _running = true;
        _thread = std::thread([&]() {
            // FIXME: Busy waiting
            while (_running)
            {
                auto data = _socket->recv();
                if (data.has_value())
                {
                    auto deserialized = byte_serializer::deserialize_vector<DataType>(data.value());
                    if (deserialized.has_value())
                    {
                        _callback(deserialized.value());
                    }
                }
            }
        });
    }

    void stop()
    {   
        if (_running)
        {
            _running = false;
            _thread.join();
        }
    }

protected:
    Subscriber(std::unique_ptr<Socket> socket)
        : _socket(std::move(socket)) {}

    virtual ~Subscriber()
    {
        stop();
    }


    std::unique_ptr<Socket> _socket;
    std::function<void(const std::vector<DataType>&)> _callback;
    std::atomic<bool> _running;
    std::thread _thread;
};