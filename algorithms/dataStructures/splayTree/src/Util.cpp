/****************************************************************
*  File: Util.cpp
*  Project: 2
*  Author: Robert Grossman
*  Created on: November 1, 2014
*  Section: 03
*  E-mail: rgross1@umbc.edu
*
*  This file contains the implementation for the Util class that is used
* as a static class for string manipulation.
*
****************************************************************/
#include "Util.h"

string Util::Lower(string inString)
{
	//need to make all letters starting at "start" lowercase
	for (unsigned int i = 0; i < inString.size(); i++)
	{
		inString[i] = tolower(inString[i]);
	}

	return inString;
}

string Util::Strip(string inString)
{
	//need to get rid of the punctuation marks at the front
	while (inString.size() > 0 && !isalpha(inString[0]))
	{
		inString = inString.substr(1, inString.size());
	}

	//need to get rid of the punctuation marks at the back
	while (inString.size() > 0 && !isalpha(inString[inString.size() - 1]))
	{
		inString = inString.substr(0, inString.size() - 1);
	}

	//need to get rid of the punctuation marks inside of the word
	string temp = "";
	bool previousPunctuation = false;
	for (int i = 0; i < inString.size(); i++)
	{
		//only add characters to the temp string that are not allowed punctuation
		if (isalpha(inString[i]))
		{
			temp.push_back(inString[i]);
			previousPunctuation = false;
		}

		if (previousPunctuation == false)
		{
			if (inString[i] == '\'' || inString[i] == '-')
			{
				temp.push_back(inString[i]);
				previousPunctuation = true;
			}
		}
	}

	inString = temp;

	return inString;

}

bool Util::FileExists(const char* fileName)
{
	ifstream infile;
	infile.open(fileName, ios_base::in);

	//check if the input stream worked
	if (infile.fail())
	{
		cout << "The file " << fileName << " failed to open!" << endl;
		infile.close();
		return false;
	}
	//close the input stream
	infile.close();

	//the file was able to be opened so return true
	return true;

}