/*
 * system.h
 *
 *  Created on: Jul 27, 2019
 *      Author: huy
 */
#pragma once
#ifndef SYSTEM_H_
#define SYSTEM_H_
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include"trie.h"
using namespace std;
class system{
private:
	trie* root;
	map<string,int> stopwords;

public:
	system(){
		root=new trie();
		stopwords.clear();
	}
	trie* get_trie();
	void load_stop_word();
	void build_trie();
	void process_AND();//1
	void process_OR();//2
	void process_minus();//3
	void process_intitle();//4
	void process_plus();//5
	void process_type();//6
	void process_a_price();//7
	void process_hashtag();//8
	void process_exact_match();//9
	void process_unknown_word();//10
	void process_range_number();//11
	void process_synonyms();//12
	void history();

};



#endif /* SYSTEM_H_ */
