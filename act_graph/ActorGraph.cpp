/*
 * ActorGraph.cpp
 * Author: Enhao Cui
 * Date:   12/6/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include "ActorGraph.h"
#include <queue>

using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
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
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
        
        // we have an actor/movie relationship, now what?
        // maps movie to actors

        string key = movie_title + " " + to_string(movie_year);
        if (ac_to_node.find(actor_name) == ac_to_node.end()) {
            ac_to_node[actor_name] = new ActorNode(actor_name);
        }
        if (mv_to_node.find(key) == mv_to_node.end()) {
            mv_to_node[key] = new ActorEdge(movie_title, movie_year);
        }

        ActorNode* actor_node = ac_to_node[actor_name];
        ActorEdge* actor_edge = mv_to_node[key];
        // add an edge to actor
        actor_node->addEdge(actor_edge);
        // add an actor to edge
        actor_edge->addActor(actor_node);

        if (mv_to_ac.find(key) == mv_to_ac.end()) {
            mv_to_ac[key] = vector<string>();
        }
        // adds actor name to mv_to_ac list
        mv_to_ac[key].push_back(actor_name);
       // cout<<actor_name<<endl;
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    ActorGraph::createMap();

    return true;
}

bool ActorGraph::countNei(const char* in_filename, const char* out_filename) {
    // print the number of neighbours
    ifstream infile(in_filename);
    ofstream outfile(out_filename);
    outfile<<"Number of Neighbors"<<endl;
    bool header = false;
    while (infile) {
        string actor;

        // get the next line
        if (!getline( infile, actor )) break;

        if (!header) {
            // skip the header
            header = true;
            continue;
        }

        int count = ac_to_ac[actor].size();

        outfile<<count<<endl;
    }
    infile.close();
    outfile.close();
    return true;
}

void ActorGraph::createMap() {
    for (auto& entry: mv_to_ac) {
        vector<string>& v = entry.second;
        unordered_set<string> s;
        // insert all actors into a set
        // while creating the entry for this actor in map
        for (auto str: v) {
            s.insert(str);
            if (ac_to_ac.find(str) == ac_to_ac.end())
                ac_to_ac[str] = unordered_set<string>();
        }
        //For every actor in the vector, add all other actors to its value in the map
        for (auto str: v) {
            s.erase(str);
            for (auto temp : s) {
                ac_to_ac[str].insert(temp);
            }
            s.insert(str);
        }
    }
}

string ActorGraph::findUnweightedPath(string& actor1, string& actor2) {
    // find unweighted path of two actors
    if (ac_to_node.find(actor1) == ac_to_node.end() || ac_to_node.find(actor2) == ac_to_node.end()) {
       // cout<<"Actor(s) not exist!"<<endl;
        return "";
    }
    // Simply do a naive bfs
    queue<string> actors;
    queue<string> paths;
    unordered_set<string> visited;
    actors.push(actor1);
    paths.push("(" + actor1 + ")");
    visited.insert(actor1);
    while (!actors.empty()) {
        string actor = actors.front();
        actors.pop();
        string path = paths.front();
        paths.pop();
        if (actor == actor2)    return path;
        for (ActorEdge* movie : ac_to_node[actor]->edges) {
            Movie* mv = movie->movie;
            string p = "--[" + mv->name + "#@" + to_string(mv->year) + "]-->";
            for (ActorNode* next : movie->actors) {
                string& nextname = next->name;
                if (visited.find(nextname) != visited.end())  continue;
                visited.insert(nextname);
                actors.push(nextname);
                paths.push(path + p + "(" + nextname + ")");
            }
        }
    }
    return "";
}

string ActorGraph::findWeightedPath(string& actor1, string& actor2) {
    if (ac_to_node.find(actor1) == ac_to_node.end() || ac_to_node.find(actor2) == ac_to_node.end()) {
       // cout<<"Actor(s) not exist!"<<endl;
        return "";
    }
    for (auto& entry : ac_to_node) {
        //Initialize all nodes
        entry.second->reset();
    }
    // Run dijkstra
    priority_queue<ActorNode*, vector<ActorNode*>, compare> pq;
    ac_to_node[actor1]->dist = 0;
    pq.push(ac_to_node[actor1]);
    while (!pq.empty()) {
        ActorNode* node = pq.top();
        pq.pop();
        if (node->name == actor2)
            break;
        if (!node->done) {
            node->done = true;
            for (auto edge : node->edges) {
                int weight = edge->weight;
                for (auto actor : edge->actors) {
                    if (actor->name == node->name)  continue;
                    int c = node->dist + weight;
                    if (c < actor->dist) {
                        actor->prev = node;
                        actor-> dist = c;
                        actor->in_edge = edge;
                        pq.push(actor);
                    }
                }
            }
        }
    }
    string res = "";
    ActorNode* node = ac_to_node[actor2];
    while(node->name != actor1) {
        res = "--[" + (node->in_edge->movie->name + "#@" + 
            to_string(node->in_edge->movie->year)) + "]-->(" + node->name + ")" + res;
        node = node->prev;
    }
    return "[" + actor1 + "]" + res;
}

vector<int> ActorGraph::findYear(unordered_map<int, vector<vector<string>>>& year_to_edge, vector<vector<string>>& actors) {
    // find the year the actors first connected
    vector<int> res(actors.size(), 9999);
    int counter = 0;
    // Traverse through all years, each time add all edges of this year to the graph
    // Then find if there exists a path between actors
    for (int i = 0; i <= 2015; i ++) {
        // all the years are found, return
        if (counter == actors.size())
            break;
        if (year_to_edge.find(i) == year_to_edge.end())  {
            continue;
        }
        addEdges(i, year_to_edge[i]);
        for (int j = 0; j < actors.size(); j ++) {
            if (res[j] != 9999)    continue;
            string& start = actors[j][0];
            string& end = actors[j][1];
            if (findUnweightedPath(start, end) != "") {
                res[j] = i;
                counter ++;
            }
        }
    }
    return res;
}

void ActorGraph::addEdges(int movie_year, vector<vector<string>>& edges) {
    // uodate edges to the graph
    for (auto& v : edges) {
        string& actor_name = v[0];
        string& movie_title = v[1];
        string key = movie_title + " " + to_string(movie_year);
        if (ac_to_node.find(actor_name) == ac_to_node.end()) {
            ac_to_node[actor_name] = new ActorNode(actor_name);
        }
        if (mv_to_node.find(key) == mv_to_node.end()) {
            mv_to_node[key] = new ActorEdge(movie_title, movie_year);
        }
        ActorNode* actor_node = ac_to_node[actor_name];
        ActorEdge* actor_edge = mv_to_node[key];
        actor_node->addEdge(actor_edge);
        actor_edge->addActor(actor_node);
        if (mv_to_ac.find(key) == mv_to_ac.end()) {
            mv_to_ac[key] = vector<string>();
        }
        mv_to_ac[key].push_back(actor_name);
    }
}
/*
int ActorGraph::unionFindYear(unordered_map<int, vector<vector<string>>>& year_to_edge, string& start, string& end) {

    for (int i = 0; i <= 2015; i ++) {
        if (year_to_edge.find(i) == year_to_edge.end())  {
            continue;
        }
        addEntries(i, year_to_edge[i]);
        if (root.find(start) != root.end() && root.find(end) != root.end() && find(start) == find(end))    return i;
    }
    return 9999;
}
*/
vector<int> ActorGraph::unionFindYear(unordered_map<int, vector<vector<string>>>& year_to_edge, vector<vector<string>>& actors) {
    vector<int> res(actors.size());
    int counter = 0;
    // traverse through all the years
    for (int i = 0; i <= 2015; i ++) {
        // counter all actors connections are found
        if (counter == actors.size())
            break;
        if (year_to_edge.find(i) == year_to_edge.end())  {
            continue;
        }
        // add all edges of this year to the map
        addEntries(i, year_to_edge[i]);
        // perform union find on every actor
        for (int j = 0; j < actors.size(); j ++) {
            if (res[j] != 0)    continue;
            string& start = actors[j][0];
            string& end = actors[j][1];
            // start and end are connected
            if (root.find(start) != root.end() && root.find(end) != root.end() && find(start) == find(end)) {
                res[j] = i;
                counter ++;
            }
        }
    }
    return res;
}

