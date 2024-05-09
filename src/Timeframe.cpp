#include "Timeframe.hpp"

bool checkTimeframeCompatibility(timeframe_e from, timeframe_e to){
    if(from>=to) return false;
    if(from==MINUTE_10 && to==MINUTE_15) return false;
    return true;
}

uint32_t intervalToSeconds(timeframe_e timeframe){
    switch (timeframe)
    {
    case MINUTE_1:
        return 60;
        break;

    case MINUTE_5:
        return 60*5;
        break;

    case MINUTE_10:
        return 60*10;
        break;
    
    case MINUTE_15:
        return 60*15;
        break;

    case MINUTE_30:
        return 60*30;
        break;

    case HOUR_1:
        return 60*60;
        break;

    case HOUR_4:
        return 60*60*4;
        break;

    case DAY_1:
        return 60*60*24;
        break;

    case WEEK_1:
        return 60*60*24*7;
        break;

    case MOUNTH_1:
        return 60*60*730;
        break;

    default:
        return 0;
        break;
    }
}

uint8_t getNumValue(timeframe_e timeframe){
    switch (timeframe)
    {
    case MINUTE_1:
        return 1;
        break;

    case MINUTE_5:
        return 5;
        break;

    case MINUTE_10:
        return 10;
        break;
    
    case MINUTE_15:
        return 15;
        break;

    case MINUTE_30:
        return 30;
        break;

    case HOUR_1:
        return 1;
        break;

    case HOUR_4:
        return 4;
        break;

    case DAY_1:
        return 1;
        break;

    case WEEK_1:
        return 1;
        break;

    case MOUNTH_1:
        return 1;
        break;

    default:
        return 0;
        break;
    }
}