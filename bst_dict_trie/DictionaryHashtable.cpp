#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
	if (word.length() == 0)
		return false;
	if (s.find(word) != s.end())
		return false;
	s.insert(word);
	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
	return s.find(word) != s.end();
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
