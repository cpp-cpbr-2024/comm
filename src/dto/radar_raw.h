#pragma once
#include <cstdint>
#include <cassert>
#include "../units/unit.h"
#include "../units/units.h"

struct PACKED RadarRaw 
{
    uint16_t id;
    Time timestamp;
    Distance range;
    Angle azimuth; 
    Velocity radial_velocity;
} END_PACKED;

static_assert(sizeof(RadarRaw) == 22);
