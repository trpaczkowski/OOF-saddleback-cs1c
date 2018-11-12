#ifndef USERPARSER_H
#define USERPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include "custom_vector.h"

/***********************************************************************
 *  File: userparser.h
 *  Description: Parses a file to add users to a users list.
 ***********************************************************************/

/***********************************************************************
 *  Parses a file that contains shape information and converts them into 
 *  shapes to be used by the program.
 ***********************************************************************/

//STRUCT - STORES THE USERS INFORMATION
struct User
{
    QString mUsername;  // Variable stores username
    QString mPassword;  // Variable stores password
    bool    mIsAdmin;   // Variable stores priviledges
};

class UserParser
{
public:
	
    //DEFAULT CONSTRUCTOR
    UserParser() {}
	
    //DECONSTRUCTOR & CLOSES INPUT FILE
    ~UserParser() { close(); }

    //FUNCTION - CLOSES INPUT FILE
    void close();

    //FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
    bool loadFile(const std::string& filePath);

    //FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
    bool parse(Vector<User>& userVector);

private:
	
    std::string   mInputFilePath;  // Variable defines input file path
    std::ifstream mInputFile;      // Variable defines input file
};

#endif
