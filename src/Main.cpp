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
    auto newPriceSeriesM5 = priceSeries.convertToTimeframe(MINUTE_5);
    /*
    for(int i=0; i<10; i++){
        newPriceSeriesM5.at(i).printVerbose();
    }
    */
    filepath = "../data/EURUSD_M5_pars.csv";
    auto originalPriceSeriesM5 = dataReader.readFromFile(filepath);
    const auto & originalPriceSeriesM5Series = originalPriceSeriesM5.series();
    const auto & newPriceSeriesM5Series = newPriceSeriesM5.series();
    auto originalPriceSeriesM5SeriesIt = originalPriceSeriesM5Series.begin();
    auto newPriceSeriesM5SeriesIt = newPriceSeriesM5Series.begin();

    // find starting point
    while( (*(originalPriceSeriesM5SeriesIt++)).timePoint !=  (*newPriceSeriesM5SeriesIt).timePoint);
    std::cout << (*originalPriceSeriesM5SeriesIt).timePoint << std::endl;


    //auto newPriceSeriesm10 = priceSeries.convertToTimeframe(MINUTE_10);
    //auto newPriceSeriesm15 = priceSeries.convertToTimeframe(MINUTE_15);
    //auto newPriceSeriesm30 = priceSeries.convertToTimeframe(MINUTE_30);
    //auto newPriceSeriesh1 = priceSeries.convertToTimeframe(HOUR_1);
    //auto newPriceSeriesh4 = priceSeries.convertToTimeframe(HOUR_4);
    //auto newPriceSeriesd1 = priceSeries.convertToTimeframe(DAY_1);
    //auto newPriceSeriesw1 = priceSeries.convertToTimeframe(WEEK_1);
    //auto newPriceSeriesM1 = priceSeries.convertToTimeframe(MOUNTH_1);
}

int main(){
    timeframeConversionTest();
    return 0;
}
