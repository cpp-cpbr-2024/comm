#include <iostream>
#include <cstring>
#include "net/multicast_recv.hpp"
#include "net/tcp_client.hpp"
#include "net/tcp_server.hpp"

#include "dto/radar_raw.h"
#include "dto/flying_object.h"

int test_multicast_recv() {
    const std::string multicastAddress = "239.255.0.1";
    const uint16_t port = 40000;
    
    try {
        boost::asio::io_service io_service;
        MulticastRecv client(io_service, multicastAddress, port);

        if (!client.joinGroup()) {
            std::cerr << "Failed to join multicast group." << std::endl;
            return 1;
        }

        std::cout << "Listening on multicast group " << multicastAddress << ":" << port << std::endl;

        while (true) {
            auto message = client.recv();
            if (message.has_value()) {
                std::cout << "Received " << message->size() << " bytes: ";
                for (const auto& byte : message.value()) {
                    std::cout << std::hex << static_cast<int>(byte) << " ";
                }
                std::cout << std::dec << std::endl;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

int test_tcp_client() {
    boost::asio::io_service io_service;
    TcpClient client(io_service,"127.0.0.1", 8080);
    std::cout << "Created" << std::endl;
    if (!client.connect()) {
        std::cerr << "Failed to start the server" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Connected" << std::endl;

    while(1)
    {
        auto recv_data = client.recv();
        if (recv_data.has_value())
        {
            std::vector<uint8_t> data = recv_data.value();
            if (!data.empty())
            {
                std::cout << "Yes" << std::endl;
                for (auto byte : data) {
                    std::cout << std::hex << static_cast<int>(byte) << " ";
                }
                std::cout << std::dec << std::endl;

                client.send(data);
            }
        }
        else
        {
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int test_tcp_server() {
    boost::asio::io_service io_service;
    TcpServer server(io_service, 8080);
    std::cout << "Created" << std::endl;
    if (!server.accept()) {
        std::cerr << "Failed to start the server" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Connected" << std::endl;

    while(1)
    {
        auto recv_data = server.recv();
        if (recv_data.has_value())
        {
            std::vector<uint8_t> data = recv_data.value();
            if (!data.empty())
            {
                std::cout << "Yes" << std::endl;
                for (auto byte : data) {
                    std::cout << std::hex << static_cast<int>(byte) << " ";
                }
                std::cout << std::dec << std::endl;

                server.send(data);
            }
        }
        else
        {
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    return test_multicast_recv();
}
