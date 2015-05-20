#ifndef XMLInteractions
#define XMLInteractions

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

class DB
{
private:
	vector<Friends> Friend;
	ifstream Import;
	ofstream Export;
	string rawLine;
	int sizeFriend = 0;
	Friends push;

public:

	void exp(string filename)
	{
		outopenFile(filename);
		for (int i = 0; i < sizeFriend; i++){

			Export << "<friend>" << endl;
			Export << "\t" << "<first>" << Friend[i].first << "</first>" << endl;
			Export << "\t" << "<last>" << Friend[i].last << "</last>" << endl;
			Export << "\t" << "<DoB>" << Friend[i].DoB << "</DoB>" << endl;
			Export << "</friend>" << endl;
		}
		outcloseFile();
		return;
	}


	void import(string filename)
	{
		int it = sizeFriend;

		inopenFile(filename);

		while (getline(Import, rawLine) && rawLine == "<friend>")
		{
			Friend.push_back(push);
			sizeFriend++;
			getline(Import, rawLine);
			regex pattern1("<first>");
			regex pattern2("</first>");
			regex pattern7("[^a-zA-Z1-9/]");
			Friend[it].first = extractvar(rawLine, pattern1, pattern2);
			Friend[it].first = removespace(Friend[it].first, pattern7);
			getline(Import, rawLine);
			regex pattern3("<last>");
			regex pattern4("</last>");
			Friend[it].last = extractvar(rawLine, pattern3, pattern4);
			Friend[it].last = removespace(Friend[it].last, pattern7);
			getline(Import, rawLine);
			regex pattern5("<DoB>");
			regex pattern6("</DoB>");
			Friend[it].DoB = extractvar(rawLine, pattern5, pattern6);	
			Friend[it].DoB = removespace(Friend[it].DoB, pattern7);
			getline(Import, rawLine);
			rawLine = "";
			cout << Friend[it].first << endl;
			cout << Friend[it].last << endl;
			cout << Friend[it].DoB << endl;
			it++;
		}
		incloseFile();
		return;
	}
	string removespace(string rawLine, regex pattern)
	{
		string result;
		result = regex_replace(rawLine, pattern, "");
		return result;
	}

	string extractvar(string rawLine, regex pattern, regex pattern2)
	{
		bool found = NULL;
		string result;
		found = regex_search(rawLine.begin(), rawLine.end(), pattern);
		if (found == true){
			rawLine = regex_replace(rawLine, pattern, "");
			result = regex_replace(rawLine, pattern2, "");
		}
		else	{
			cout << "ERROR, Pattern not found!" << endl;
			return "ERROR";
		}
		return result;
	}
	void outopenFile(string filename)
	{
		Export.open(filename + ".txt");
		if (!Export.is_open()){
			cout << "Error: Could not open file!" << endl;
			return;
		}
	}

	void inopenFile(string filename)
	{
		Import.open(filename + ".txt");
		if (!Import.is_open()){
			cout << "Error: Could not open file!" << endl;
			return;
		}
	}

	void outcloseFile()
	{
		Export.close();
		return;
	}

	void incloseFile()
	{
		Import.close();
		return;
	}

	// ********************************* DEBUGGING FUNCTIONS *************************************************

	void DEBUGCOTROLL()
	{
		int choise;
		string file;
		do{
			choise = 0;
			cout << "1. import" << endl << "2. export" << endl << "3. setup" << endl << "4. Exit" << endl;
			cin >> choise;
			switch (choise){
				case 1:
					cin >> file;
					import(file);
					break;
				case 2:
					cin >> file;
					exp(file);
					break;
				case 3:
					setup();
					break;
				default:
					break;
			}
		} while (choise != 4 || choise < 4);
	}

	void setup()
	{
		int i = sizeFriend;
		string again;
		do {
			Friend.push_back(push);
			sizeFriend++;
			cout << "first: ";
			cin >> Friend[i].first;
			cout << endl << "last: ";
			cin >> Friend[i].last;
			cout << endl << "DoB: ";
			cin >> Friend[i].DoB;
			cout << endl;

			i++;
			cout << "Again? y/n" << endl;
			cin >>  again;
		} while (again == "y");
		return;
	}

//********************************************************************************************************************


};


