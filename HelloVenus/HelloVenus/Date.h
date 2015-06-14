#include <iostream>
using namespace std;
#pragma	once

class Time
{
	public:
		Time(int i){ D = i; }

		bool operator+=(const Time &val) { return (D += val.D); }
		bool operator-=(const Time &val) { return (D -= val.D); }

		int GetValue() const{ return D; }

		operator int() const{return D;}
	private:
		int D;
};

class Day: public Time
{
    public:
        Day(int i = 0):Time(i) {}
};

class Month: public Time
{
    public:
        Month(int i = 0):Time(i) {}
};

class Year: public Time
{
    public:
        Year(int i = 0):Time(i) {}
};

class Date
{
	public:
		Date(Day,Month,Year);
		Date(int, int, int);
		const Date operator+(const Date &val);
		const Date operator-(const Date &val);
		bool operator=(const Date &val);
		bool operator+=(const Date &val);
		bool operator-=(const Date &val);
		bool operator>(const Date &val);
		bool operator<(const Date &val);
		bool operator>=(const Date &val);
		bool operator<=(const Date &val);

		const Date operator+(const Day &val){return Date(Day(D + val),M,Y);}
        const Date operator-(const Day &val){return Date(Day(D - val),M,Y);}
        bool operator=(const Day &val){return (D = val);}
        bool operator+=(const Day &val){return D += val;}
        bool operator-=(const Day &val){return D -= val;}
        bool operator>(const Day &val){return D>val;}
        bool operator<(const Day &val){ return D<val;}
        bool operator>=(const Day &val){ return D>=val;}
        bool operator<=(const Day &val){ return D<=val;}

		const Date operator+(const Month &val){return Date(D,Month(M+val),Y);}
		const Date operator-(const Month &val){return Date(D,Month(M-val),Y);}
		bool operator=(const Month &val){return(M = val);}
		bool operator+=(const Month &val){return M += val;}
		bool operator-=(const Month &val){return M -= val;}
		bool operator>(const Month &val){return M > val;}
		bool operator<(const Month &val){return M < val;}
		bool operator>=(const Month &val){return M >= val;}
		bool operator<=(const Month &val){return M <= val;}

		const Date operator+(const Year &val){return Date(D,M,Year(Y+val));}
		const Date operator-(const Year &val){return Date(D,M,Year(Y-val));}
		bool operator=(const Year &val){return(Y = val);}
		bool operator+=(const Year &val){return Y += val;}
		bool operator-=(const Year &val){return Y -= val;}
		bool operator>(const Year &val){return Y > val;}
		bool operator<(const Year &val){return Y < val;}
		bool operator>=(const Year &val){return Y >= val;}
		bool operator<=(const Year &val){return Y <= val;}

		void PrintDate() {cout << "Date:" << D << " Month:" << M << " Year" << Y << endl;}
		int CalcDay(); //returns int reflecting day 1= Sunday .... 7= Saterday
		void PrintDay(); //prints day to screen

		Day GetDay() const { return D;}
		Month GetMonth() const { return M;}
		Year GetYear() const { return Y;}

		~Date();
	private:
		void StripExcess();
		Day D;
		Month M;
		Year Y;
};

