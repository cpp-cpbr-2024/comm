#pragma once

#define PACKED __attribute__((packed))

template <typename T>
class PACKED Unit
{
public:
    Unit(T init_val = T())
        : _val{init_val} {};

    T get_raw() { return _val; }
    void set_raw(T val) {_val = val;}

protected:
    T _val;
};