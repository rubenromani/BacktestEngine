#ifndef PRICE_SERIES_HPP
#define PRICE_SERIES_HPP

#include <cstdint>
#include <vector>
#include <iostream>
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

        std::cout << startIdx << std::endl;

        return PriceSeries<T>(std::move(newSeries),timeframe);
    }


private:
    std::vector<T> series_{};
    timeframe_e timeframe_{};
};

#endif /* PRICE_SERIES_HPP */