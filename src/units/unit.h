#pragma once

#if defined(_MSC_VER) // For MSVC
  #define PACKED __pragma(pack(push, 1))
  #define END_PACKED __pragma(pack(pop))
#elif defined(__GNUC__) || defined(__clang__) // For GCC/Clang
  #define PACKED __attribute__((packed))
  #define END_PACKED
#else
  #error "Unsupported compiler"
#endif


template <typename T>
class PACKED Unit
{
public:
    Unit(T init_val = T())
        : _val{init_val} {};

    T get_raw() const { return _val; }
    void set_raw(T val) {_val = val;}

protected:
    T _val;
} END_PACKED;