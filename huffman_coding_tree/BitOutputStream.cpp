/*
Author: Enhao Cui
CSE 100 PA3
A53202267
Bit output stream cpp
*/
#include "BitOutputStream.h"

void BitOutputStream::push(bool bit) {
	//write one bit into the buffer, write from the most significant bit
	buffer.set(count, bit);
	count --;
	if (count == -1) {
		// Buffer is full, write buffer to the output
		flush();
		//reset
		count = 7;
		buffer.reset();
	}
};

void BitOutputStream::flush() {
	//flush to the output
	unsigned long i = buffer.to_ulong(); 
	unsigned char c = static_cast<unsigned char>(i);
	out<<c;
	//cout<<"flushing "<<(int)c<<endl;
};

BitOutputStream::~BitOutputStream() {
	//destructor, remember to write to the output the last byte
	int lastbits = 7 - count; //The number of useful bits in the last byte
	flush();
	//Save the number of last bits at the end
	out<<lastbits;
	out.close();
};