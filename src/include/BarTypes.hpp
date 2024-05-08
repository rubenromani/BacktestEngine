#ifndef BAR_TYPES_HPP
#define BAR_TYPES_HPP
#include <ctime>

class Bar{
public:
    uint32_t timePoint{};
    float open{};
    float high{};
    float low{};
    float close{};
    tm time{};

    Bar(uint32_t timePoint, float open, float high, float low, float close);
    virtual float range() const;
    virtual bool operator==(const Bar& rhs) const;

private:
    virtual void timePointToTime();
};

class Mt5Bar : public Bar{
public:
    uint32_t tickvol{};
    uint32_t vol{};
    uint32_t spread{};

    Mt5Bar(uint32_t timePoint, float open, float high, float low, float close,
        uint32_t tickvol, uint32_t vol, uint32_t spread);
    virtual bool operator==(const Mt5Bar& rhs) const;
};

#endif /* BAR_TYPES_HPP */