#pragma once
#include "socket.hpp"
#include <boost/asio.hpp>
#include <string>

class MulticastSender : public Socket 
{
public:
    MulticastSender(boost::asio::io_context& ioContext, std::string multicastAddress, uint16_t port);
    bool send(std::vector<uint8_t> data) override;
    std::optional<std::vector<uint8_t>> recv() override;

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint multicastEndpoint_;
};