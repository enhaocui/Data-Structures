/*
Enhao Cui
A53202267
CSE 100 PA4
utils.cpp
the header file for some utility functions that are useful for many classes
*/
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace util {
using namespace std;

//parse the actor pairs query file into a vector of actor pairs
void parsePairs(const char* pairs, vector<vector<string>>& result) {
	ifstream infile(pairs);
	bool header = false;
	while (infile) {
		string s;
		if (!getline(infile, s))	break;
		if (!header) {
			header = true;
			continue;
		}
		cout << s <<endl;
		istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      record.push_back( next );
    }
		if (record.size() != 2) {
      // we should have exactly 2 columns
      cout<<record.size()<<endl;
      cout<<"size wrong!"<<endl;
      continue;
    }
    result.push_back(record);
	}
	infile.close();
}

//parse the movie_cast.tsv into a map which maps year to a list of movies and actors of that year
void parseEdges(const char* movie_ca, unordered_map<int, vector<vector<string>>>& result) {
	ifstream infile(movie_ca);
	bool header = false;
	while (infile) {
		string s;
		if (!getline(infile, s))	break;
		if (!header) {
			header = true;
			continue;
		}
		istringstream ss( s );
       	vector <string> record;

       	while (ss) {
            string next;
           	// get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;
            record.push_back( next );
        }
		if (record.size() != 3) {
            	// we should have exactly 3 columns
            cout<<record.size()<<endl;
            cout<<"size wrong!"<<endl;
            continue;
       	}
       	int year = stoi(record[2]);
       	string actor = record[0];
       	string movie = record[1];
        // each edge entry has a movie title and an actor name
       	if (result.find(year) == result.end()) {
       		result[year] = vector<vector<string>>();
       	}
       	vector<string> entry;
       	entry.push_back(actor);
       	entry.push_back(movie);
       	result[year].push_back(entry);
	}
	infile.close();
}
}
#endif