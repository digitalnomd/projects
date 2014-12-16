/****************************************************************
*  File: HashedSplays.h
*  Project: 2
*  Author: Robert Grossman
*  Created on: November 2, 2014
*  Section: 03
*  E-mail: rgross1@umbc.edu
*
*  This file contains the interface for the HashedSplays class that is used
* as the main base class for the project. HashedSplays holds all of the splay
* trees and whose methods mainly output the contents of those trees.
*
****************************************************************/

#ifndef HASHED_SPLAYS_H
#define HASHED_SPLAYS_H

#include "SplayTree.h"
#include "Node.h"
#include "Util.h"
#include <fstream>
#include <string>
#include "Exceptions.h"
#include <iostream>
#define ALPHABET_SIZE 26
#define charOffset 32 //offset of uppercase from lowercase chars in ASCII
using namespace std;


class HashedSplays
{
public:

	/**********************************************************************
     * Name: HashedSplays (constructor)
     * PreCondition: size -- the number of splay trees contained in the hash table.
     * 
     * PostCondition:  Creates a hash table of size "size" and whose contents are
	 * splay trees.
     *********************************************************************/
	HashedSplays(int size);

	/**********************************************************************
     * Name: HashedSplays (destructor)
     * PreCondition: None
     * 
     * PostCondition:  Frees the dynamic memory associated with the HashedSplays object.
     *********************************************************************/
	~HashedSplays(void);

	/**********************************************************************
     * Name: FileReader
     * PreCondition: inFileName -- the input file in .txt format
     * 
     * PostCondition:  Reads in the contents of the specified file.
     *********************************************************************/
	void FileReader(string inFileName);

	/**********************************************************************
     * Name: PrintTree
     * PreCondition: index -- the index of the splay tree to be printed.
     * 
     * PostCondition:  Prints the splay tree at the specified index.
     *********************************************************************/
	void PrintTree(int index);

	/**********************************************************************
     * Name: PrintTree
     * PreCondition: inFileName -- the index of the splay tree to be printed.
     * 
     * PostCondition:  Prints the splay tree for the specified letter.
     *********************************************************************/
	void PrintTree(string letter);

	/**********************************************************************
     * Name: PrintHashCounts
     * PreCondition: None.
     * 
     * PostCondition:  Prints the first node in each splay three along with the number of nodes contained.
     *********************************************************************/
	void PrintHashCountResults();

	/**********************************************************************
     * Name: FindAll
     * PreCondition: inPart -- the start of the word 
     * 
     * PostCondition:  Prints all words that start with inPart.
     *********************************************************************/
	void FindAll(string inPart);

	/**********************************************************************
     * Name: GetIndex
     * PreCondition: inLetter-- the letter character
     * 
     * PostCondition:  Returns the numeric value consistent with the given letter.
     *********************************************************************/
	int GetIndex(string inLetter);

private:
	SplayTree<Node>* table;
	int m_trees;

};

#endif