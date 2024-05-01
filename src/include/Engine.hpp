#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <cstdint>
#include <vector>
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

template <typename T>
class PriceSeries{
public:
    PriceSeries(){};
    virtual void push(const T e){
        series_.push_back(e);
    }
    virtual const std::vector<T> & series() const{
        return series_;
    }
    virtual uint32_t size() const{
        return series_.size();
    }
    virtual const T & at(uint32_t index) const{
        return series_[index];
    }
private:
    std::vector<T> series_;
};

#endif /* ENGINE_HPP */