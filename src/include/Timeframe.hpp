#ifndef TIMEFRAME_HPP
#define TIMEFRAME_HPP

typedef enum {
    MINUTE_1,
    MINUTE_5,
    MINUTE_10,
    MINUTE_15,
    MINUTE_30,
    HOUR_1,
    HOUR_4,
    DAY_1,
    WEEK_1,
    MOUNTH_1,
} timeframe_e;

bool checkTimeframeCompatibility(timeframe_e from, timeframe_e to);

#endif /* TIMEFRAME_HPP */