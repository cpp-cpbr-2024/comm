#pragma once
#include "unit.h"
#include <numbers>

class PACKED Angle : public Unit<float>
{
public:
    Angle(float radian) 
        : Unit(radian) {}

    float get_radians() { return get_raw(); }
    float get_degrees() { return get_raw() * 180.0f * std::numbers::inv_pi_v<float>; }
};
