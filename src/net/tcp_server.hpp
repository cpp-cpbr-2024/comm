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

class TcpServer : Socket
{
public:
    TcpServer(boost::asio::io_service& io_service, uint16_t port);
    virtual ~TcpServer();

    bool accept();

    bool send(std::vector<uint8_t> data) override;
    std::optional<std::vector<uint8_t>> recv() override;

private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};