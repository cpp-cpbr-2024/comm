#pragma once
#include "subscriber.hpp"
#include "config.hpp"
#include "../dto/radar_raw.h"
#include "../dto/flying_object.h"
#include "../net/multicast_recv.hpp"

class RadarRawSubscriber : public Subscriber<RadarRaw>
{
public:
    RadarRawSubscriber(boost::asio::io_context& ioContext)
        : Subscriber(std::move(std::make_unique<MulticastRecv>(
            ioContext, network_config::raw_radar_multicast_ip, network_config::raw_radar_multicast_port))) 
    {}

    ~RadarRawSubscriber() override = default;
};

class FlyingObjectSubscriber : public Subscriber<FlyingObject>
{
public:
    FlyingObjectSubscriber(boost::asio::io_context& ioContext)
        : Subscriber(std::move(std::make_unique<MulticastRecv>(
            ioContext, network_config::flying_object_multicast_ip, network_config::flying_object_multicast_port))) 
    {}

    ~FlyingObjectSubscriber() override = default;
};
