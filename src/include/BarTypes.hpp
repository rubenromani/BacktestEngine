#ifndef BAR_TYPES_HPP
#define BAR_TYPES_HPP
#include <ctime>

class Bar{
public:
    time_t time;
    float open;
    float high;
    float low;
    float close;

    Bar(time_t time, float open, float high, float low, float close);

    virtual bool operator==(const Bar& rhs) const;
};

class Mt5Bar : public Bar{
public:
    uint32_t tickvol;
    uint32_t vol;
    uint32_t spread;

    Mt5Bar(time_t time, float open, float high, float low, float close,
        uint32_t tickvol, uint32_t vol, uint32_t spread);

    virtual bool operator==(const Mt5Bar& rhs) const;
};

#endif /* BAR_TYPES_HPP */