//
//  function.hpp
//  Project 1
//
//  Created by Tracey on 10/14/21.
//

#ifndef function_hpp
#define function_hpp

#include <stdio.h>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>


using namespace std;
// check whether the user entered a date in the valid format.
bool checkFormat(string date);

// calculate the number og business date between two dates
double businessDiff(string start, string end);

#endif /* function_hpp */
