/*
Enhao Cui
A53202267
CSE 100 PA4
Graph.h
This is the header file for the simple data structures used in this PA. Namely, they are: ActorNode, ActorEdge, and Movie
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

//A Movie consists of a name and a year
struct Movie {
	string name;
	int year;
	//int weight;
	Movie(string movie, int y) {
		name = movie;
		year = y;
	//	weight = 2015 - year + 1;
		//dist = INT_MAX;
	}
	~Movie() {
	}
};
//forward declaration of ActorNode
struct ActorNode;
//An Actor Edge is basically a movie with a list of all actors/actresses starring in it
struct ActorEdge {
	vector<ActorNode*> actors;
	Movie* movie;
	int weight;
	ActorEdge(string& mov, int year) {
		movie = new Movie(mov, year);
		weight = 2015 - movie->year + 1;

	}
	void addActor(ActorNode* actor) {
		actors.push_back(actor);
	}
	~ActorEdge() {
		delete movie;
	}
};
//An Actor Node has several members: the actor name, a list of all the actor edges connected to this actor,
//prev, in_edge, dist, and done used in pathfinder
struct ActorNode {
	vector<ActorEdge*> edges;
	string name;
	int dist;
	ActorNode* prev;
	ActorEdge* in_edge;
	bool done;
	//initialization
	ActorNode(string& n) {
		name = n;
		prev = NULL;
		done = false;
		dist = INT_MAX;
		in_edge = NULL;
	}
	void addEdge(ActorEdge* movie) {
		edges.push_back(movie);
	}
	void reset() {
		// Reinitialize
		prev = NULL;
		done = false;
		dist = INT_MAX;
		in_edge = NULL;
	}
	~ActorNode() {
	}
};

//Comparator for actornode
struct compare{
	bool operator()(const ActorNode* a1,const ActorNode* a2) const{
    	return a1->dist > a2->dist;
  	}
};

#endif