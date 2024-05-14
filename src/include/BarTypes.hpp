#ifndef BAR_TYPES_HPP
#define BAR_TYPES_HPP
#include <ctime>
#include <vector>

class Bar{
public:
    uint32_t timePoint{};
    float open{};
    float high{};
    float low{};
    float close{};
    tm time{};
    std::vector<Bar> intrabar{};

    Bar(uint32_t timePoint, float open, float high, float low, float close);
    Bar(uint32_t timePoint, float open, float high, float low, float close, std::vector<Bar>&& intrabar);
    virtual float range() const;
    virtual bool operator==(const Bar& rhs) const;
    virtual void print() const;

private:
    virtual void timePointToTime();
};

class Mt5Bar : public Bar{
public:
    uint32_t tickvol{};
    uint32_t vol{};
    uint32_t spread{};
    std::vector<Mt5Bar> intrabar{};

    Mt5Bar(uint32_t timePoint, float open, float high, float low, float close,
        uint32_t tickvol, uint32_t vol, uint32_t spread);
    Mt5Bar(uint32_t timePoint, float open, float high, float low, float close,
        uint32_t tickvol, uint32_t vol, uint32_t spread, std::vector<Mt5Bar>&& intrabar);
    virtual bool operator==(const Mt5Bar& rhs) const;
};

#endif /* BAR_TYPES_HPP */