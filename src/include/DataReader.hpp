#ifndef DATA_READER_HPP
#define DATA_READER_HPP
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept> 
#include <sstream> 
#include <type_traits>
#include "PriceSeries.hpp"

template <typename T>
class DataReader {
public:

    virtual PriceSeries<T> readFromFile(std::string path){
        std::ifstream inputFile;
        inputFile.open(path);
        std::string line;
        auto priceSeries = PriceSeries<T>();

        while(getline(inputFile, line)){
            auto bar = getBarFromLine(line);
            priceSeries.push(bar);
            line="";
        }

        return priceSeries;
    }

    T getBarFromLine(std::string line);
};

template<typename T> 
T DataReader<T>::getBarFromLine(std::string line){}

template<>
Bar DataReader<Bar>::getBarFromLine(std::string line)
{
    std::string tmp;
    uint32_t timePoint;
    float open;
    float high;
    float low;
    float close;
    
    std::stringstream inputString(line);
    tmp="";
    getline(inputString, tmp, ',');
    timePoint = std::stoul(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    open = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    high = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    low = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp);
    close = std::stof(tmp,nullptr);
    
    return Bar(timePoint,open,high,low,close);
}

template<>
Mt5Bar DataReader<Mt5Bar>::getBarFromLine(std::string line)
{
    std::string tmp;
    uint32_t timePoint;
    float open;
    float high;
    float low;
    float close;
    uint32_t tickvol;
    uint32_t vol;
    uint32_t spread;
    std::stringstream inputString(line);
    
    tmp="";
    getline(inputString, tmp, ',');
    timePoint = std::stoul(tmp,nullptr);
    getline(inputString, tmp, ',');
    open = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    high = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    low = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    close = std::stof(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    tickvol = std::stoul(tmp,nullptr);
    tmp="";
    getline(inputString, tmp, ',');
    vol = std::stoul(tmp,nullptr);
    tmp="";
    getline(inputString, tmp);
    spread = std::stoul(tmp,nullptr);
    return Mt5Bar(timePoint,open,high,low,close,tickvol,vol,spread);
}


#endif /* DATA_READER_HPP */