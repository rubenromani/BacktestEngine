#include "Timeframe.hpp"

bool checkTimeframeCompatibility(timeframe_e from, timeframe_e to){
    if(from>=to) return false;
    if(from==MINUTE_10 && to==MINUTE_15) return false;
    return true;
}