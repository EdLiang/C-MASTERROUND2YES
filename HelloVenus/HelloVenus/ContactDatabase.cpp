#include "ContactDatabase.h"
#include <math.h>

ContactDatabase::ContactDatabase()
{
}


ContactDatabase::~ContactDatabase()
{
}

void ContactDatabase::genFirstNameKey(Contact& cont)
{
	cont.Key = 0;
	unsigned int i;
	for ( i = 0; i < cont.first.size(); ++i)
	{
		cont.Key += cont.first[i];
	}
	pow(cont.Key, cont.first[--i]);
	//hash function: Key = sum of all ascii values to the power of the last value
}

void ContactDatabase::genLastNameKey(Contact& cont)
{
	cont.Key = 0;
	unsigned int i;
	for (i = 0; i < cont.last.size(); ++i)
	{
		cont.Key += cont.last[i];
	}
	pow(cont.Key, cont.last[--i]);
}

void ContactDatabase::genDOBKey(Contact& cont)
{
	cont.Key = 0;
	cont.Key += cont.DoB.GetDay();
	cont.Key += cont.DoB.GetMonth();
	cont.Key += cont.DoB.GetYear();
	pow(cont.Key, int(cont.DoB.GetYear()));
}

void ContactDatabase::EnterContact(Contact &cont)
{
	Contact firstNameCont = cont, lastNameCont = cont, DOBCont = cont;
	genFirstNameKey(firstNameCont);
	genLastNameKey(lastNameCont);
	genDOBKey(DOBCont);
	FirstNameTree.insertItem(firstNameCont);
	LastNameTree.insertItem(lastNameCont);
	DOBTree.insertItem(DOBCont);
}

void ContactDatabase::DeleteContact(Contact &cont)
{
	Contact firstNameCont = cont, lastNameCont = cont, DOBCont = cont;
	genFirstNameKey(firstNameCont);
	genLastNameKey(lastNameCont);
	genDOBKey(DOBCont);
	FirstNameTree.removeItem(firstNameCont);
	LastNameTree.removeItem(lastNameCont);
	DOBTree.removeItem(DOBCont);
}

bool ContactDatabase::SearchLastName(string last, Contact &val)
{
	bool found;
	val.last = last;
	genLastNameKey(val);
	found = LastNameTree.findItem(val);
	if (found)
		val = LastNameTree.getItem(val);
	return found;
}
bool ContactDatabase::SearchFirstName(string first, Contact &val)
{
	bool found;
	val.first = first;
	genFirstNameKey(val);
	found = FirstNameTree.findItem(val);
	if (found)
		val = FirstNameTree.getItem(val);
	return found;
}
bool ContactDatabase::SearchDateOfBirth(Date DOB, Contact &val)
{
	bool found;
	val.DoB = DOB;
	genDOBKey(val);
	found = DOBTree.findItem(val);
	if (found)
		val = DOBTree.getItem(val);
	return found;
}