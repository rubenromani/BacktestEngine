#ifndef PRICE_SERIES_HPP
#define PRICE_SERIES_HPP

#include <cstdint>
#include <vector>
#include <iostream>
#include <numeric>
#include <functional>
#include "BarTypes.hpp"
#include "Timeframe.hpp"


template <typename T>
class PriceSeries {
public:
    PriceSeries(){};

    PriceSeries(PriceSeries<T>&& src) 
    : series_{std::move(src.series_)}, timeframe_{src.timeframe_}{}

    PriceSeries(std::vector<T>&& srcSeries, timeframe_e timeframe) 
    : series_{std::move(srcSeries)}, timeframe_{timeframe}{}

    virtual void setTimeframe(timeframe_e timeframe){
        timeframe_ = timeframe;
    }

    virtual timeframe_e getTimeframe() const {
        return timeframe_;
    }

    virtual void push(const T e) {
        series_.push_back(e);
    }

    virtual const std::vector<T> & series() const {
        return series_;
    }

    virtual uint32_t size() const {
        return series_.size();
    }

    virtual const T & at(uint32_t index) const {
        return series_[index];
    }

    PriceSeries<T> convertToTimeframe(timeframe_e timeframe){
        if(!checkTimeframeCompatibility(timeframe_,timeframe)){
            std::cout << "Error: incompatible timeframes" << std::endl;
            return PriceSeries<T>();
        }
        std::vector<T> newSeries;

        // Search for starting point
        uint8_t timeOrder=0;
        if(timeframe<timeframe_e::HOUR_1){
            timeOrder=1;
        }
        else if(timeframe<timeframe_e::DAY_1){
            timeOrder=2;
        }
        else if(timeframe<timeframe_e::WEEK_1){
            timeOrder=3;
        }
        else if(timeframe<timeframe_e::MOUNTH_1)        {
            timeOrder=4;
        }
        else {
            timeOrder=5;
        }
        uint32_t startIdx=0;

        for(uint32_t i=0; i<series_.size(); i++){
            switch (timeOrder)
            {
            case 1:
                if(series_[i].time.tm_min % getNumValue(timeframe) == 0){break;}
                continue;

            case 2:
                if(series_[i].time.tm_min == 0){break;}
                continue;

            case 3:
                if(i==0){continue;}
                if(series_[i].time.tm_hour - series_[i-1].time.tm_hour<0){break;}
                continue;

            case 4:
                if(series_[i].time.tm_wday==1){break;}
                continue;
            
            case 5:
                if(i==0){continue;}
                if(series_[i].time.tm_mday-series_[i-1].time.tm_mday<0){break;}
                continue;

            default:
                break;
            }
            startIdx = i;
            break;
        }

        // GetNewBar
        uint32_t intervalSec = intervalToSeconds(timeframe);
        uint32_t endIdx = 0;

        std::function<T(std::vector<T>&,uint32_t,uint32_t)> getNewBar =
            [&](std::vector<T>& series, uint32_t startIdx, uint32_t endIdx) -> T {

                typename std::vector<T>::iterator startIt = series.begin() + startIdx;
                typename std::vector<T>::iterator endIt = series.begin() + endIdx;
                typename std::vector<T> intrabar{};

                if(timeframe_==timeframe_e::MINUTE_1){
                    for(auto it=startIt; it<endIt; it++){
                        intrabar.push_back(*it);
                    }
                }

                if constexpr(std::is_same<T, Bar>::value){
                    return T(
                        (*startIt).timePoint,
                        (*startIt).open,
                        (*std::max_element(startIt,endIt,[](T a, T b){
                            return a.high < b.high;
                        })).high,
                        (*std::min_element(startIt,endIt,[](T a, T b){
                            return a.low < b.low;
                        })).low,
                        (*(endIt-1)).close,
                        std::move(intrabar)
                    );
                } else {
                    return T(
                        (*startIt).timePoint,
                        (*startIt).open,
                        (*std::max_element(startIt,endIt,[](T a, T b){
                            return a.high < b.high;
                        })).high,
                        (*std::min_element(startIt,endIt,[](T a, T b){
                            return a.low < b.low;
                        })).low,
                        (*(endIt-1)).close,
                        std::accumulate(startIt, endIt, 0, [](uint32_t i, T t){return i+t.tickvol;}),
                        std::accumulate(startIt, endIt, 0, [](uint32_t i, T t){return i+t.vol;}),
                        std::accumulate(startIt, endIt, 0, [](uint32_t i, T t){return i+t.spread;})/static_cast<int>((endIt-startIt)),
                        std::move(intrabar)
                    );
                }

            };

        for(uint32_t i=startIdx; i<series_.size(); i++){
            if(static_cast<time_t>(series_[i].timePoint) - static_cast<time_t>(series_[startIdx].timePoint) >= intervalSec){
                endIdx=i;
                newSeries.push_back(getNewBar(series_,startIdx,endIdx));
                startIdx=i;
            }
        }

        return PriceSeries<T>(std::move(newSeries),timeframe);
    }


private:
    std::vector<T> series_{};
    timeframe_e timeframe_{};
};

#endif /* PRICE_SERIES_HPP */