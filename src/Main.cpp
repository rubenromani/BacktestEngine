#include <iostream>
#include "DataReader.hpp"
#include "BarTypes.hpp"

int main(){
    std::cout << "Hello from BacktestingEngine" << std::endl; 
    auto dataReader = DataReader<Bar>();
    auto priceSeries = dataReader.readFromFile("../data/AUDUSD_M1.csv");
    printf("Size %d", priceSeries.size());
    for( auto bar : priceSeries.series()){
        printf("%ld\t%f\t%f\t%f\t%f\n",
        bar.time,bar.open,bar.high,bar.low,bar.close);
    }
    return 0;
}