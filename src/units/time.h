#pragma once
#include "unit.h"

class PACKED Time : public Unit<uint64_t>
{
public:
    Time(uint64_t miliseconds = 0UL) 
        : Unit(miliseconds) {}

    uint64_t get_seconds() const { return get_raw(); }
};
