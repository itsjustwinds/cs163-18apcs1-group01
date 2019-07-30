/*
 * System.h
 *
 *  Created on: Jul 27, 2019
 *      Author: huy
 */
#pragma once
#ifndef System_H_
#define System_H_
#include<iostream>
#include <sys/types.h>
 //#include <dirent.h>
#include <fstream>
#include<algorithm>
#include<memory>
#include<string>
#include <cerrno>
#include<vector>
#include<map>
#include<fstream>
#include"trie.h"
using namespace std;
void change(string &S, int is_query);
class System {
private:
	string searchString;
	trie* root;
	map<string, int> stopwords;
	vector<string > files;
	vector<vector<string> > synonym;
	map<string,int > ID_synonym;
public:
	System() {
		root = new trie();
		files.clear();
		stopwords.clear();
		synonym.clear();
		ID_synonym.clear();
	}
	trie* get_root();//done
	//void get_files_name();//done
	void InputFiles();
	int check_file(string s);
	string Find_keyword(ifstream &fin, vector<string> word);
	vector<string> Print(string filename, vector<string> word);

	string getSearch();
	void inputSearch();
	void pushtoFrontEnd(vector<string> fileName, vector<string> titleName, vector<string> shortWord);
	vector<string> CutWord(string s, string type);//done
	void Rank_files(int *check, vector<string> word);//done
	void Rank_up(int *check, vector<string> wordfiles);//done
	void Rank_down(int *check, vector<string> wordfiles);//done
	void load_synonym();
	void load_stop_word();//done
	void build_trie();
	void process_AND(string s);//1
	void process_OR(string s);//2
	void process_minus(string s);//3
	void process_intitle(string s);//4
	void process_plus(string s);//5
	void process_type(string s);//6
	void process_a_price();//7
	void process_hashtag();//8
	void process_exact_match();//9
	void process_unknown_word();//10
	void process_range_number();//11
	void process_synonyms();//12
	void history();

};

struct fn {
	string file;
	int num;
};


#endif /* System_H_ */
