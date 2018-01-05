/*
Author: Enhao Cui
CSE 100 PA3
A53202267
Bit input stream cpp
*/
#include "BitInputStream.h"

int BitInputStream::get() {
	//If all bits in the buffer are read/buffer is empty, read a char from the input
	if (count == -1) {
		read();
		if (count == -1) //Reach EOF, then return -1
			return -1;
	}
	if (in.tellg() == lastpos && count == 7 - lastbits)	return -1; //Reach EOF, and all the last bits are read, return -1
	return buffer[count--]; //decrease the counter
}

void BitInputStream::read() {
	
	unsigned char c;
	c = in.get();
	if (in.eof())
		return;
	//cout<<"BitInputStream read  "<<c<<endl;
	//cout<<"bit read"<<endl;
	//cout<<(unsigned int)c<<endl;
	buffer = bitset<8>(c);//Set the buffer
	count = 7;//Reset count
}

