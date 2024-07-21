/*
Name: Adam Kucharzewski
Email: Adam.Kucharzewski94@myhunter.cuny.edu
 spell_check.cc: A simple spell checker.
 This file contains the implementation of a spell checker utilizing the double_hashing method. 
 The spell checker checks words unregonized by the dictionary (stored in a hash table), and attempts to correct them by adding/removing a letter,
 or swapping 2 letters.
*/

#include <fstream>
#include <iostream>
#include <string>


#include "double_hashing.h"
#include "quadratic_probing.h"
#include "linear_probing.h"

using namespace std;


// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  ifstream f; 
  f.open(dictionary_file); 
  if(f.fail()){ 
    cerr << "Failed to open file" << dictionary_file << endl; 
  }
  string l;
  while(getline(f, l))
  { 
    dictionary_hash.Insert(l); 
  }
  f.close(); //closing file 
  return dictionary_hash;
}


// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary,
		  const string &document_file) 
{
ifstream f;
  f.open(document_file);
  if(f.fail()){ 
    cerr << "Failed to open file" << document_file << endl; 
  }
  string l;

  while(f >> l)
  {
    if(!isalnum(l[l.length()-1])){
      l = l.substr(0,l.length()-1); //Checks and accounts for punctuation marks
    }
    transform(l.begin(), l.end(), l.begin(), ::tolower);
    
    if (dictionary.Contains(l))
    { 
      cout << l << " is CORRECT" << endl; 
    }
    else 
    {
  
      cout << l << " is INCORRECT" << endl; 
      string alphabet = "abcdefghijklmnopqrstuvwxyz"; 
      
      //Adding one character in any possible position
      //Case A
      for (int i = 0; i < l.length(); ++i)
      {
        for(char a : alphabet) 
        {
          string modifiedWrd = l.substr(0, i) + a + l.substr(i);
          if (dictionary.Contains(modifiedWrd)) 
          {
            cout << "** " << l << " -> " << modifiedWrd << " ** case A" << endl; 
          }
        }
      }
      
      //Adding one character in the last position
      //Case A
      for(char a : alphabet) 
      {
        string modifiedWrd = l.substr(0, l.length()) + a;
        if (dictionary.Contains(modifiedWrd))
        {
          cout << "** " << l << " -> " << modifiedWrd << " ** case A" << endl; //case A output 
        }
      }

      //Removing one character from the word
      //Case B
      for (int i = 0; i < l.length(); ++i)
      {
        string modifiedWrd = l;
        modifiedWrd = modifiedWrd.erase(i, 1); //from the ith to 1st index position
        if (dictionary.Contains(modifiedWrd))
        {
          cout << "** " << l << " -> " << modifiedWrd << " ** case B" << endl;//case B output 
        }
      }
      
      //Swapping adjacent characters in the word
      //Case C
      for (int i = 0; i < l.length() - 1; ++i)
      {
        //swapping the vlaues 
        string modifiedWrd = l; 
        char a = modifiedWrd[i];
        modifiedWrd[i] = modifiedWrd[i + 1];
        modifiedWrd[i + 1] = a;
        if (dictionary.Contains(modifiedWrd)) 
        {
          cout << "** " << l << " -> " << modifiedWrd << " ** case C" << endl; //case C output 
        }
      }
    }
  }
  f.close();
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
