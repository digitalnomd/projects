/****************************************************************
*  File: Util.h
*  Author: Robert Grossman
*  Created on: November 1, 2014
*  E-mail: rgross1@umbc.edu
*
*  This file contains the interface for the Util class that is used
* as a static class for string manipulation.
*
****************************************************************/


#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Util 
{

public:

	/**********************************************************************
     * Name: Lower
     * PreCondition: inString -- a tokenized word
     * PostCondition:  Returns the word with all lower case letters except for the first.
     *********************************************************************/
	static string Lower(string inString);

	/**********************************************************************
     * Name: Strip
     * PreCondition: inString -- a tokenized word
     * 
     * PostCondition:  Removes the punctuation from the word.
     *********************************************************************/
	static string Strip(string inString);

	/**********************************************************************
     * Name: FileExists
     * PreCondition: fileName -- name of the file to be read in.  
     * 
     * PostCondition:  Returns true if the file can be read in. False otherwise.
     *********************************************************************/
	static bool FileExists(const char* fileName);

};





#endif
