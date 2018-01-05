/*
Author: Enhao Cui
CSE 100 PA3
A53202267
Uncompress cpp
*/
#include <iostream>
#include <fstream>
#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

using namespace std;

void countFreq(vector<int>& freqs, ifstream& infile) {
	//count the freqs from the header
	for (int i = 0; i < 256; ++i) {
		string s;
		getline(infile, s);
		freqs[i] = stoi(s);
	}
};

void decode(HCTree& codetree, ifstream& infile, ofstream& outfile) {
	//decode the char input
	while (true) {
		unsigned char c = codetree.decode(infile);
		outfile<<c;
		if (infile.eof())
			break;
	}
};

void decodeByte(HCTree&codetree, ifstream& infile, ofstream& outfile, int lastpos, int lastbits) {
	//decode the binary input
	BitInputStream bitin(infile, lastpos, lastbits);
	while (true) {
		int c = codetree.decode(bitin);
		if (c == -1)
			break;
		outfile<<(unsigned char)c;
	}
}

int main(int argc, char** argv) {
	if (argc < 3) {
		cout<<"Need more arguments." << endl;
		return -1;
	}
	string inputfile = string(argv[1]);
	string outputfile = string(argv[2]);
	ifstream infile;
	//Check if file is empty
	infile.open(inputfile);
	infile.seekg(0,ios::end);
    size_t size = infile.tellg();
    if( size == 0) {
    	//create an empty file
    	infile.close();
    	cout<<"Empty file!"<<endl;
    	ofstream outfile;
    	outfile.open(outputfile, ofstream::trunc);
    	outfile.close();
    	return -1;
    }
    // Get to the last char of the input
    infile.seekg(size - 1, ios::beg);
    unsigned char lastbits = infile.get();
    //The last char means the valid bits of the last byte
	vector<int> freqs(256, 0);
	infile.seekg(0, ios::beg);
	countFreq(freqs, infile);
	HCTree codetree;
	codetree.build(freqs);
	ofstream outfile;
	outfile.open(outputfile);
	//size - 1 means the position of the last byte
	decodeByte(codetree, infile, outfile, size - 1, lastbits - '0');
	infile.close();
	outfile.close();
};