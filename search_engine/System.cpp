/*
 * System.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: huy
 */

#include"System.h"

vector<string> GetDirectoryFiles(const string& dir) {
  vector<string> files;
  shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
  struct dirent *dirent_ptr;
  if (!directory_ptr) {
	  return files;
  }

  while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
    files.push_back(string(dirent_ptr->d_name));
  }
  return files;
}



void System::get_files_name(){
	  const auto& directory_path = string("data/Search Engine-Data");
	  const auto& f = GetDirectoryFiles(directory_path);
	  for (const auto& file : f)
	  if((int)file.size()>2){
	    files.push_back(file);
	  }
	  ofstream out("data/files.txt");
	  for (int i=0;i<(int)files.size();++i){
		  out<<files[i]<<"\n";
		  //cout<<files[i]<<"\n";
		  }
	  out.close();
}

trie* System::get_root() {
	return root;
}

void change(string &S){
	string tmp=S;
	S="";
	for (int i=0;i<(int)tmp.size();++i){
		int ok=0;
		if (tmp[i]>='a'&&tmp[i]<='z') ok=1;
		if (tmp[i]>='A'&&tmp[i]<='Z') ok=1;
		if (tmp[i]=='#'||tmp[i]=='$') ok=1;
		if (!ok) continue;
		S=S+tmp[i];
	}
}

void System::load_stop_word() {
	ifstream in("data/stop_words.txt");
	string S;
	while(getline(in,S)){
		stopwords[S]=1;
	}
	in.close();
}

void System::build_trie() {
	//for every file
	//vector<word>
	//root.add_word(word,file)
	for (auto file_name: files){
		vector<string > words;
		words.clear();
		map<string,int > mark;
		mark.clear();
		string name="data/Search Engine-Data/"+file_name;
		ifstream in(name);
		if (!in.is_open()){
			cout<<"error when open file";
			return;
		}
		string S;
		while(in>>S){
			change(S);
			if (mark[S]||stopwords[S]) continue;
			mark[S]=1;
			root->add_word(S,file_name);
			cout<<S<<" "<<file_name<<"\n";
		}
		in.close();
	}
	cout<<"done loading";
}

void System::Rank_files(int *check, vector<string> word) {
	vector<string> wordfiles;
	//int max = 0;
	for (int i = 0; i < (int)word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
		Rank_up(check, wordfiles);
	}
}

void System::Rank_up(int *check, vector<string> wordfiles)
{
	for (int i = 0; i < (int)wordfiles.size(); i++)
	{
		int id = root->check_link(wordfiles[i]);
		if (id != -1) check[id]++;
	}
}

void System::Rank_down(int *check, vector<string> wordfiles)
{
	for (int i = 0; i < (int)wordfiles.size(); i++)
	{
		int id = root->check_link(wordfiles[i]);
		if (id != -1) check[id]--;
	}
}

vector<string> System::CutWord(string s, string type) {
	vector<string> word;
	//Find all TYPE
	if (type != "intitle:" && type != "filetype:" && type != " -") {
		int pos;
		do
		{
			pos = s.find(type);
			if (pos != -1) s.erase(pos + 1, type.size() - 1);
		} while (pos != -1);
	}
	else if (type == "intitle:" || type == "filetype:") s.erase(0, type.size());
	//Cut all words
	int start = 0;
	//int co = -1;
	for (int i = 0; i < (int)s.size(); i++)
		if (s[i] == ' ')
		{
			if (start != i)
				word.push_back(s.substr(start, i - start));
			start = i + 1;
		}
	if (start != (int)s.size()) word.push_back(s.substr(start, s.size() - start));
	return word;
}

void System::process_AND(string s) {
	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;

	vector<string> word = CutWord(s, " AND ");

	Rank_files(check, word);

	/*
	int co = 0;
	for (int i = 0; i < 15000; i++)
	{
		if (check[i] == word.size()) {
			co++;
			print(root->files[i]);
			}
		if (co == 5) break;
	}
		*/
}

void System::process_OR(string s) {

	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;
	vector<string> word = CutWord(s, " OR ");

	Rank_files(check, word);

	/*
	for (int co = 0; co < 5; co++)
	{
		int max = 0, index_max;
		for (int i = 0; i < 15000; i++)
			if (check[i] > max)
			{
				max = check[i];
				index_max = i;
			}
		check[index_max] = -1;
		print(files[index_max]);
	}
		*/
}

void System::process_minus(string s) {
	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;
	//get first and second word from query
	vector<string> word = CutWord(s, " -");
	//get all files thats have i word
	vector<string> wordfiles;
	for (int i = 0; i < (int)word.size(); i++)
	{
		if (word[i][0] == '-')
		{
			word[i] = word[i].erase(0, 1);
			wordfiles = root->get_files_from_word(word[i]);
			// Rank down - all these files
			Rank_down(check, wordfiles);
		}
		else
		{
			wordfiles = root->get_files_from_word(word[i]);
			// Rank up + all these files
			Rank_up(check, wordfiles);
		}
	}
	/*
	for (int co = 0; co < 5; co++)
	{
		int max = 0, index_max;
		for (int i = 0; i < 15000; i++)
			if (check[i] > max)
			{
				max = check[i];
				index_max = i;
			}
		check[index_max] = -1;
		print(files[index_max]);
	}
		*/
}

void checkTitle(string word, vector<string> titles, int* check) {
	for (int i = 0; i < (int)titles.size(); i++)
	{
		if (titles[i].find(word) == string::npos)
			check[i]++;
	}
}

vector<string> getTitle(vector<string> wordfiles) {
	vector<string> titles;
	for (int i = 0; i < (int)wordfiles.size(); i++)
	{
		ifstream fin;
		fin.open(wordfiles[i] + ".txt");
		string title;
		fin >> title;
		titles.push_back(title);
	}
	return titles;
}

void System::process_intitle(string s) {
	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;
	//get vector<word> from query
	vector<string> word = CutWord(s, "intitle:");

	//get all files thats have all word like AND query

	//go through each file to check and rank up
	vector<string> wordfiles;
	vector<string> wordTitle;

	for (int i = 0; i < (int)word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
		wordTitle = getTitle(wordfiles);
		checkTitle(word[i], wordTitle, check);
	}

	//print 5 max value
}

void System::process_plus(string s) {
	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;
	vector<string> word = CutWord(s, " +");

	Rank_files(check, word);

	/*
	int co = 0;
	for (int i = 0; i < 15000; i++)
	{
		if (check[i] == word.size()) {
			co++;
			print(root->files[i]);
			}
		if (co == 5) break;
	}
		*/
}

void System::process_type(string s) {
	//from list of file, return file that same type as query
	vector<string> word = CutWord(s, "filetype:");

	vector<string> wordfiles;
	for (int i = 0; i < (int)word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
	}
}

void System::process_a_price() {

}
void System::process_hashtag() {

}
void System::process_exact_match() {

}
void System::process_unknown_word() {

}
void System::process_range_number() {

}
void System::process_synonyms() {

}
void System::history() {

}
