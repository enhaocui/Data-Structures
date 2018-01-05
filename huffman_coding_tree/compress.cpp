/*
Author: Enhao Cui
CSE 100 PA3
A53202267
Compression main program
*/
#include <iostream>
#include <fstream>
#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

using namespace std;

void countFreq(vector<int>& freqs, ifstream& infile) {
	//Count the freqs of each word
	byte c;
	while (1) {
		c = infile.get();
		//cout << c;
    	if (infile.eof())
    		break;
    	//cout<<c;
    	freqs[c] ++;
	}
};

void encode(HCTree& codetree, ifstream& infile, ofstream& outfile) {
	//Encode as char sequence in '1' and '0'
	byte c;
	while (1) {
		c = infile.get();
    	//infile >> c;
    	if (infile.eof())
    		break;
    	//cout<<c;
    	codetree.encode(c, outfile);

	}
};

void encodeByte(HCTree& codetree, ifstream& infile, string& outfile) {
	//Encode into bytes
	byte c;
	BitOutputStream out(outfile);
	//cout<<"encoding"<<endl;
	while (1) {
		c = infile.get();
		// Stop at end of file
		if (infile.eof())
    		break;
		//cout<<(int)c;
		codetree.encode(c, out);
	}
	//cout<<"encoded"<<endl;
} 



int main(int argc, char** argv) {
	if (argc < 3) {
		cout<<"Need more arguments." << endl;
		return -1;
	}
	//Input file name
	string inputfile = string(argv[1]);
	//Output file name
	string outputfile = string(argv[2]);
	ifstream infile;
	infile.open(inputfile,ios::binary);
	//Check if it is empty
	infile.seekg(0,ios::end);
    size_t size = infile.tellg();
    //Empty file, generate an empty output file
    if( size == 0) {
    	infile.close();
    	ofstream outfile;
    	//Delete all contents in the file
    	outfile.open(outputfile, ofstream::trunc);
    	outfile.close();
    	cout<<"Empty file!"<<endl;
    	return -1;
    }
    //Back to beginning of file
    infile.seekg(0,ios::beg);
	vector<int> freqs(256, 0);
	countFreq(freqs, infile);
	infile.close();
	//Build the tree
	HCTree codetree;
	codetree.build(freqs);
	ofstream outfile;
	outfile.open(outputfile);
	//File header, each line represent the freq of the corresponding char
	for (int num : freqs) {
		outfile<<num<<endl;
	}
	outfile.close();
	infile.open(inputfile,ios::binary);
	encodeByte(codetree, infile, outputfile);
	infile.close();
	outfile.open("out.txt");
	infile.open(inputfile,ios::binary);
	encode(codetree, infile, outfile);
	infile.close();
	outfile.close();
};

