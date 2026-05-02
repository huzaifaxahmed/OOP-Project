#include <iostream>
#include "headers.h"
using namespace dHeader;

Date::Date (int day, int month , int year){
    this->day = day;
    this->month = month;
    this->year = year; 
}
bool Date::within24Hours(Date other){
    if (this->day == other.day && this->month == other.month && this->year == other.year)
        return true;
    if (this->day == other.day - 1 && this->month == other.month && this->year == other.year)
        return true;
    if (other.day == 1) {
        int lastMonth = other.month - 1;
        int lastYear = other.year;
        
        if (lastMonth == 0) { 
            lastMonth = 12;
            lastYear = other.year - 1;
        }
        
        int daysInLastMonth;
        if (lastMonth == 2)
            daysInLastMonth = 28;
        else if (lastMonth == 4 || lastMonth == 6 || lastMonth == 9 || lastMonth == 11)
            daysInLastMonth = 30;
        else
            daysInLastMonth = 31;
        
        if (this->day == daysInLastMonth && this->month == lastMonth && this->year == lastYear)
            return true;
    }
    return false;
}
void Date::display(){
    std::cout << day << "/" << month << "/" << year;
}
int Date::yearsAgo(Date other){
    return other.year - this->year;
}
