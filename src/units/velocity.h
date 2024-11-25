#pragma once
#include "unit.h"

class PACKED Velocity : public Unit<float>
{
public:
    Velocity(float meters_per_second = 0.0f) 
        : Unit(meters_per_second) {}

    float get_meters_per_second() const { return get_raw(); }
};
