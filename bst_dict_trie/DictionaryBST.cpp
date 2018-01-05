#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	if (word.length() == 0)
		return false;
	if (s.find(word) != s.end())
		return false;
	s.insert(word);
	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	return s.find(word) != s.end();
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
