/*
Author: Enhao Cui
CSE 100 PA2
A53202267
The program for benchmarking different hash functions.
*/
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

/* djb2 
http://www.cse.yorku.ca/~oz/hash.html
This algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. 
Another version of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; 
The magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.
*/

int djb2(const char *str, int table_size) {

	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return (int)hash % table_size;
};

/*
sdbm
http://www.cse.yorku.ca/~oz/hash.html
This algorithm was created for sdbm (a public-domain reimplementation of ndbm) database library. 
It was found to do well in scrambling bits, causing better distribution of the keys and fewer splits. 
It also happens to be a good general hashing function with good distribution. 
The actual function is hash(i) = hash(i - 1) * 65599 + str[i]; 
The magic constant 65599 was picked out of thin air while experimenting with different constants, and turns out to be a prime. 
This is one of the algorithms used in berkeley db (see sleepycat) and elsewhere.
*/

int sdbm(const char *str, int table_size) {

	unsigned long hash = 0;
	int c;

	while (c = *str++)
		hash = c + (hash << 6) + (hash << 16) - hash;
	return (int)hash % table_size;
};

void stripFrequency(string& line) { // Get rid of the frequencies at the beginning of each line
    // Count the number of characters past the first space
    int count = 0;
    string::iterator last = line.end();
    for (string::iterator it = line.begin(); it != last; ++it) {
        count++;
        if (*it == ' ') {
            break;
        }
    }
    line.erase(0, count);
};

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout<<"Need more input arguments"<<endl;
		return -1;
	}
	string dictfile = string(argv[1]);
	int num_words = stoi(string(argv[2]));
	//table size = words num * 2
	int table_size = num_words << 1;
	int *count_djb2 = new int[table_size]{0};
	int *count_sdbm = new int[table_size]{0};
	int *hits_djb2 = new int[table_size]{table_size};
	int *hits_sdbm = new int[table_size]{table_size};
	int djb2_max = 0;
	int sdbm_max = 0;
	ifstream infile(dictfile);
	for (int i = 0; i < num_words; ++i) {
		string line = "";
		getline(infile, line);
		stripFrequency(line);
		int hash1 = djb2(line.c_str(), table_size);
		int hash2 = sdbm(line.c_str(), table_size);
		// Update the number of hits each hash value received.
		djb2_max = max(djb2_max, ++count_djb2[hash1]);
		sdbm_max = max(sdbm_max, ++count_sdbm[hash2]);
		// Update the number of strings each number of hits has.
		hits_djb2[count_djb2[hash1] - 1] --;
		hits_djb2[count_djb2[hash1]] ++;
		hits_sdbm[count_sdbm[hash2] - 1] --;
		hits_sdbm[count_sdbm[hash2]] ++;
	}
	cout << "Printing the statistics for djb2 with hash table size " << table_size << "." << endl;
	for (int i = 0; i < table_size; ++i) {
		if (hits_djb2[i] > 0)
			cout << i << ' ' << hits_djb2[i] << endl;
	}
	int total = 0; //The number of words with no less than the current number of hits
	int totalhits = 0; // Total number of hits
	for (int i = table_size - 1; i >= 0; i --) {
		if (hits_djb2[i] > 0) {
			total += hits_djb2[i];
			totalhits += i * total;

		}
	}
	cout<< "The average number of steps for a successful search for djb2 would be " << totalhits*1.0/num_words << "." <<endl;
	cout<< "The worst case steps that would be needed to find a word is " << djb2_max << "." << endl;
	cout << "Printing the statistics for sdbm with hash table size " << table_size << "." << endl;
	for (int i = 0; i < table_size; ++i) {
		if (hits_sdbm[i] > 0)
			cout << i << ' ' << hits_sdbm[i] << endl;
	}
	total = 0; //The number of words with no less than the current number of hits
	totalhits = 0; // Total number of hits
	for (int i = table_size - 1; i >= 0; i --) {
		if (hits_sdbm[i] > 0) {
			total += hits_sdbm[i];
			totalhits += i * total;

		}
	}
	cout<< "The average number of steps for a successful search for sdbm would be " << totalhits*1.0/num_words << "." <<endl;
	cout<< "The worst case steps that would be needed to find a word is " << sdbm_max << "." << endl;

	delete[] count_djb2;
	delete[] count_sdbm;
	delete[] hits_sdbm;
	delete[] hits_djb2;
	cout<<djb2("I have a busy day", 2000);
	cout<<sdbm("I have a busy day", 2000);

	return 0;
};

