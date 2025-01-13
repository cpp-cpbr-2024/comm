#pragma once
#include "unit.h"

class PACKED Distance : public Unit<float>
{
public:
    Distance(float meters = 0.0f) 
        : Unit(meters) {}

    float get_meters() const { return get_raw(); }
} END_PACKED;
