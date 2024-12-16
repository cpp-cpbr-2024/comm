#pragma once
#include <cstdint>
#include <cassert>
#include "vector_2d.h"
#include "../units/unit.h"
#include "../units/units.h"

struct PACKED FlyingObject
{ 
    uint16_t id;
    Time timestamp;
    Vector2D<Distance> position;
    Vector2D<Velocity> velocity; 
} END_PACKED;

static_assert(sizeof(FlyingObject) == 26);
