#ifndef PRICE_SERIES_HPP
#define PRICE_SERIES_HPP

#include <cstdint>
#include <vector>

#include "BarTypes.hpp"


template <typename T>
class PriceSeries {
public:
    PriceSeries(){};
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
private:
    std::vector<T> series_;
};

#endif /* PRICE_SERIES_HPP */