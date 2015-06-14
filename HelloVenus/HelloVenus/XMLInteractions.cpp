#include "XMLInteractions.h"

void DB::exp(string filename)
{
    outopenFile(filename);
    for (int i = 0; i < sizeContact; i++){
        
        Export << "<Contact>" << endl;
        Export << "\t" << "<first>" << Contacts[i].first << "</first>" << endl;
        Export << "\t" << "<last>" << Contacts[i].last << "</last>" << endl;
        Export << "\t" << "<DoB>" << Contacts[i].DoB.GetDay() << " " << Contacts[i].DoB.GetMonth() << " " << Contacts[i].DoB.GetYear() << "</DoB>" << endl;
        Export << "</Contact>" << endl;
    }
    outcloseFile();
    return;
}

//Adapting to aidans code thingies.
string DB::dealingWithAidan(string rawDateLine){
    regex pattern("/");
    string rawLine = regex_replace(rawDateLine, pattern, " ");
    return rawLine;
    
    
}


void DB::import(string filename)
{
    int it = sizeContact;
    
    inopenFile(filename);
    while (getline(Import, rawLine))// && rawLine == "<Contact>")
    {
        //cout << "da raw line is: " << rawLine << endl;
        Contacts.push_back(push);
        sizeContact++;
        getline(Import, rawLine);
        regex pattern1("<first>");
        regex pattern2("</first>");
        regex pattern7("[^a-zA-Z1-9/]");
        Contacts[it].first = extractvar(rawLine, pattern1, pattern2);
        Contacts[it].first = removespace(Contacts[it].first, pattern7);
        getline(Import, rawLine);
        regex pattern3("<last>");
        regex pattern4("</last>");
        Contacts[it].last = extractvar(rawLine, pattern3, pattern4);
        Contacts[it].last = removespace(Contacts[it].last, pattern7);
        getline(Import, rawLine);
        regex pattern5("<DoB>");
        regex pattern6("</DoB>");
        string rawDoBString = extractvar(rawLine, pattern5, pattern6);
        rawDoBString = dealingWithAidan(rawDoBString);
        
        istringstream iss(rawDoBString);
        
        int day = 0, month = 0, year = 0;
        
        do
        {
            string sub;
            iss >> sub;
            cout << "Substring: " << sub << endl;
            if (!day)
            {
                day = stoi(sub);
            }
            else
            {
                if (!month)
                {
                    month = stoi(sub);
                }
                else
                {
                    if (!year)
                    {
                        year = stoi(sub);
                    }
                }
            }
        } while (iss);
        

        
        Contacts[it].DoB = Date( day, month, year);
        //Contacts[it].DoB = removespace(Contacts[it].DoB, pattern7);
        //Contacts[it].DoB = Date(0, 0, 0);
        getline(Import, rawLine);
        rawLine = "";
        cout << "\t" << Contacts[it].first << endl;
        cout << "\t" << Contacts[it].last << endl;
        cout << "\t";
        Contacts[it].DoB.PrintDate();
        cout << endl;
        it++;
    }
    incloseFile();
    return;
}
string DB::removespace(string rawLine, regex pattern)
{
    string result;
    result = regex_replace(rawLine, pattern, "");
    return result;
}

string DB::extractvar(string rawLine, regex pattern, regex pattern2)
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
void DB::outopenFile(string filename)
{
    Export.open(filename + ".txt");
    if (!Export.is_open()){
        cout << "Error: Could not open file!" << endl;
        return;
    }
}

void DB::inopenFile(string filename)
{
    Import.open(filename + ".txt");
    if (!Import.is_open()){
        cout << "Error: Could not open file!" << endl;
        return;
    }
}

void DB::outcloseFile()
{
    Export.close();
    return;
}

void DB::incloseFile()
{
    Import.close();
    return;
}

// ********************************* DEBUGGING FUNCTIONS *************************************************

void DB::DEBUGCOTROLL()
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

void DB::setup()
{
    int i = sizeContact;
    string again;
    do {
        Contacts.push_back(push);
        sizeContact++;
        cout << "first: ";
        cin >> Contacts[i].first;
        cout << endl << "last: ";
        cin >> Contacts[i].last;
        cout << endl << "DoB: ";
        int day, month, year;
        cin >> day;
        cin >> month;
        cin >> year;
        Contacts[i].DoB = Date(day, month, year);
        cout << endl;
        
        i++;
        cout << "Again? y/n" << endl;
        cin >>  again;
    } while (again == "y");
    return;
}
