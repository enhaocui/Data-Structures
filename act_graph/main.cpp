/*
Enhao Cui
A53202267
CSE 100 PA4
main.cpp
This is the code file for counting neighbours in this PA.
*/
#include "ActorGraph.h"
#include "Graph.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 4) {
		cout<<"More args needed!"<<endl;
		return -1;
	}
	char* movie_ca = argv[1];
	char* test_nei = argv[2];
	char* output = argv[3];
	ActorGraph graph;
	graph.loadFromFile(movie_ca, false); //Create graph
	graph.countNei(test_nei, output); // count neighbours
}