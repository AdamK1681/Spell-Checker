/*Name: Adam Kucharzewski
Email: Adam.Kucharzewski94@myhunter.cuny.edu
This file tests the various implementations of hash tables, found in linear_probing.h,
quadratic_probing.h, and double_hashing.h.
*/

#include <fstream>
#include <iostream>
#include <string>


#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"

using namespace std;

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) 
    {
    
    hash_table.MakeEmpty();    
    ifstream f;
    f.open(words_filename);
    if(f.fail()){
        cerr << "Failed to open file" << words_filename << endl; //If the file doesn't open for whatever reason
    }
    string l;
    while(getline(f, l))
    { 
        hash_table.Insert(l); //Fills the hash table
    }
    f.close();//closes the file
    

    //Q1
    cout << "number_of_elements: " << hash_table.getNumElements() << endl;
    cout << "size_of_table: " << hash_table.getTableSize() << endl;
    cout << "load_factor: " << (float)hash_table.getNumElements()/hash_table.getTableSize() << endl;
    cout << "collisions: " << hash_table.getNumCollisions() << endl;
    cout << "avg_collisions: " << (float)hash_table.getNumCollisions()/hash_table.getNumElements() << endl << endl;

    f.open(query_filename);
    if(f.fail()){
        cerr << "Failed to open file" << query_filename << endl;    //If the file doesn't open for whatever reason
    }
    while (getline(f, l)) //while the file can be opened display the list of words found or not
    {
        hash_table.clearCol();//first resets and clears the collisions 
        if(hash_table.Contains(l)){
            cout << l << " Found " << hash_table.getNumCollisions() + 1 << endl; //The number of times the word is found will alwaus be off by 1
        }
        else{ 
            cout << l << " Not_Found " << hash_table.getNumCollisions() + 1 << endl;//The number of times the word is found will alwaus be off by 1
        }
    }
    f.close();
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename,
       			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
	HashTableDouble<string> double_probing_table;
	TestFunctionForHashTable(double_probing_table, words_filename,
	 			 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 && argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
