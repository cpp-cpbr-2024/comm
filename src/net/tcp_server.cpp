#include "tcp_server.hpp"

TcpServer::TcpServer(boost::asio::io_service& io_service, uint16_t port)
    :   acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service)
{

}

TcpServer::~TcpServer()
{
    socket_.close();
}

bool TcpServer::accept()
{
    acceptor_.accept(socket_);
    return true;
}

bool TcpServer::send(std::vector<uint8_t> data)
{
    try
    {
        boost::asio::write(socket_, boost::asio::buffer(data));
        return true;
    }
    catch (const boost::system::system_error& e)
    {
        std::cerr << "Send failed: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::vector<uint8_t>> TcpServer::recv()
{
    boost::system::error_code error; 
    int len = socket_.available();
    if (len <= 0)
    {
        return socket_.is_open() ? std::optional(std::vector<uint8_t>()) : std::nullopt;
    }

    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket_, receive_buffer, boost::asio::transfer_exactly(len), error);

    if (error == boost::asio::error::eof)
    {
        return std::nullopt;
    }
    else if (error)
    {
        throw boost::system::system_error(error);
    }

    const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
    std::vector<uint8_t> result(data, data + receive_buffer.size());
    return result;
}
