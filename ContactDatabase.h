#ifndef CONTACTDATABASE_HDoB
#define CONTACTDATABASE_H
#include "friend.h"
#include "TwoThreeTree.h"

class ContactDatabase
{
public:
	ContactDatabase();
	~ContactDatabase();
	void EnterContact(Contact &cont); //inserts contact into all three trees
	void DeleteContact(Contact &cont);
	bool SearchLastName(string last, Contact &val);//return true if found then data is stored in val
	bool SearchFirstName(string first, Contact &val);
	bool SearchDateOfBirth(Date DOB, Contact &val);
private:
	void genFirstNameKey(Contact& cont);
	void genLastNameKey(Contact& cont);
	void genDOBKey(Contact& cont);
	TwoThreeTree<Contact> FirstNameTree;
	TwoThreeTree<Contact> LastNameTree;
	TwoThreeTree<Contact> DOBTree;
};

#endif //CONTACTDATABASE_H