#include "util.h"
#include "DictionaryTrie.h"
#include <iostream>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
	root.freq = -1;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	if (word.length() == 0)
		return false;
	TrieNode *node = &root;
	for (int i = 0; i < word.length(); ++i) {
		int index;
		if (word[i] == ' ') {
			index = 26;
		}
		else {
			index = word[i] - 'a';
		}
		if ((node->children)[index] != nullptr) {
			node = node->children[index];
		}
		else {
			createNode(node, word, i, freq);
			return true;
		}
	}
	if ((long)(node->freq) == freq) {
		return false;
	}
	if ((long)freq > node->freq) { // without long, node->freq is converted to unsigned int, which makes -1 super big...
		if (node->freq != -1) {
			node->freq = freq;
			return false;
		}
		node->freq = freq;
		return true;
	}
  	return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	const TrieNode *node = &root;
	for (auto c : word) {
		int index;
		if (c == ' ') {
			index = 26;
		}
		else {
			index = c - 'a';
		}
		if (node->children[index] == nullptr) {
			return false;
		}
		else {
			node = node->children[index];
		}
	}
	if (node->freq != -1)
		return true;
  	return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  	std::vector<std::string> words;
  	if (prefix.length() == 0) {
  		std::cout<<"Invalid Input. Please retry with correct input." << std::endl;
  		return words;
  	}
  	TrieNode *node = &root;
  	std::string path = "";
  	for (auto c : prefix) {
  		if (!node) //prefix does not exist
  			return words;
  		path += c;
  		int index;
  		if (c == ' ')	index = 26;
  		else	index = (int)(c - 'a');
  		if (c != ' ' && (index > 25 || index < 0)) {
  			std::cout<<"Invalid Input. Please retry with correct input." << std::endl;
  			return words;
  		}
  		node = node->children[index];
  	}
  	std::priority_queue<WordF, std::vector<WordF>, Compare> pq;
  	dfs(node, path, pq, num_completions);
  	words.resize(pq.size());
  	int index = pq.size() - 1;
  	while (!pq.empty()) {
  		words[index--] = pq.top().word;
  		pq.pop();
  	}
  	return words;
}

void DictionaryTrie::createNode(TrieNode* node, std::string& word, int start, int freq) {
	while (start != word.length()) {
		int index;
		if (word[start] == ' ') {
			index = 26;
		}
		else {
			index = word[start] - 'a';
		}
		node->children[index] = new TrieNode();
		node = node->children[index];
		++start;
	}
	node->freq = freq;
}

void DictionaryTrie::deleteNode(TrieNode* node) {
	if (node == nullptr)
		return;
	for (TrieNode *n : node->children) {
		deleteNode(n);
	}
	delete node;
}

void DictionaryTrie::dfs(TrieNode* node, std::string word, std::priority_queue<WordF, std::vector<WordF>, Compare>& pq, int size) {
	if (!node)	return;
	if (node->freq != -1) {
		pq.push(WordF(node->freq,word));
	}
	if (pq.size() > size)
		pq.pop();
	for (int i = 0; i < 27; ++i) {
		char c;
		if (i != 26)
			c = (char)('a' + i);
		else
			c = ' ';
		dfs(node->children[i], word + c, pq, size);
	}
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	for (TrieNode *n : root.children) {
		deleteNode(n);
	}
}
