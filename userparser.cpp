/***********************************************************************
 * AUTHOR     : Jeffrey Adams
 * CLASS      : CS1C T/TH 12:30pm-2:50pm
 **********************************************************************/

#include "userparser.h"

//FUNCTION - CLOSES INPUT FILE
void UserParser::close()
{
    if(mInputFile.is_open())
    {
        //CLOSES INPUT FILE
        mInputFile.close();
        
        //CLEARS FILE PATH
        mInputFilePath.clear();
    }
}

//FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
bool UserParser::loadFile(const std::string& filePath)
{
    //OPENS INPUT FILE
    mInputFile.open(filePath);
    
    //COPY FILE PATH INTO PRIVATE DATA PATH
    mInputFilePath = filePath;

    return mInputFile.is_open();
}

//FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
bool UserParser::parse(Vector<User>& userVector)
{
    if(!mInputFile.is_open())
    {
        return false;
    }
    
    //LOCAL VARIABLES
    User        user;
    std::string inputLine;
    int         inputType = 0;

    while(mInputFile >> inputLine)
    {
        if(inputType == 0)
        {
            //CLEARS INPUT LINE
            user.mUsername = inputLine.c_str();
            
            //INCREMENTS INPUT TYPE
            ++inputType;
        }
        else if(inputType == 1)
        {
            //CLEARS INPUT LINE
            user.mPassword = inputLine.c_str();
            
            //INCREMENTS INPUT TYPE
            ++inputType;
        }
        else
        {
            if(inputLine == "0")
            {
                user.mIsAdmin = false;
            }
            else if(inputLine == "1")
            {
                user.mIsAdmin = true;
            }
            else
            {
                return false;
            }

            userVector.push_back(user);
            
            //CLEARS USERNAME
            user.mUsername.clear();
            
            //CLEARS PASSWORD
            user.mPassword.clear();
            
            //CLEARS ADMIN
            user.mIsAdmin = 0;
            
            inputType = 0;
        }
    }

    return true;
}