void ActorGraph::addEntries(int movie_year, vector<vector<string>>& edges) {
    for (auto& v : edges) {
        string& actor_name = v[0];
        string& movie_title = v[1];
        string key = movie_title + " " + to_string(movie_year);
        if (mv_to_ac.find(key) == mv_to_ac.end()) {
            mv_to_ac[key] = vector<string>();
        }
        // create a root entry in the map
        if (root.find(actor_name) == root.end()) {
            root[actor_name] = actor_name;
            root_size[actor_name] = 1;
        }
        //afind(actor_name);
        //union all the actors of this movie
        for (auto& actor : mv_to_ac[key]) {
            unionn(actor, actor_name);
        }
        mv_to_ac[key].push_back(actor_name);
    }
}

string ActorGraph::find(string actor) {
    while (root[actor] != actor) {
        root[actor] = root[root[actor]]; //path compression
        actor = root[actor];
    }
    return actor;
}

void ActorGraph::unionn(string& actor1, string& actor2) {
    string root1 = find(actor1);
    string root2 = find(actor2);
    // always merge the smaller set with the larger set to make tree lower
    if (root_size[root1] > root_size[root2]) {
        root_size[root1] += root_size[root2];
        root[root2] = root1;
    }
    else {
        root_size[root2] += root_size[root1];
        root[root1] = root2;
    }
}

ActorGraph::~ActorGraph() {
    // destruct all the actor nodes and actor edges
    for (auto& entry : ac_to_node) {
        delete entry.second;
    }
    for (auto& entry : mv_to_node) {
        delete entry.second;
    }
}









