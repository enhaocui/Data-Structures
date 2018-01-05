/*
Author: Enhao Cui
CSE 100 PA2
A53202267
The program for benchmarking different dicts.
*/
#include "util.h"
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 5) {
		cout<<"Need more input arguments"<<endl;
		return -1;
	}
	int min_size = stoi(string(argv[1]));
	int step_size = stoi(string(argv[2]));
	int num_iterations = stoi(string(argv[3]));
	string dictfile = string(argv[4]);
	
	
	DictionaryTrie trie;
	Timer timer;

	//Test for hashtable
	cout<<"hashtable"<<endl;
	for (int iterations = 0; iterations < num_iterations; ++iterations) {
		ifstream infile(dictfile);
		DictionaryHashtable* hashtable = new DictionaryHashtable();
		Utils::load_dict(*hashtable, infile, min_size + iterations*step_size);
		string line = "";
		long long totaltime = 0;
		for (int j = 0; j < 100; j ++) { // for each iterations, run 100 times and take average
    		for (int i = 0; i < 100; ++i) {
        		getline(infile, line);
        		if (infile.eof()) {
            		std::cout << "Warning!  Only " << i << " words read from file." << endl;
            		break;
        		}
        		int count = 0;
    			string::iterator last = line.end();
    			for (string::iterator it = line.begin(); it != last; ++it) {
        			count++;
        			if (*it == ' ') {
            			break;
        			}
    			}
    			line.erase(0, count);
        		timer.begin_timer();
        		hashtable->find(line);
        		totaltime += timer.end_timer();
    		}
    	}
    	delete hashtable;
    	totaltime /= 100;
    	cout<<min_size + iterations*step_size << "\t"<<totaltime<<endl; //Output results

	}

	cout<<"BST"<<endl;
	for (int iterations = 0; iterations < num_iterations; ++iterations) {
		ifstream infile(dictfile);
		DictionaryBST* bst = new DictionaryBST();
		Utils::load_dict(*bst, infile, min_size + iterations*step_size);
		string line = "";
		long long totaltime = 0;
		for (int j = 0; j < 100; j ++) {
    		for (int i = 0; i < 100; ++i) {
        		getline(infile, line);
        		if (infile.eof()) {
            		std::cout << "Warning!  Only " << i << " words read from file." << endl;
            		break;
        		}
        		int count = 0;
    			string::iterator last = line.end();
    			for (string::iterator it = line.begin(); it != last; ++it) {
        			count++;
        			if (*it == ' ') {
            			break;
        			}
    			}
    			line.erase(0, count);
        		timer.begin_timer();
        		bst->find(line);
        		totaltime += timer.end_timer();
    		}
    	}
    	delete bst;
    	totaltime /= 100;
    	cout<< min_size + iterations*step_size << "\t"<<totaltime<<endl;

	}

	cout<<"Trie"<<endl;
	for (int iterations = 0; iterations < num_iterations; ++iterations) {
		ifstream infile(dictfile);
		DictionaryTrie* trie = new DictionaryTrie();
		Utils::load_dict(*trie, infile, min_size + iterations*step_size);
		string line = "";
		long long totaltime = 0;
		for (int j = 0; j < 100; j ++) {
    		for (int i = 0; i < 100; ++i) {
        		getline(infile, line);
        		if (infile.eof()) {
            		std::cout << "Warning!  Only " << i << " words read from file." << endl;
            		break;
        		}
        		int count = 0;
    			string::iterator last = line.end();
    			for (string::iterator it = line.begin(); it != last; ++it) {
        			count++;
        			if (*it == ' ') {
            			break;
        			}
    			}
    			line.erase(0, count);
        		timer.begin_timer();
        		trie->find(line);
        		totaltime += timer.end_timer();
    		}
    	}
    	delete trie;
    	totaltime /= 100;
    	cout<< min_size + iterations*step_size << "\t"<<totaltime<<endl;

	}
	return 0;
};

