//
//  function.cpp
//  Project 1
//
//  Created by Tracey on 10/14/21.
//

#include "function.hpp"
#include <boost/date_time/gregorian/gregorian.hpp>
namespace bg = boost::gregorian;

// check whether the user entered a date in the valid format.
bool checkFormat(string date) {
    if ((date.length() != 10) || (date[4] != '-') || (date[7] != '-') || !isdigit(date[0]))
    {
        cout << "Invalid format, try again." << endl;
        return false;
    }
    return true;
}

// calculate the number og business date between two dates
double businessDiff(string start, string end) {
    bg::date START = bg::from_simple_string(start);
    bg::date END = bg::from_simple_string(end);
    long ndays = (END-START).days() + 1; // +1 for inclusive
    long nwkends = 2*( (ndays+END.day_of_week())/7 ); // 2*Saturdays
    if( END.day_of_week() == boost::date_time::Sunday ) ++nwkends;
    if( START.day_of_week() == boost::date_time::Saturday ) --nwkends;
    return ((ndays - nwkends)/252.0);
    
}
