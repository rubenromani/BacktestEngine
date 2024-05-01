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

        getline(inputFile, line);
        while(getline(inputFile, line)){
            if (std::is_same<T, Bar>::value){
                auto bar = getBarFromLine(line);
                priceSeries.push(bar);
            }
            else {
                auto mt5Bar = getBarFromLine(line);
                priceSeries.push(mt5Bar);
            }
            line="";
        }

        return priceSeries;
    }

    Bar getBarFromLine(std::string line)
    {
        std::string tmp;
        time_t time;
        float open;
        float high;
        float low;
        float close;
        
        std::stringstream inputString(line);
        tmp="";
        getline(inputString, tmp, ',');
        time = std::stoul(tmp,nullptr);
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
        
        return Bar(time,open,high,low,close);
    }

    Mt5Bar getMt5BarFromLine(std::string line)
    {
        std::string tmp;
        time_t time;
        float open;
        float high;
        float low;
        float close;
        uint32_t tickvol;
        uint32_t vol;
        uint32_t spread;

        std::stringstream inputString(line);
        tmp="";
        getline(inputString, tmp, ' ');
        time = std::stoul(tmp,nullptr);
        tmp="";
        getline(inputString, tmp, ' ');
        tmp="";
        getline(inputString, tmp, ' ');
        printf("%s\n", tmp.c_str());
        open = std::stof(tmp,nullptr);
        tmp="";
        getline(inputString, tmp, ' ');
        high = std::stof(tmp,nullptr);
        tmp="";
        getline(inputString, tmp, ' ');
        low = std::stof(tmp,nullptr);
        tmp="";
        getline(inputString, tmp, ' ');
        close = std::stof(tmp,nullptr);
        tmp="";
        getline(inputString, tmp, ' ');
        tickvol = std::stoul(tmp,nullptr);
        tmp="";
        getline(inputString, tmp, ' ');
        vol = std::stoul(tmp,nullptr);
        tmp="";
        getline(inputString, tmp);
        spread = std::stoul(tmp,nullptr);

        return Mt5Bar(time,open,high,low,close,tickvol,vol,spread);
    }
};


#endif /* DATA_READER_HPP */