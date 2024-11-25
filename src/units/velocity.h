#pragma once
#include "unit.h"

class PACKED Velocity : public Unit<float>
{
public:
    Velocity(float meters_per_second) 
        : Unit(meters_per_second) {}

    float get_meters_per_second() { return get_raw(); }
};
