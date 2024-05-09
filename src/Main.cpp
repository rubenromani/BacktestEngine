#include <iostream>
#include "DataReader.hpp"
#include "BarTypes.hpp"
#include <chrono>
#include <thread>

void readData(const std::string& path){
    auto dataReader = DataReader<Mt5Bar>();
    auto priceSeries = dataReader.readFromFile(path);
}

void parallelSpeedTest(){
    std::string filepaths[6] = {
        "../data/AUDUSD_M1_pars.csv",
        "../data/EURUSD_M1_pars.csv",
        "../data/GBPUSD_M1_pars.csv",
        "../data/USDCAD_M1_pars.csv",
        "../data/USDCHF_M1_pars.csv",
        "../data/USDJPY_M1_pars.csv"
    };
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Hello from BacktestingEngine" << std::endl; 
    for(auto& path : filepaths){
        readData(path);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Sequential Duration: " << duration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::thread t_vec[6];
    for(size_t i=0;i<6;i++){
        t_vec[i] = std::thread(readData, filepaths[i]);
    }
    for(size_t i=0;i<6;i++){
        t_vec[i].join();
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Parallel Duration: " << duration.count() << " seconds" << std::endl;

}

void dateTimeTest(){
    std::string filepath = "../data/EURUSD_M1_pars.csv";
    auto dataReader = DataReader<Mt5Bar>();
    auto priceSeries = dataReader.readFromFile(filepath);
    int count{};
    for( const auto& bar : priceSeries.series()){
        count++;
        std::cout 
        << "Year: " << bar.time.tm_year + 1900 << " "
        << "Month: " << bar.time.tm_mon+1 << " "
        << "Day: " << bar.time.tm_mday << " "
        << "Hour: " << bar.time.tm_hour << " "
        << "Min: " << bar.time.tm_min << " "
        << "Sec: " << bar.time.tm_sec << " "
        << std::endl;
        if(count==1000) break;
    }
}

void timeframeConversionTest(){
    std::string filepath = "../data/EURUSD_M1_pars.csv";
    auto dataReader = DataReader<Mt5Bar>();
    auto priceSeries = dataReader.readFromFile(filepath);
    priceSeries.setTimeframe(MINUTE_1);
    for(uint64_t i =0; i<4500; i++)
    {
        std::cout 
        << "Index: " << i << "\t"
        << "Year: " << priceSeries.at(i).time.tm_year + 1900 << " "
        << "Month: " << priceSeries.at(i).time.tm_mon+1 << " "
        << "Day: " << priceSeries.at(i).time.tm_mday << " "
        << "Hour: " << priceSeries.at(i).time.tm_hour << " "
        << "Min: " << priceSeries.at(i).time.tm_min << " "
        << "Sec: " << priceSeries.at(i).time.tm_sec << " "
        << std::endl;
    }
    auto newPriceSeriesm5 = priceSeries.convertToTimeframe(MINUTE_5);
    auto newPriceSeriesm10 = priceSeries.convertToTimeframe(MINUTE_10);
    auto newPriceSeriesm15 = priceSeries.convertToTimeframe(MINUTE_15);
    auto newPriceSeriesm30 = priceSeries.convertToTimeframe(MINUTE_30);
    auto newPriceSeriesh1 = priceSeries.convertToTimeframe(HOUR_1);
    auto newPriceSeriesh4 = priceSeries.convertToTimeframe(HOUR_4);
    auto newPriceSeriesd1 = priceSeries.convertToTimeframe(DAY_1);
    auto newPriceSeriesw1 = priceSeries.convertToTimeframe(WEEK_1);
    auto newPriceSeriesM1 = priceSeries.convertToTimeframe(MOUNTH_1);
}

int main(){
    timeframeConversionTest();
    return 0;
}
