/****************************************************************
*  File: HashedSplays.cpp
*  Created on: November 2, 2014
*
*  This file contains the implementation for the HashedSplays class that is used
* as the main base class for the project. HashedSplays holds all of the splay
* trees and whose methods mainly output the contents of those trees.
*
****************************************************************/

#include "HashedSplays.h"

HashedSplays::HashedSplays(int size)
{
	table = new SplayTree<Node>[size];
	m_trees = size;
}

HashedSplays::~HashedSplays(void)
{
	delete [] table;
	table = NULL;
}

void HashedSplays::FileReader(string inFileName)
{
	//first need to check and make sure that the file exists
	if (Util::FileExists(inFileName.c_str()))
	{
		//initializing an input stream
		ifstream input;
		input.open(inFileName.c_str(), ios_base::in);
		string token = "";

		while (!input.eof())
		{
			//need to read in the token and then clean it to remove mis-capitalized words
			//and punctuation at the front and back
			input >> token;

			//need to remove all punctuation from the word
			token = Util::Strip(token);

			Node node(token, 1);
			//now need to search for the node in the appropriate tree
			if (!token.empty())
			{
				if (table[GetIndex(token.substr(0, 1))].contains(node))
				{
					//increment it's frequency if it exists
					table[GetIndex(token.substr(0, 1))].getComparable().IncrementFrequency();
				}
				else
				{
					//insert the node if it doesn't already exist
					table[GetIndex(token.substr(0, 1))].insert(node);
				}
			}
		}

		//need to close the stream
		input.close();
	}
}

void HashedSplays::PrintTree(int index)
{
	table[index].printTree();
	if (table[index].getCount() > 0)
	{
		cout << "This tree had " << table[index].getSplayCount() << " splays." << endl;
	}
}

void HashedSplays::PrintTree(string letter)
{
	//same as the above method except have to convert letter to the appropriate index first
	table[GetIndex(letter)].printTree();
	if (table[GetIndex(letter)].getCount() > 0)
	{
		cout << "This tree had " << table[GetIndex(letter)].getSplayCount() << " splays." << endl;
	}
}

void HashedSplays::PrintHashCountResults()
{
	//iterate over the table and only print the trees that are not empty
	for (int i = 0; i < m_trees; i++)
	{
		if (table[i].getCount() > 0)
		{
			cout << "This tree starts with " << table[i].getComparable()
				<< " and has " << table[i].getCount() << " nodes." << endl;
		}
		else
		{
			cout << "This tree has no nodes." << endl;
		}
	}
}

void HashedSplays::FindAll(string inPart)
{
	
	Node node(inPart, 0);
	cout << "Printing the results of the nodes that start with '" << inPart << "'" << endl;
	table[GetIndex(inPart)].printDerivatives(node);
}

int HashedSplays::GetIndex(string inLetter)
{
	return (inLetter[0] - 'A') % charOffset;
}
