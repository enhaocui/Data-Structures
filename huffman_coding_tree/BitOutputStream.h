/*
Author: Enhao Cui
CSE 100 PA3
A53202267
Bit output stream h
*/
#ifndef BITOUTPUT_H
#define BITOUTPUT_H

#include <iostream>
#include <fstream>
#include <bitset>

typedef unsigned char byte;

using namespace std;

class BitOutputStream {
	private:
		ofstream out; //output file stream
		unsigned int count; //the index to the bit to be written in the buffer
		bitset<8> buffer; //the buffer
		void flush(); //flush the buffer to the putput file
	public:
		void push(bool bit); //writes a bit to the buffer
		BitOutputStream(string output):count(7){
			out.open(output, ofstream::out | ofstream::app); //Append to the file so that we keep the header
		};
		~BitOutputStream();

};

#endif