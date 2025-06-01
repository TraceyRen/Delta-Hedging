//
//  main.cpp
//  Project 1
//
//  Created by Tracey on 10/12/21.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "BlackScholes.hpp"
#include "function.hpp"
#include "test.hpp"
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ctype.h>

using namespace std;
namespace bg = boost::gregorian;

int main() {
// test functions here.
    //test_vega();
    //test_impliedVol();
    //test_impliedVol();
    
// --------- Part 1: Test delta hedging implementation by the Black-Scholes model ------------
    
    // generate normal distribution random variable
    const unsigned long seed = 89210;
    boost::lagged_fibonacci1279 rng(seed);
    boost::normal_distribution<> norm(0,1);
    boost::variate_generator<boost::lagged_fibonacci1279&, boost::normal_distribution<>> stdnorm(rng, norm);
    
    vector<double> stockPrice;
    vector<double> callPrice;
    vector<double> Delta;
    vector<double> B;
    vector<double> HedgingError;
    vector<double> profitNloss;
    vector<double> PNLhedged;
    
    vector<double> stockPrice1000;
    vector<double> callPrice1000;
    vector<double> Delta1000;
    vector<double> B1000;
    vector<double> HedgingError1000;
    vector<double> profitNloss1000;
    vector<double> PNLhedged1000;
    
    double S = 100;
    double T = 0.4;
    double mu = 0.05;
    double sigma = 0.24;
    double r = 0.025;
    double q = 0;
    int N = 100;
    double delta_t = T/N;
    
    double K = 105;
    
    // for 100 simulation, stock prices and option prices
    ofstream hedgeTest100("/Users/tracey/Documents/GT/ISYE 6767/Project 1/Project 1/hedgeTest100.csv");
    
    if (!hedgeTest100.is_open()) cout << "Fail to open this hedgeTest100.csv." << endl;
    
    ofstream option100("/Users/tracey/Documents/GT/ISYE 6767/Project 1/Project 1/option100.csv");
    
    if (!hedgeTest100.is_open()) cout << "Fail to open this option100.csv." << endl;
    
    for(int n = 1; n <= 1000; n++){
        stockPrice.clear();
        callPrice.clear();
        Delta.clear();
        B.clear();
        HedgingError.clear();
        profitNloss.clear();
        PNLhedged.clear();

        stockPrice.push_back(S);
        BlackScholes call(K, S, sigma, r, T, q, true);
        double callValue = call.OptionValue();
        double callDelta = call.delta();
        callPrice.push_back(callValue);
        Delta.push_back(callDelta);
        B.push_back(callValue - callDelta*S);
        HedgingError.push_back(0);
        profitNloss.push_back(0);
        PNLhedged.push_back(0);
    
        for (int i = 1; i < N; i++) {
            
            stockPrice.push_back(stockPrice[i-1] + mu*stockPrice[i-1]*delta_t + sigma*stockPrice[i-1]*sqrt(delta_t)*stdnorm());
            BlackScholes call(K, stockPrice[i-1], sigma, r, (T - i*delta_t), q, true);
            callValue = call.OptionValue();
            callDelta = call.delta();
            callPrice.push_back(callValue);
            Delta.push_back(callDelta);
            B.push_back(Delta[i-1]*stockPrice[i] + B[i-1]*exp(r*delta_t) - Delta[i]*stockPrice[i]);
            HedgingError.push_back(Delta[i-1]*stockPrice[i] + B[i-1]*exp(r*delta_t) - callPrice[i]);
            profitNloss.push_back(callPrice[0] - callPrice[i]);
            PNLhedged.push_back(HedgingError[i]);
        }
        if (n <= 100) {
            for (int i = 0; i < N; i++) {
                hedgeTest100 << stockPrice[i] << ",";
                option100 << callPrice[i] << ",";
            }
            hedgeTest100 << "\n";
            option100 << "\n";
        } 
        unsigned long j = stockPrice.size() -1;
        //cout << stockPrice[j] << "," << callPrice[j] << "," << Delta[j] << "," << HedgingError[j] << "," << profitNloss[j] << endl;
        stockPrice1000.push_back(stockPrice[j]);
        callPrice1000.push_back(callPrice[j]);
        Delta1000.push_back(Delta[j]);
        HedgingError1000.push_back(HedgingError[j]);
        profitNloss1000.push_back(profitNloss[j]);
        PNLhedged1000.push_back(PNLhedged[j]);
    }
    
    hedgeTest100.close();
    option100.close();
    
    // output
    // 1000 simulation last day results
    ofstream hedgeTest1000("/Users/tracey/Documents/GT/ISYE 6767/Project 1/Project 1/hedgeTest1000.csv");
    
    if (!hedgeTest1000.is_open()) cout << "Fail to open this hedgeTest1.csv." << endl;
    
    hedgeTest1000 << "Test delta hedging implementation by the Black-Scholes model" << endl;
    hedgeTest1000 << "1000 simulation" << endl;
    hedgeTest1000 << "Simulated stock price" << "," << "Option price" << "," << "Delta" << "," << "Hedging error" << "," << "Profit and loss" << "," << "PNL Hedged" << "\n";
    
    for (int j = 0; j < 1000; j++) {
        hedgeTest1000 << stockPrice1000[j] << "," << callPrice1000[j] << "," << Delta1000[j] << "," << HedgingError1000[j] << "," << profitNloss1000[j] << "," << PNLhedged1000[j] << "\n";
    }
    hedgeTest1000.close();
    
// --------- Part 2:  ------------

    
    // user input
    string u_sDate, u_eDate, u_T;
    bg::date u_t0, u_t1, u_expiry;
    
        
    // dates, start date, end date, maturity date
    cout << "Please input the following dates information in the yyyy-mm-dd format." << endl;
    bool flag = true;
    do{
        do{
            cout << "Please input the option start date." << endl;
            cin >> u_sDate;
        }while(!checkFormat(u_sDate));
        u_t0 = bg::from_simple_string(u_sDate);
        
        do{
        cout << "Please input the option end date." << endl;
        cin >> u_eDate;
        }while(!checkFormat(u_eDate));
        u_t1 = bg::from_simple_string(u_eDate);
        
        if (u_t0 >= u_t1) {
            cout << "Start date should before end date. Try enter again." << endl;
            flag = false;
        } else flag = true;
    }while(!flag);
    
    do{
    cout << "Please input the option maturity date." << endl;
    cin >> u_T;
    }while(!checkFormat(u_T));
    u_expiry = bg::from_simple_string(u_T);
    if (u_t1 > u_expiry) {
        cout << "The end date is greater than the option expiry date." << "\n" <<
        "The result will be till maturity." << endl;
    }
    //cout << u_t0 << "," << u_t1 << "," << u_expiry << endl;
    
    // option type
    char u_ot;
    string str_ot;
    bool u_optionType = false;
    cout << "What's the type of your option? Call or put?" << "\n" <<
    "Please input c/C or p/P" << endl;
    
    cin >> u_ot;
    while(u_ot != 'c' && u_ot != 'C' && u_ot != 'p' && u_ot != 'P') {
        cout << "You enter an invalid type. Try again." << endl;
        cin >> u_ot;
    }
    if (u_ot == 'c' || u_ot == 'C') {str_ot = "C"; u_optionType = true;}
    else if (u_ot == 'p' || u_ot == 'P') {str_ot = "P"; u_optionType = false;}
    
    // strike price
    double u_K;
    cout << "Please input the option strike price." << endl;
    cin >> u_K;
    
    //read in interest rate
    ifstream interest("/Users/tracey/Documents/GT/ISYE 6767/Project 1/data/interest.csv");
    if (!interest.is_open()) cout << "Fail to open this Interest.csv." << endl;
    
    vector<string> date_vec;
    vector<double> intRate_vec;
        
    string line, temp;
    bg::date temp_d;
    double temp_r;

    while (getline(interest, line)) {
        if (isdigit(line[0])) {
            auto position = line.find_first_of(',');
            temp_d = bg::from_simple_string(line.substr(0, position));
            
            // filter
            if (temp_d >= u_t0 && temp_d <= u_t1) {
                temp = line.substr(position + 1, line.length());
                temp_r = atof(temp.c_str());
                date_vec.push_back(line.substr(0, position));
                intRate_vec.push_back(temp_r/100);
            }
            
        }
    }
    interest.close();
    //cout<< date_vec[0] << "," << rate[0] << endl;
    
    // read in security data
    ifstream closePrice("/Users/tracey/Documents/GT/ISYE 6767/Project 1/data/sec_GOOG.csv");
    if (!closePrice.is_open()) cout << "Fail to open this sec_GOOG.csv." << endl;
    
    stockPrice.clear();;
    double temp_s;
    
    while (getline(closePrice, line)) {
        if (isdigit(line[0])) {
            auto position = line.find_first_of(',');
            temp_d = bg::from_simple_string(line.substr(0, position));
            
            // filter
            if (temp_d >= u_t0 && temp_d <= u_t1) {
                temp = line.substr(position + 1, line.length());
                temp_s = atof(temp.c_str());
                stockPrice.push_back(temp_s);
            }
        }
    }
    closePrice.close();
    //cout << cPrice_vec[0] << endl;
    
    // read in option data
    ifstream options("/Users/tracey/Documents/GT/ISYE 6767/Project 1/data/op_GOOG.csv");
    if (!options.is_open()) cout << "Fail to open this op_GOOG.csv." << endl;
    
    vector<string> buyDate;
    vector<double> optionPrice_vec;
    string dt_temp, ex_temp, cp, strike_temp, bid_temp, offer_temp;
    double strike, bid, offer;
    
    while (getline(options, dt_temp, ',')) {
        
        getline(options, ex_temp, ',');
        getline(options, cp, ',');
        getline(options, strike_temp, ',');
        getline(options, bid_temp, ',');
        getline(options, offer_temp);
        
        if(isdigit(dt_temp[0])) {
            strike = atof(strike_temp.c_str());
            bg::date dt = bg::from_simple_string(dt_temp);
            bg::date Expiry = bg::from_simple_string(ex_temp);
            
            //filter
            if (dt >= u_t0 && dt <= u_t1 && Expiry == u_expiry && cp == str_ot && strike == u_K) {
                buyDate.push_back(dt_temp);
                bid = atof(bid_temp.c_str());
                offer = atof(offer_temp.c_str());
                optionPrice_vec.push_back((bid + offer)/2);
            }
        }
    }
    options.close();
    
    if (optionPrice_vec.size() == 0 ) {
        cout << "There is no matching option in the dataset." << endl;
    } else {
        // set up dynamic hedging
        Delta.clear();
        vector<double> IM;
        
        //double dateDiff = businessDiff(buyDate[0], u_T);
        //cout << u_K<< "," << stockPrice[0]<< "," << optionPrice_vec[0]<< "," << intRate_vec[0]<< "," << dateDiff << "," << 0<< "," << u_optionType<< endl;
        
        for (int i = 0; i < optionPrice_vec.size(); i++) {
            double dateDiff = businessDiff(buyDate[0], u_T);
            
            BlackScholes option;
            double impVol = option.impliedVol(u_K, stockPrice[i], optionPrice_vec[i], intRate_vec[i], dateDiff, 0, u_optionType);
            option = BlackScholes(u_K, stockPrice[i], impVol, intRate_vec[i], dateDiff, 0, u_optionType);
            IM.push_back(impVol);
            Delta.push_back(option.delta());
        }
        
        B.clear();
        HedgingError.clear();
        profitNloss.clear();
        PNLhedged.clear();
        B.push_back(optionPrice_vec[0] - Delta[0]*stockPrice[0]);
        HedgingError.push_back(0);
        profitNloss.push_back(0);
        PNLhedged.push_back(0);
        vector<double> totalWealth;
        totalWealth.push_back(0);
        delta_t = 1/252;
        
        for (int i = 1; i < optionPrice_vec.size(); i++) {
            B.push_back(Delta[i-1]*stockPrice[i] + B[i-1]*exp(intRate_vec[i]*delta_t) - Delta[i]*stockPrice[i]);
            HedgingError.push_back(Delta[i-1]*stockPrice[i] + B[i-1]*exp(intRate_vec[i]*delta_t) - optionPrice_vec[i]);
            profitNloss.push_back(optionPrice_vec[0] - optionPrice_vec[i]);
            PNLhedged.push_back(HedgingError[i]);
            totalWealth.push_back(HedgingError[i]);
        }
        
        //output the results
        ofstream deltaHedge("/Users/tracey/Documents/GT/ISYE 6767/Project 1/Project 1/deltaHedge.csv");
        
        if (!deltaHedge.is_open()) cout << "Fail to open this deltaHedge.csv." << endl;
        
        deltaHedge << "Using the Black-Scholes formula to construct the delta-hedging portfolio." << endl;
        deltaHedge << "User input information:" << endl;
        deltaHedge << "Start date: " << u_t0 << endl;
        deltaHedge << "End date: " << u_t1 << endl;
        deltaHedge << "Option expiry date: " << u_expiry << endl;
        deltaHedge << "Option type: " << str_ot << endl;
        deltaHedge << "Option strike price: " << u_K << endl;
        deltaHedge << "\n" << endl;
        deltaHedge << "Date" << "," << "Stock price" << "," << "Option price" << "," << "Implied volatility" << "," << "Delta" << "," << "Hedging error" << "," << "Profit and loss" << "," << "PNL Hedged" << "," << "Total wealth with hedging" << "," << "Total wealth without hedging" << "\n";
        
        for (int j = 0; j < optionPrice_vec.size(); j++) {
            deltaHedge << date_vec[j] << "," << stockPrice[j] << "," << optionPrice_vec[j] << "," << IM[j] << "," << Delta[j] << "," << HedgingError[j] << "," << profitNloss[j] << "," << PNLhedged[j] << "," << totalWealth[j] << "," << profitNloss[j] << "\n";
        }
        deltaHedge.close();
    }
    return 0;
}
