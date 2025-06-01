//
//  StdNormalCDF.hpp
//  Project 1
//
//  Created by Tracey on 10/12/21.
//

#ifndef StdNormalCDF_hpp
#define StdNormalCDF_hpp

#include <stdio.h>

// Standard Normal distribution CDF class
class StdNormalCDF {
    
public:
    double operator()(double x) const;
    
private:
    static const double A1;
    static const double A2;
    static const double A3;
    static const double A4;
    static const double A5;
    static const double B;
    static const double NORMALIZER;
};

#endif /* StdNormalCDF_hpp */
