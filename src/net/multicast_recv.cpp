#include "multicast_recv.hpp"
#include <iostream>

MulticastRecv::MulticastRecv(boost::asio::io_service& io_service, std::string multicastAddress, uint16_t port)
    : socket_(io_service),
      multicastAddress_(boost::asio::ip::make_address(multicastAddress)),
      listenEndpoint_(boost::asio::ip::udp::v4(), port)
{
    socket_.open(listenEndpoint_.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listenEndpoint_);
    joinGroup();
}

bool MulticastRecv::joinGroup()
{
    try
    {
        socket_.set_option(boost::asio::ip::multicast::join_group(multicastAddress_));
        return true;
    }
    catch (const boost::system::system_error &e)
    {
        std::cerr << "Error joining multicast group: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::vector<uint8_t>> MulticastRecv::recv()
{
    try
    {
        boost::system::error_code error;
        size_t length = socket_.receive_from(boost::asio::buffer(recvBuffer_), senderEndpoint_, 0, error);

        if (error && error != boost::asio::error::message_size)
        {
            std::cerr << "Receive error: " << error.message() << std::endl;
            return std::nullopt;
        }
        return std::vector<uint8_t>(recvBuffer_.begin(), recvBuffer_.begin() + length);
    }
    catch (const boost::system::system_error &e)
    {
        std::cerr << "Error receiving data: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool MulticastRecv::send(std::vector<uint8_t> data)
{
    return false;
}
