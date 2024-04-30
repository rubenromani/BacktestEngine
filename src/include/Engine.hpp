#include <vector>

struct Bar{
    float open;
    float high;
    float loe;
    float close;
    float volume;
};

class PricesSeries{
public:
    PricesSeries(){};
    virtual void push(const Bar e){
        series_.push_back(e);
    }
    virtual const std::vector<Bar> & series() const {
        return series_;
    }
private:
    std::vector<Bar> series_;
};