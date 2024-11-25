#pragma once
#include "Socket.hpp"
#include <boost/asio.hpp>
#include <string>

class MulticastSender : public BaseSender {
public:
    MulticastSender(boost::asio::io_context& ioContext, std::string multicastAddress, uint16_t port);
    bool send(std::vector<uint8_t> data) override;

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint multicastEndpoint_;
};