/*
 * trie.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: huy
 */

#include"trie.h"
using namespace std;

void trie::add_word(string S,string file){
	if (!S.size()){
		files.push_back(file);
		return;
	}
	char beg=S[0]; int id=getid(beg);
	if (id==-1){
		id=had.size();
		had.push_back(beg);
		trie* New=new trie();
		Next.push_back(New);
	}
	trie* New=NULL;
	getNode(id,New);
	S.erase(S.begin());
	New->add_word(S,file);
}

int trie::getid(char s){
	for (int i=0;i<(int)had.size();++i)
	if (had[i]==s) return i;
	return -1;
}

void trie::getNode(int id,trie* &Node){
	Node=Next[id];
}

vector<string > trie::get_all_files(){
	return files;
}

vector<string > trie::get_files_from_word(string S){
	if (!S.size())
		return files;
	char beg=S[0];
	int id=getid(beg);
	if (id==-1) {
		vector<string > tmp;
		tmp.clear();
		return tmp;
	}
	trie* New=NULL;
	getNode(id,New);
	S.erase(S.begin());
	return New->get_files_from_word(S);
}

int trie::check_link(string s) {
	for (int i=0;i<(int)files.size();++i)
		if (s==files[i]) return 1;
	return 0;
}

