/*
Author: Enhao Cui
CSE 100 PA3
A53202267
Bit input stream h
*/
#ifndef BITINPUT_H
#define BITINPUT_H

#include <iostream>
#include <fstream>

typedef unsigned char byte;

using namespace std;

class BitInputStream {
	private:
		ifstream& in; //input file stream
		unsigned int count; //the pointer pointing to the bit in the buffer note that bit set indices 0 represent the least significant bit
		//i.e., 7 6 5 4 3 2 1 0
		bitset<8> buffer;
		void read(); // read to buffer
		unsigned int lastbits; // # of useful bits in the last byte
		unsigned int lastpos; // Where is the last byte in the file
	public:
		int get(); //get a bit, retuurns -1 when EOF or used last valid bit
		BitInputStream(ifstream& input, unsigned int pos, unsigned bits):in(input), count(-1), lastpos(pos), lastbits(bits){};
		~BitInputStream(){};
};

#endif