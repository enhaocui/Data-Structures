/*
Enhao Cui
A53202267
CSE 100 PA4
Actorconnections.cpp
This is the main cpp for actor connections. It takes two actor/actress names as arguments, 
and it returns in which year earliest did the two actors/actresses become connected.
*/
#include <iostream>
#include "util.h"
#include <fstream>
#include "ActorGraph.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 4) {
		cout<<"More args needed!"<<endl;
		return -1;
	}
	char* movie_ca = argv[1]; //input actor and film list
	char* pairs = argv[2]; // input actor pairs
	char* output = argv[3]; // output file name
	char* b_or_u; // use bfs or ufind
	if (argc == 4) {
		b_or_u = "ufind"; //ufind by default
	}
	else {
		b_or_u = argv[4];
	}
	vector<vector<string>> actors;
	util::parsePairs(pairs, actors); //generate a vector of actor pairs
	unordered_map<int, vector<vector<string>>> year_to_edge;
	util::parseEdges(movie_ca, year_to_edge); // generate a map which maps years to a list of edges at that year
	string mode(b_or_u);
	vector<int> result;
	ActorGraph graph;
	if (mode == "ufind") {
		result = graph.unionFindYear(year_to_edge, actors); //unionfind
	}
	else if (mode == "bfs") {
		result = graph.findYear(year_to_edge, actors); //bfs
	}
	else {
		cout<<"Wrong flag!"<<endl; //exception
		return -1;
	}
	ofstream outfile(output); //cout header
	outfile<<"Actor1\tActor2\tYear"<<endl; 
	for (int i = 0; i < actors.size(); ++i) {
		outfile<<actors[i][0]<<"\t"<<actors[i][1]<<"\t"<<result[i]<<endl;
	}
	outfile.close();
	return 0;
}

