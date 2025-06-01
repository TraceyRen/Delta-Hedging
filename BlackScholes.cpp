//
//  BlackScholes.cpp
//  lab1
//
//  Created by Tracey on 10/1/21.
//

#include "BlackScholes.hpp"

// BlackScholes class definition
// default constructor
BlackScholes::BlackScholes(){
    strike = 0;
    assetPrice = 0;
    volatility = 0;
    rf = 0;
    maturity = 0;
    yield = 0;
    optionType = NULL;
}

// constructor
BlackScholes::BlackScholes(double K, double S0, double sigma, double r, double T, double q, bool ot) {
    strike = K;
    assetPrice = S0;
    volatility = sigma;
    rf = r;
    maturity = T;            
    yield = q;
    optionType = ot;
}

// destructor
BlackScholes::~BlackScholes(){}

// calculate option value
double BlackScholes::OptionValue()
{
    double K = strike;
    double S0 = assetPrice;
    double sigma = volatility;
    double r = rf;
    double T = maturity;
    double q = yield;
    bool ot = optionType;
    
    double d1 = (log(S0/K) + (r - q + 0.5*sigma*sigma)*T)/(sigma*sqrt(T));
    double d2 = d1 - sigma*sqrt(T);
    StdNormalCDF phi;
    if (ot)
        return S0*exp(-q*T)*phi(d1) - K*exp(-r*T)*phi(d2);
    else
        return K*exp(-r*T)*phi(-d2) - S0*exp(-q*T)*phi(-d1);
}

// print out option information
void BlackScholes::optionInf() {
    cout << "Underlying stock price: " << assetPrice << endl;
    cout << "Strike:                 " << strike << endl;
    cout << "Volatility:             " << volatility << endl;
    cout << "Risk-free rate:         " << rf << endl;
    cout << "Maturity time:          " << maturity << endl;
    cout << "Yield:                  " << yield << endl;
    if(optionType)
        cout << "Option type:            Call" << endl;
    else cout << "Option type:            Put" << endl;
  
}

// implied volitality (Newton-Raphson)
double BlackScholes::impliedVol(double K, double S0,
                                double QP, // quoted option price, QP
                                double r, double T, double q, bool ot) {
    
    double tolerance = 0.00001;
    double initialVol = 0.5;
    
    BlackScholes bs(K, S0, initialVol, r, T, q, ot);
    double optVal = bs.OptionValue();
    double diff = optVal - QP;
    double vega = bs.vega();
    double vol = initialVol - diff/vega;
    
    while ((abs(vol - initialVol) > tolerance) && (abs(diff) > tolerance)) {
        initialVol = vol;
        BlackScholes bs(K, S0, initialVol, r, T, q, ot);
        optVal = bs.OptionValue();
        diff = optVal - QP;
        vega = bs.vega();
        vol = initialVol - diff/vega;
    }
    
    return vol;
}

// vega
double BlackScholes::vega()
{
    double K = strike;
    double S0 = assetPrice;
    double sigma = volatility;
    double r = rf;
    double T = maturity;
    double q = yield;
    
    StdNormalCDF phi;
    double d1 = (log(S0/K) + (r - q + 0.5*sigma*sigma)*T)/(sigma*sqrt(T));
    double vega = exp(-q*T)*S0*sqrt(T)*phi(d1);
    return vega;
}

// delta
double BlackScholes::delta()
{
    double K = strike;
    double S0 = assetPrice;
    double sigma = volatility;
    double r = rf;
    double T = maturity;
    double q = yield;
    bool ot = optionType;
    
    StdNormalCDF phi;
    double d1 = (log(S0/K) + (r - q + 0.5*sigma*sigma)*T)/(sigma*sqrt(T));
    double delta;
    
    if (ot) {
        delta = exp(-q*T)*phi(d1);                 // call option
    } else delta = exp(-q*T)*(1 - phi(d1));        // put option
    
    return delta;
}
