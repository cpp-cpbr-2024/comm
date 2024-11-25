#pragma once
#include "unit.h"

class PACKED Distance : public Unit<float>
{
public:
    Distance(float meters) 
        : Unit(meters) {}

    float get_meters() { return get_raw(); }
};
