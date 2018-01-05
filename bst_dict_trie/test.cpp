#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
  
  std::vector<string> v;
  
  for (int i = 0; i < 26; i ++) {
    std::string s = std::string(1, (char)('a' + i));
    for (int j = 0; j < 26; j ++) {
      v.push_back(s + std::string(1, (char)('a' + j)));
    }
  }
  
  //v.push_back("ha");
  //v.push_back("sr");
  //v.push_back("au");
  
  int freq = 1;
  vector<string>::iterator wi;
  vector<string>::iterator we;
  wi = v.begin();
  we = v.end();
  for(; wi != we; ++wi)
    {
      cout << "Inserting: \"" << *wi << "\"... ";
      tt = dt.insert(*wi, freq++);
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

    /*
    while(true) {
      std::string input;
      int times;
      std::cin>>input;
      std::cin>>times;
      std::vector<string> output = dt.predictCompletions(input, times);
      for (auto s : output) {
        std::cout<<s<<std::endl;
      }
      std::cout<<"Over"<<endl;
    }
    */
    


  cout << endl;
  return 0;
}
