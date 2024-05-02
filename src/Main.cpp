#include <iostream>
#include "DataReader.hpp"
#include "BarTypes.hpp"
#include <chrono>
#include <thread>

void readData(const std::string& path){
    auto dataReader = DataReader<Mt5Bar>();
    auto priceSeries = dataReader.readFromFile(path);
}

int main(){
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
    return 0;
}
