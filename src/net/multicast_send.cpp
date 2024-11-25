#include "multicast_send.hpp"
#include <iostream>

MulticastSender::MulticastSender(boost::asio::io_context& ioContext, std::string multicastAddress, uint16_t port)
    : socket_(ioContext),
      multicastEndpoint_(boost::asio::ip::make_address(multicastAddress), port) {

    socket_.open(boost::asio::ip::udp::v4());
    socket_.set_option(boost::asio::ip::multicast::hops(1));
    socket_.set_option(boost::asio::ip::multicast::enable_loopback(true));
}

bool MulticastSender::send(std::vector<uint8_t> data) {
    try {
        socket_.send_to(boost::asio::buffer(data), multicastEndpoint_);
        std::cout << "Sent " << data.size() << " bytes." << std::endl;
        return true;
    } catch (const boost::system::system_error& e) {
        std::cerr << "Send error: " << e.what() << std::endl;
        return false;
    }
}