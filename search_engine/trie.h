/*
 * trie.h
 *
 *  Created on: Jul 26, 2019
 *      Author: huy
 */
#pragma once
#ifndef TRIE_H_
#define TRIE_H_
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class trie{
private:
	vector<char > had;
	vector<trie* > Next;
	vector<string > files;
public:
	trie(){
		had.clear();
		Next.clear();
		files.clear();
	}

	void add_word(string S,string file);
	int getid(char s);
	void getNode(int id,trie* &Node);
	vector<string > get_all_files();
	vector<string > get_files_from_word(string S);
	int check_link(string s);	
};




#endif /* TRIE_H_ */
