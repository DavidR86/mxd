/// @file  kepler.hpp
/// @brief Example solution of Kepler's equation.
/// @date  November 06, 2018
 
#pragma once
 
// C++ Standard Library
#include <cmath>
#include <limits>
 
namespace mxd {
 
/// @brief Solve Kepler's equation with a naive algorithm.
/// @tparam T Floating-point type.
/// @param ecc Orbital eccentricity.
/// @param man Mean anomaly, rad.
/// @return Eccentric anomaly, rad.
template <typename T>
inline T kepler(T ecc, T man) {
  T ean{man};
  T fval{ean - ecc * std::sin(ean) - man};
 
  T numberOfTimesRepeated{0};
  T lastValue{0};
 
  while (std::abs(fval) > std::numeric_limits<T>::epsilon()) {
    T dval{1 - ecc * std::cos(ean)};
    T step{-(fval / dval)};
   
    ean += step;
 
    fval = (ean - ecc * std::sin(ean) - man);
   
    if(std::abs(fval) == lastValue){
        numberOfTimesRepeated++;
    } else {
        numberOfTimesRepeated = 0;
        lastValue = std::abs(fval);
    }
   
    if(numberOfTimesRepeated > 3){
        break;
    }
   
   
  }
 
  return ean;
}
 
}  // namespace mxd