//Project Euler: Problem 19

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int leaptest (int);
int main()
{
    int year;
    int common_year [76];
    int *cy = common_year;
    int leap_year[25];
    int *ly = leap_year;
    int day [101]; // Count 1 Jan 1900 As day 0
    int *d = &day[0];
    int i, j=0, k, SumOfDays = 0, temp = 0, counter = 0;
    int FirstDayofMonth [1200];
    int monthtable [2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    // 1. Creating list of leap and common years
    for (year = 1900; year <= 2000; year ++) {
        if (leaptest(year)) {
            *d++ = 366; // Leap year
            *ly++ = year;
        } else { // Common Year
            *d++ = 365;
            *cy++ = year;
        }
    }
    
    //2. Mark each and every first day of month
    for (year = 1901; year <= 2000; year ++) {
        for (i=1900; i<year; i++)
            SumOfDays += day[i-1900];// Sum of days b4 the current year.
        
        FirstDayofMonth[j++] = SumOfDays + 1; // For 1st Jan
        temp = FirstDayofMonth[j-1];
        
        if (leaptest(year))
            for (k=0; k<11; k++) { // Last month is excluded. Last one is 1Dec
                FirstDayofMonth[j++] = temp + monthtable[1][k];
                temp = FirstDayofMonth[j-1]; // Use leap month table
            } else
            for (k=0; k<11; k++) {
                FirstDayofMonth[j++] = temp + monthtable[0][k];
                temp = FirstDayofMonth[j-1]; //Use common month table
            }
        SumOfDays = 0;
    }
    //3. Mark each and every Sunday. If element in 3 coincide with 2, increase counter by one
    for (i=0; i<=1200; i++) // First sunday is Day 7 (7 Jan 1900). Hence every day with day number of integer multiple of 7 is a Sunday
        if (FirstDayofMonth[i] % 7 == 0)
            counter ++;
    printf ("Number of Sundays that fall on 1st day of the month in the 20th century is %d.", counter);
    return 0;
}

int leaptest (int yr)
{
    if (((yr%4 == 0) && (yr%100!=0)) || yr%400 == 0)
        return 1;
    return 0;
}

// The answer given by the program is 171.
