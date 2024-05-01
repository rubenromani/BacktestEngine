#ifndef DATA_READER_HPP
#define DATA_READER_HPP
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept> 
#include <sstream> 
#include "PriceSeries.hpp"

template <typename T>
class DataReader {
public:
    virtual PriceSeries<T> readFromFile(std::string path) override;
};


#endif /* DATA_READER_HPP */