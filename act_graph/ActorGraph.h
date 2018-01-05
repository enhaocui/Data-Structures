/*
 * ActorGraph.h
 * Author: Enhao Cui
 * Date:   12/6/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "Graph.h"

// Maybe include some data structures here

using namespace std;

class ActorGraph {
    protected:

        unordered_map<string, vector<string>> mv_to_ac; //maps movies to a list of starring actors
        unordered_map<string, unordered_set<string>> ac_to_ac; //maps actors to a set of all actors connected
        unordered_map<string, ActorNode*> ac_to_node; //maps actor name to actor node
        unordered_map<string, ActorEdge*> mv_to_node; //maps movie name to actor edges
        unordered_map<string, string> root; // root for union find
        unordered_map<string, int> root_size; // the size of node set 
        // creates a map from actors to all connected actors
        void createMap();
        // add all edges of a year to the graph
        void addEdges(int year, vector<vector<string>>& edges);
        // add entry to mv_to_ac
        void addEntries(int year, vector<vector<string>>& edges);
        // find root
        string find(string actor);
        // union the sets
        void unionn(string& actor1, string& actor2);

        // Maybe add class data structure(s) here

    public:
        ActorGraph(void);
        ~ActorGraph();

        // Maybe add some more methods here

        /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie relationships.
         *
         * in_filename - input filename
         * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
        bool loadFromFile(const char* in_filename, bool use_weighted_edges);
        //count num of neighbours
        bool countNei(const char* in_filename, const char* out_filename); 
        //find the unweighted path between two actors
        string findUnweightedPath(string& actor1, string& actor2);
        //find the weighted path between two actors
        string findWeightedPath(string& actor1, string& actor2);
        //use bfs to find the earliest year the two actors connected
        vector<int> findYear(unordered_map<int, vector<vector<string>>>& year_to_edge, vector<vector<string>>& actors);
        //use union find to find the earliest year the two actors connected
        vector<int> unionFindYear(unordered_map<int, vector<vector<string>>>& year_to_edge, vector<vector<string>>& actors);
};


#endif // ACTORGRAPH_H
