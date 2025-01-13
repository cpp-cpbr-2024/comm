#pragma once
#include <boost/asio.hpp>
#include <optional>
#include <vector>
#include <string>

#include "socket.hpp"

class MulticastRecv : public Socket
{
public:
    MulticastRecv(boost::asio::io_context& io_context, const std::string& multicastAddress, uint16_t port);
    bool joinGroup();

    std::optional<std::vector<uint8_t>> recv() override;
    bool send(std::vector<uint8_t> data) override;

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint senderEndpoint_;
    boost::asio::ip::udp::endpoint listenEndpoint_;
    boost::asio::ip::address multicastAddress_;
    std::array<uint8_t, 1500> recvBuffer_{}; // Buffer size for UDP packet
};