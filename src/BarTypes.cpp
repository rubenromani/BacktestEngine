#include <cstdint>
#include <chrono>

#include "BarTypes.hpp"
#include "Utils.hpp"

Bar::Bar(uint32_t timePoint, float open, float high, float low, float close)
    : timePoint{timePoint}, open{open}, high{high}, low{low}, close{close}{
        timePointToTime();
    }

bool Bar::operator==(const Bar& rhs) const{ 
    return (
        timePoint == rhs.timePoint &&
        compareFloats<float>(open, rhs.open) &&
        compareFloats<float>(high, rhs.high) &&
        compareFloats<float>(low, rhs.low) &&
        compareFloats<float>(close, rhs.close)
        ); 
}

float Bar::range() const {
    return close-open;
}

void Bar::timePointToTime(){
    time_t timePoint_ = static_cast<time_t>(timePoint);
    gmtime_r(&timePoint_, &time);
}

Mt5Bar::Mt5Bar(uint32_t timePoint, float open, float high, float low, float close,
    uint32_t tickvol, uint32_t vol, uint32_t spread)
    : Bar{timePoint,open,high,low,close}, tickvol{tickvol}, vol{vol}, spread{spread}{}

bool Mt5Bar::operator==(const Mt5Bar& rhs) const{ 
    return (
        timePoint == rhs.timePoint &&
        compareFloats<float>(open, rhs.open) &&
        compareFloats<float>(high, rhs.high) &&
        compareFloats<float>(low, rhs.low) &&
        compareFloats<float>(close, rhs.close) &&
        tickvol == rhs.tickvol &&
        vol == rhs.vol &&
        spread == rhs.spread
        ); 
}