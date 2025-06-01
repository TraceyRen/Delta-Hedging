//
//  BlackScholes.hpp
//  lab1
//
//  Created by Tracey on 10/1/21.
//

#ifndef BlackScholes_hpp
#define BlackScholes_hpp

#include <stdio.h>
#include "StdNormalCDF.hpp"
#include <iostream>
#include <math.h>

using namespace std;

class BlackScholes
{
protected:
    double strike;          // option strike price, K
    double assetPrice;      // underlying asset's current price, S0
    double volatility;      // volitality, sigma
    double rf;              // risk-free rate, r
    double maturity;        // time to maturity, T
    double yield;           // dividend yeild, q
    bool optionType;        // call or put
public:
    
    // default constructor
    BlackScholes();
    
    // constructor
    BlackScholes(double K, double S0, double sigma, double r, double T, double q, bool ot);
    
    // destructor
    ~BlackScholes();
    
    // calculate option value
    double OptionValue();
    
    // print the option information
    void optionInf();
    
    // implied volitality (Newton-Raphson)
    double impliedVol(double K, double S0,
                      double QP, // quoted option price, QP
                      double r, double T, double q, bool ot);
    
    // vega
    double vega();
    
    // delta
    double delta();
   
};

// verify "put-call parity"
double put_call(double S0, double K, double q, double T, double r);

#endif /* BlackScholes_hpp */

