#include <cstdint>
#include <cassert>
#include "vector_2d.h"
#include "../units/units.h"

struct __attribute__((packed)) FlyingObject
{ 
    uint16_t id;
    Time timestamp;
    Vector2D<Distance> position;
    Vector2D<Velocity> velocity; 
};

static_assert(sizeof(FlyingObject) == 26);
