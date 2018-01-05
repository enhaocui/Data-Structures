/*
Author: Enhao Cui
CSE 100 PA3
A53202267
HC Tree cpp
*/
#include "HCTree.h"
#include <stack>

using namespace std;

void HCTree::build(const vector<int>& freqs) {
	//build the tree with the counted freq vector
	if (freqs.size() == 0)
		return;
	//PQ, sorted by the freqs of each char
	priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;
	for (int i = 0; i < freqs.size(); i ++) {
		if (freqs[i] == 0)
			continue;
		//Only construct nodes for non-zero occurence 
		HCNode* leaf = new HCNode(freqs[i], (byte)i);
		pq.push(leaf);
		leaves[i] = leaf;
	}
	//If we have only one node, add a sibling for it so we can still have a valid coding tree with one parent and two children
	if (pq.size() == 1) {
		HCNode* dummy = new HCNode(0, 255);
		pq.push(dummy);
	}
	//Iteratively gets two nodes from the pq, and then create a parent for them, then push back the parent
	while (pq.size() > 1) {
		HCNode* n0 = pq.top();
		pq.pop();
		HCNode* n1 = pq.top();
		pq.pop();
		HCNode* parent = new HCNode(n1->count + n0->count, 255);
		cout<<"n0 "<<n0->symbol<<" "<<"n1 "<<n1->symbol<<endl;
		//cout<<*n0<<" "<<*n1<<endl;
		parent->c0 = n0;
		parent->c1 = n1;
		n0->p = parent;
		n1->p = parent;
		pq.push(parent);
	}
	root = pq.top();
	pq.pop();
};

void HCTree::encode(byte symbol, BitOutputStream& out) const{
	//encode from bottom to top, each time we append to existing code
	string code = "";
	HCNode* leaf = leaves[symbol];
	while (leaf->p != 0) {
		if (leaf == leaf->p->c0) {
			code = "0" + code; // prepend to the code
		}
		else {
			code = "1" + code;
		}
		leaf = leaf->p;
	}
	for (auto c : code) {
		//write to the bit out put stream
		if (c == '1')
			out.push(true);
		else
			out.push(false);
	}
};

void HCTree::encode(byte symbol, ofstream& out) const{
	//Encode into char sequence, works similarly
	HCNode* leaf = leaves[(int)symbol];

	stack<byte> s;
	while (leaf->p != 0) {
		if (leaf == leaf->p->c0) {
			s.push('0');
		}
		else {
			s.push('1');
		}
		leaf = leaf->p;
	}
	while (!s.empty()) {
		out<<s.top();
		s.pop();
	}

};

int HCTree::decode(BitInputStream& in) const{
	//decode the input bit stream, start at root
	//Loop until we reach the leaf of the tree
	HCNode* node = root;
	while (node->c0 || node->c1) {
		int flag = in.get();
		//return after we decoded the last bit
		if (flag == -1)	return -1;//eof
		//Go to the lower level according to the returned val
		if (flag == 1) {
			node = node->c1;
		}
		else {
			node = node->c0;
		}
	}
	return node->symbol;
};

int HCTree::decode(ifstream& in) const{
	//decode the encoded input char stream
	// Works similarly
	HCNode* node = root;
	byte c;
	while (node->c0 || node->c1) {
		in>>c;
		if (c == '0') {
			node = node->c0;
		}
		else {
			node = node->c1;
		}
	}
	return node->symbol;
};

HCTree::~HCTree() {
	// remember to gc
	deleteNode(root);
};

void HCTree:: deleteNode(HCNode* node) {
	//post order traversal to delete all nodes
	if (!node)
		return;
	deleteNode(node->c0);
	deleteNode(node->c1);
	delete node;
};

