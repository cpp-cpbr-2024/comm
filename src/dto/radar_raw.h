#include <cstdint>
#include <cassert>
#include "../units/units.h"

struct __attribute__((packed)) RadarRaw 
{
    uint16_t id;
    Time timestamp;
    Distance distance;
    Angle azimuth; 
    Velocity radial_velocity;
};

static_assert(sizeof(RadarRaw) == 22);
