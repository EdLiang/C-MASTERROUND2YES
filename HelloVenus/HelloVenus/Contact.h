#ifndef FRIEND
#define FRIEND

#include <iostream>
#include "Date.h"
using namespace std;

class Contact{
public:
	Contact(string f, string l, Date d) :first(f), last(l), DoB(d) {};
	Contact():DoB(Date(0,0,0)) {};
	string first;
	string last;
	Date DoB;
	unsigned int Key;
	bool operator<(const Contact &val) const { return (Key < val.Key); }
	bool operator>(const Contact &val) const { return (Key > val.Key); }
	bool operator<=(const Contact &val) const { return (Key <= val.Key); }
	bool operator>=(const Contact &val) const { return (Key >= val.Key); }
	bool operator==(const Contact &val) const { return (Key == val.Key); }
};



#endif // !FRIEND
