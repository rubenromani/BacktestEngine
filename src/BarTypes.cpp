#include <cstdint>
#include <chrono>
#include <iostream>

#include "BarTypes.hpp"
#include "Utils.hpp"

Bar::Bar(uint32_t timePoint, float open, float high, float low, float close)
    : timePoint{timePoint}, open{open}, high{high}, low{low}, close{close}{
        timePointToTime();
    }

Bar::Bar(uint32_t timePoint, float open, float high, float low, float close, std::vector<Bar>&& intrabar)
    : timePoint{timePoint}, open{open}, high{high}, low{low}, close{close}, intrabar{std::move(intrabar)}{
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

void Bar::print() const {
    std::cout 
        << time.tm_year + 1900 << ""
        << "/" <<time.tm_mon+1 << ""
        << "/" << time.tm_mday << " "
        << time.tm_hour << " "
        << ":" << time.tm_min << ""
        << ":" << time.tm_sec << "\t"
        << open << ", " << high << ", " << low << ", " << close << ", "
        << std::endl;
}

void Bar::printVerbose() const {
    print();
    if(!intrabar.empty()){
        for(auto& intra : intrabar){
            std::cout << "\t";
            intra.print();
        }
    }
}

Mt5Bar::Mt5Bar(uint32_t timePoint, float open, float high, float low, float close,
    uint32_t tickvol, uint32_t vol, uint32_t spread)
    : Bar{timePoint,open,high,low,close}, tickvol{tickvol}, vol{vol}, spread{spread}{}

Mt5Bar::Mt5Bar(uint32_t timePoint, float open, float high, float low, float close,
    uint32_t tickvol, uint32_t vol, uint32_t spread, std::vector<Mt5Bar>&& intrabar)
    : Bar{timePoint,open,high,low,close}, tickvol{tickvol}, vol{vol}, spread{spread}, intrabar{std::move(intrabar)}{}

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