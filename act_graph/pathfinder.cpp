/*
Enhao Cui
A53202267
CSE 100 PA4
pathfinder.cpp
This is the main cpp for fathfinder. It takes two actor/actress names as arguments, 
and it returns the shortest weighted/unweighted path between them.
*/

#include "ActorGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "util.h"
//#include <string.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 5) {
		cout<<"More args needed!"<<endl;
		return -1;
	}
	char* movie_ca = argv[1]; //movie_cast.tsv
	char* weighted = argv[2]; //weighted or not 
	char* pairs = argv[3]; //actor pairs
	char* output = argv[4]; // output file
	bool use_weighted = false;
	if (strncmp(weighted, "w", 1) == 0)
		use_weighted = true;
	else if (strncmp(weighted, "u", 1) != 0) {
		cout<<"weighted flag wrong!"<<endl; //exception
		return -1;
	}
	ActorGraph graph;
	graph.loadFromFile(movie_ca, use_weighted); //create graph
	vector<vector<string>> actors;
	util::parsePairs(pairs, actors); //generate a list of actor pairs for query
	vector<string> result;
	for (auto& record : actors) { //calculate paths
		if (record[0] == record[1])	continue;
		if (use_weighted)
        	result.push_back(graph.findWeightedPath(record[0], record[1]));
        else
        	result.push_back(graph.findUnweightedPath(record[0], record[1]));
	}
	ofstream outfile(output);
	outfile<<"(actor)--[movie#@year]-->(actor)--..."<<endl;
	for (auto& s : result) {
		outfile<<s<<endl;
	}
	outfile.close();
	return 0;
}