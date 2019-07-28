/*
 * system.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: huy
 */

#include"system.h"

trie* system::get_trie() {
	return root;
}

void system::load_stop_word() {

}

void system::build_trie() {
	//for every file
	//vector<word>
	//root.add_word(word,file)
}

void system::Rank_files(int *check, vector<string> word) {
	vector<string> wordfiles; int max = 0;
	for (int i = 0; i < word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
		Rank_up(check, wordfiles);
	}
}

void system::Rank_up(int *check, vector<string> wordfiles)
{
	for (int i = 0; i < wordfiles.size(); i++)
	{
		int id = root->check_link(wordfiles[i]);
		if (id != -1) check[id]++;
	}
}

void system::Rank_down(int *check, vector<string> wordfiles)
{
	for (int i = 0; i < wordfiles.size(); i++)
	{
		int id = root->check_link(wordfiles[i]);
		if (id != -1) check[id]--;
	}
}

vector<string> system::CutWord(string s, string type) {
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
	int start = 0; int co = -1;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == ' ')
		{
			if (start != i)
				word.push_back(s.substr(start, i - start));
			start = i + 1;
		}
	if (start != s.size()) word.push_back(s.substr(start, s.size() - start));
	return word;
}

void system::process_AND(string s) {
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

void system::process_OR(string s) {

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

void system::process_minus(string s) {
	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;
	//get first and second word from query
	vector<string> word = CutWord(s, " -");
	//get all files thats have i word
	vector<string> wordfiles;
	for (int i = 0; i < word.size(); i++)
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
	for (int i = 0; i < titles.size(); i++)
	{
		if (titles[i].find(word) == string::npos)
			check[i]++;
	}
}
vector<string> getTitle(vector<string> wordfiles) {
	vector<string> titles;
	for (int i = 0; i < wordfiles.size(); i++)
	{
		ifstream fin;
		fin.open(wordfiles[i] + ".txt");
		string title;
		fin >> title;
		titles.push_back(title);
	}
	return titles;
}
void system::process_intitle(string s) {
	int check[15000]; for (int i = 0; i < 15000; i++) check[i] = 0;
	//get vector<word> from query
	vector<string> word = CutWord(s, "intitle:");

	//get all files thats have all word like AND query

	//go through each file to check and rank up
	vector<string> wordfiles;
	vector<string> wordTitle;

	for (int i = 0; i < word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
		wordTitle = getTitle(wordfiles);
		checkTitle(word[i], wordTitle, check);
	}

	//print 5 max value
}

void system::process_plus(string s) {
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

void system::process_type(string s) {
	//from list of file, return file that same type as query
	vector<string> word = CutWord(s, "filetype:");

	vector<string> wordfiles;
	for (int i = 0; i < word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
	}
}

void system::process_a_price() {

}
void system::process_hashtag() {

}
void system::process_exact_match() {

}
void system::process_unknown_word() {

}
void system::process_range_number() {

}
void system::process_synonyms() {

}
void system::history() {

}
