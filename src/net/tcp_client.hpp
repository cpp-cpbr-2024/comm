#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <thread>
#include <vector>

#include "socket.hpp"

using boost::asio::ip::tcp;

class TcpClient : Socket
{
public:
    TcpClient(boost::asio::io_service& io_service, std::string ip, uint16_t port);
    virtual ~TcpClient();

    bool connect();

    bool send(std::vector<uint8_t> data) override;
    std::optional<std::vector<uint8_t>> recv() override;

private:
    tcp::socket socket_;
    std::string ip_;
    uint16_t port_;
};