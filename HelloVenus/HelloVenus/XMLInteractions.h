//
//  XMLInteractions.h
//  
//
//  Created by Michael Zuccarino on 6/14/15.
//
//

#ifndef ____XMLInteractions__
#define ____XMLInteractions__


#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include "Contact.h"
#include <sstream>

using namespace std;

class DB
{
private:
    vector<Contact> Contacts;
    ifstream Import;
    ofstream Export;
    string rawLine;
    int sizeContact = 0;
    Contact push;
    
public:
    void exp(string filename);
    void import(string filename);
    string removespace(string rawLine, regex pattern);
    string extractvar(string rawLine, regex pattern, regex pattern2);
    void outopenFile(string filename);
    void inopenFile(string filename);
    void outcloseFile();
    void incloseFile();
    string dealingWithAidan(string rawDateLine);
    
    // ********************************* DEBUGGING FUNCTIONS *************************************************
    void DEBUGCOTROLL();
    void setup();
    //********************************************************************************************************************
    
    
};




#endif /* defined(____XMLInteractions__) */
