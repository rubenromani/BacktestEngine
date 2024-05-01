#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

bool compareFloats(const float A, const float B, const float epsilon = 0.00000001){
    return fabs(A-B)<epsilon;
}

#endif /* UTILS_HPP */