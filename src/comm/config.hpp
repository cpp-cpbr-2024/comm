#pragma once

#include <cstdint>

namespace network_config
{
    static constexpr const char* raw_radar_multicast_ip = "239.255.0.1";
    static constexpr uint16_t raw_radar_multicast_port = 10000;

    static constexpr const char* flying_object_multicast_ip = "239.255.0.1";
    static constexpr uint16_t flying_object_multicast_port = 10001;
}