#include "tcp_client.hpp"

TcpClient::TcpClient(boost::asio::io_context& io_context, std::string ip, uint16_t port)
    :   socket_(io_context), ip_{ip}, port_{port}
{
    ;
}

TcpClient::~TcpClient()
{
    socket_.close();
}

bool TcpClient::connect()
{
    socket_.connect( tcp::endpoint( boost::asio::ip::make_address(ip_), port_ ));
    return true;
}

bool TcpClient::send(std::vector<uint8_t> data)
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

std::optional<std::vector<uint8_t>> TcpClient::recv()
{
    boost::system::error_code error; 
    int len = socket_.available();
    if (len <= 0)
    {
        return std::vector<uint8_t>();
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

    // const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data().data());
    const auto data = static_cast<const char*>(receive_buffer.data().data());

    std::vector<uint8_t> result(data, data + receive_buffer.size());
    return result;
}
