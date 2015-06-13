#include "Date.h"

Date::Date(Day Da, Month Mo, Year Ye)
:D(Da), M(Mo), Y(Ye)
{
    StripExcess();
}

Date::Date(int Da, int Mo, int Ye)
:D(Da), M(Mo), Y(Ye)
{
    StripExcess();
}


Date::~Date()
{
}

const Date Date::operator+(const Date &val)
{
    return Date(val.D + D, val.M + M, val.Y + Y);
}

const Date Date::operator-(const Date &val)
{
    return Date(val.D - D, val.M - M, val.Y - Y);
}

bool Date::operator=(const Date &val)
{
    D = val.D;
    M = val.M;
    Y = val.Y;
    StripExcess();
    return true;
}

bool Date::operator+=(const Date &val)
{
    D += val.D;
    M += val.M;
    Y += val.Y;
    StripExcess();
    return true;
}

bool Date::operator-=(const Date &val)
{
    D -= val.D;
    M -= val.M;
    Y -= val.Y;
    StripExcess();
    return true;
}

bool Date::operator>(const Date &val)
{
    if(val.GetYear() > Y)
        return true;

    else if(val.GetMonth() > M)
        return true;

    else if(val.GetDay() > D)
        return true;

    return false;
}
bool Date::operator<(const Date &val)
{
    return (*this>val) ? false:true;
}
bool Date::operator>=(const Date &val)
{
    if(val.GetYear() > Y)
        return true;

    else if(val.GetMonth() > M)
        return true;

    else if(val.GetDay() > D)
        return true;

    return true;
}
bool Date::operator<=(const Date &val)
{
    if(val.GetYear() < Y)
        return true;

    else if(val.GetMonth() < M)
        return true;

    else if(val.GetDay() < D)
        return true;

    return true;
}

int Date::CalcDay()
{
    int C = Y/100;
    int DayRep = D + (2.6*M - 0.2) - (2 * C) + Y + (Y/4) +(C/4);
    DayRep %= 7;
    return DayRep;
}

void Date::PrintDay()
{
    int day = CalcDay();
    switch(day)
    {
        case 0:
            cout << "Sunday";
            break;
        case 1:
            cout << "Monday";
            break;
        case 2:
            cout << "Tuesday";
            break;
        case 3:
            cout << "Wednesday";
            break;
        case 4:
            cout << "Thursday";
            break;
        case 5:
            cout << "Friday";
            break;
        case 6:
            cout << "Saturday";
            break;
    }
}


void Date::StripExcess()
{
    int MaxDay = 31;
    if( M == 4|| M == 6|| M ==9 || M==11)
    {
        MaxDay = 30;
    }
    else if(M == 2)
    {
        if((Y%4 == 0 && Y%100 != 0) || Y%400 == 0)
            MaxDay = 29;
        else
            MaxDay = 28;

    }
	while (D> MaxDay)
	{
		D -= MaxDay;
		M += 1;
	}
	while (M > 12)
	{
		M -= 12;
		Y += 1;
	}
}
