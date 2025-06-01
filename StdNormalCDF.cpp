//
//  StdNormalCDF.cpp
//  Project 1
//
//  Created by Tracey on 10/12/21.
//

#include "StdNormalCDF.hpp"
#include "math.h"

// find max
double max(double x, double y) {
        if (x > y) {return x;}
        else return y;
}

// Standard Normal distribution CDF class
double StdNormalCDF::operator()(double x) const {
    double K = 1.0 / (1.0 + B * fabs(x));
    double Rz = A1 * K + A2 * pow(K,2) + A3 * pow(K, 3) + A4 * pow(K, 4) + A5 * pow(K, 5);
    double cnd = NORMALIZER * exp(- 0.5 * x * x) * Rz;

    if (x > 0)
        cnd = 1.0 - cnd;
    return cnd;
}

const double StdNormalCDF::A1 = 0.319381530;
const double StdNormalCDF::A2 = -0.35653782;
const double StdNormalCDF::A3 = 1.781477937;
const double StdNormalCDF::A4 = -1.821255978;
const double StdNormalCDF::A5 = 1.330274429;
const double StdNormalCDF::B = 0.2316419;
const double StdNormalCDF::NORMALIZER = 0.39894228;     // really 1/sqrt(2*pi);
