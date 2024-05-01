#include <cstdint>

#include "BarTypes.hpp"
#include "Utils.hpp"

Bar::Bar(time_t time, float open, float high, float low, float close)
    : time{time}, open{open}, high{high}, low{low}, close{close}{}

bool Bar::operator==(const Bar& rhs) const{ 
    return (
        time == rhs.time &&
        compareFloats(open, rhs.open) &&
        compareFloats(high, rhs.high) &&
        compareFloats(low, rhs.low) &&
        compareFloats(close, rhs.close)
        ); 
}

Mt5Bar::Mt5Bar(time_t time, float open, float high, float low, float close,
    uint32_t tickvol, uint32_t vol, uint32_t spread)
    : Bar{time,open,high,low,close}, tickvol{tickvol}, vol{vol}, spread{spread}{}

bool Mt5Bar::operator==(const Mt5Bar& rhs) const{ 
    return (
        time == rhs.time &&
        compareFloats(open, rhs.open) &&
        compareFloats(high, rhs.high) &&
        compareFloats(low, rhs.low) &&
        compareFloats(close, rhs.close) &&
        tickvol == rhs.tickvol &&
        vol == rhs.vol &&
        spread == rhs.spread
        ); 
}