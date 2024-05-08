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

int main(){
    dateTimeTest();
    return 0;
}
