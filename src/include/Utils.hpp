#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

template <typename T>
bool compareFloats(const T A, const T B, const T epsilon = 0.00000001){
    return fabs(A-B)<epsilon;
}

#endif /* UTILS_HPP */