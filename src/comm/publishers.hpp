#pragma once
#include "publisher.hpp"
#include "config.hpp"
#include "../dto/radar_raw.h"
#include "../dto/flying_object.h"
#include "../net/multicast_send.hpp"

class RadarRawPublisher : public Publisher<RadarRaw>
{
public:
    RadarRawPublisher(boost::asio::io_context& ioContext)
        : Publisher(std::move(std::make_unique<MulticastSender>(
            ioContext, network_config::raw_radar_multicast_ip, network_config::raw_radar_multicast_port))) 
    {}

    ~RadarRawPublisher() override = default;
};

class FlyingObjectPublisher : public Publisher<FlyingObject>
{
public:
    FlyingObjectPublisher(boost::asio::io_context& ioContext)
        : Publisher(std::move(std::make_unique<MulticastSender>(
            ioContext, network_config::flying_object_multicast_ip, network_config::flying_object_multicast_port))) 
    {}

    ~FlyingObjectPublisher() override = default;
};


