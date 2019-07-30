/*
 * System.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: huy
 */

#include"System.h"
 /*
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
 */
trie* System::get_root() {
	return root;
}

int System::check_file(string s) {
	for (int i = 0; i < (int)files.size(); ++i)
	{
		//cout << files[i] << endl;
		if (s == files[i]) return i;
	}
	return -1;
}

string System::Find_keyword(ifstream &fin, vector<string> word) {
	//bool check = true;
	for (int i = 0; i < (int)word.size(); i++)
	{
		string key = " " + word[i] + " ";
		string read; //cout << "...";
		while (!fin.eof()) {
			getline(fin, read);
			read = " " + read + " ";
			string str = read;
			for (int i = 0; i < (int)read.size(); i++) {
				if (read[i] >= 'A' && read[i] <= 'Z') read[i] = char(read[i] - 'A' + 'a');
				if ((read[i] >= '!' && read[i] <= '/') || (read[i] >= ':' && read[i] <= '@') || (read[i] >= '[' && read[i] <= '-') || (read[i] >= '{' && read[i] <= '~'))
					read[i] = ' ';
			}
			int pos = read.find(key);
			if (pos != -1) {
				/* if ((int)read.size() < 250) cout << str; else {
					if (pos < 100) pos = 0; else pos = pos - 100;
					for (int w = pos; (w < pos + 200) && (w < (int)str.size()); w++)
						cout << str[w]; */
				return read;
				//}
				//check = false;
				//break;
			}
			//if (!check) break;
		}
		//if (!check) break;
	}
	//cout << "..." << endl;
	//cout << endl;
}

vector<string> System::Print(string filename, vector<string> word) {
	ifstream fin;
	fin.open("data/Search Engine-Data/" + filename);
	string Title; vector<string> ans_tmp;
	getline(fin, Title);
	ans_tmp.push_back(Title);
	string keystr = Find_keyword(fin, word);
	ans_tmp.push_back(keystr);
	fin.close();
	return ans_tmp;
}

void change(string &S, int is_query) {
	if (!is_query) {
		for (int i = 0; i < (int)S.size(); ++i)
			if (S[i] == '$') {
				while (S[0] != '$') S.erase(S.begin());
				while (S.size() && (S.back() >= '0'&&S.back() <= '9') == 0)
					S.pop_back();
				return;
			}
	}
	string tmp = S;
	S = "";
	for (int i = 0; i < (int)tmp.size(); ++i) {
		int ok = 0;
		if (tmp[i] >= 'a'&&tmp[i] <= 'z') ok = 1;
		if (tmp[i] >= 'A'&&tmp[i] <= 'Z') ok = 1;
		if (tmp[i] >= '0'&&tmp[i] <= '9') ok = 1;
		if (tmp[i] == '#' || tmp[i] == '$' || tmp[i] == '-') ok = 1;
		if (is_query) {
			if (tmp[i] == '+' || tmp[i] == '-') ok = 1;
			if (tmp[i] == '.' || tmp[i] == ' ') ok = 1;
		}
		if (!ok) continue;
		if (tmp[i] >= 'A'&&tmp[i] <= 'Z') tmp[i] = char(tmp[i] - 'A' + 'a');
		S = S + tmp[i];
	}
}

void System::load_stop_word() {
	ifstream in("data/stop_words.txt");
	string S;
	while (getline(in, S)) {
		stopwords[S] = 1;
	}
	in.close();
}

void System::inputSearch() {
	//system("cls");
	cout << "Input your search:";
	getline(cin, searchString, '\n');
	change(searchString, 1);
}

string System::getSearch() {
	return searchString;
}

void System::InputFiles() {
	ifstream fin;
	fin.open("data/files.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			string fileName;
			getline(fin, fileName, '\n');
			if (fileName.size() > 4) files.push_back(fileName);
		}
	}
	fin.close();
}
void System::build_trie() {
	//for every file
	//vector<word>
	//root.add_word(word,file)
	int cnt = 0;
	for (auto file_name : files) {
		++cnt;
		if (cnt > 100)
			break;
		vector<string > words;
		words.clear();
		map<string, int > mark;
		mark.clear();
		string name = "data/Search Engine-Data/" + file_name;
		ifstream in(name);
		/*if (!in.is_open()) {
			cout << "error when open file "<<file_name;
			system("pause");
			return;
		}*/
		string S;
		while (in >> S) {
			change(S, 0);
			if (mark[S] || stopwords[S]) continue;
			mark[S] = 1;
			root->add_word(S, file_name);
		}
		cout << cnt << "/" << files.size() << " " << file_name << " done \n";
		in.close();
	}
	cout << "done loading\n";
}

void System::Rank_files(int *check, vector<string> word) {
	vector<string> wordfiles;
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
		int id = check_file(wordfiles[i]);
		if (id != -1 && check[id] != -1) check[id]++;
	}
}

void System::Rank_down(int *check, vector<string> wordfiles)
{
	for (int i = 0; i < (int)wordfiles.size(); i++)
	{
		int id = check_file(wordfiles[i]);
		if (id != -1) check[id] = -1;
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
	else if (type == "intitle:" || type == "filetype:") s.erase(0, type.size() - 1);
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
	int *check = new int[12000]; 
	for (int i = 0; i < 12000; i++) check[i] = 0;

	vector<string> word = CutWord(s, " and ");

	Rank_files(check, word);
	
	vector<string> ans;
	int co = 0;
	for (int i = 0; i < 12000; i++)
	{
		if (check[i] >= (int)word.size()) {
			co++;
			ans.push_back(files[i]);
		}
		if (co == 5) break;
	}

	vector<string> ans_key; vector<string> ans_Title;
	for (int i = 0; i < (int)ans.size(); i++)
	{
		vector<string> tmp = Print(ans[i], word);
		ans_key.push_back(tmp[0]);
		ans_Title.push_back(tmp[1]);
	}
}

void System::process_OR(string s) {

	int *check = new int[12000];
	for (int i = 0; i < 100; i++) check[i] = 0;
	vector<string> word = CutWord(s, " or ");

	Rank_files(check, word);

	vector<string> ans;
	for (int co = 0; co < 5; co++)
	{
		int max = 0, index_max = -1;
		for (int i = 0; i < 12000; i++)
			if (check[i] > max)
			{
				max = check[i];
				index_max = i;
			}
		if (index_max != -1) {
			check[index_max] = -1;
			ans.push_back(files[index_max]);
		}
	}

	vector<string> ans_key; vector<string> ans_Title;
	for (int i = 0; i < (int)ans.size(); i++)
	{
		vector<string> tmp = Print(ans[i], word);
		ans_key.push_back(tmp[0]);
		ans_Title.push_back(tmp[1]);
	}
}

void System::process_minus(string s) {
	int *check = new int[12000];
	for (int i = 0; i < 12000; i++) check[i] = 0;
	//get first and second word from query
	vector<string> word = CutWord(s, " -");
	//get all files thats have i word
	vector<string> wordfiles; vector<string> keyword;
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
			keyword.push_back(word[i]);
			wordfiles = root->get_files_from_word(word[i]);
			// Rank up + all these files
			Rank_up(check, wordfiles);
		}
	}
	
	vector<string> ans;
	for (int co = 0; co < 5; co++)
	{
		int max = 0, index_max = -1;
		for (int i = 0; i < 12000; i++)
			if (check[i] > max)
			{
				max = check[i];
				index_max = i;
			}
		if (index_max != -1) {
			check[index_max] = -1;
			ans.push_back(files[index_max]);
		}
	}

	vector<string> ans_key; vector<string> ans_Title;
	for (int i = 0; i < (int)ans.size(); i++)
	{
		vector<string> tmp = Print(ans[i], word);
		ans_key.push_back(tmp[0]);
		ans_Title.push_back(tmp[1]);
	}
}

void checkTitle(string word, vector<string> titles, int* check) {
	for (int i = 0; i < (int)titles.size(); i++)
	{
		if (titles[i].find(word) != string::npos)
			check[i]++;
	}
}

vector<string> getTitle(vector<string> wordfiles) {
	vector<string> titles;
	for (int i = 0; i < (int)wordfiles.size(); i++)
	{
		ifstream fin;
		fin.open("data/Search Engine-Data/" + wordfiles[i]);
		string title;
		getline(fin, title);
		//fin >> title;
		titles.push_back(title);
		fin.close();
	}
	return titles;
}

void System::process_intitle(string s) {
	cout << endl;
	int check[15000];
	for (int i = 0; i < 1000; i++) check[i] = 0;
	//get vector<word> from query

	vector<string> word = CutWord(s, "intitle:");

	//get all files thats have all word like AND query

	//go through each file to check and rank up
	vector<string> wordfiles;
	vector<string> wordTitle;

	vector<string> fileNamePush;
	vector<string> titlePush;
	vector<string> wordPush;

	for (int i = 0; i < (int)word.size(); i++)
	{
		wordfiles = root->get_files_from_word(word[i]);
		wordTitle = getTitle(wordfiles);
		checkTitle(word[i], wordTitle, check);
	}

	//print 5 max value
	for (int co = 0; co < 5; co++)
	{
		int max = 0, index_max = 0;
		for (int i = 0; i < wordfiles.size(); i++)
			if (check[i] > max)
			{
				max = check[i];
				index_max = i;
			}
		check[index_max] = -1;
		if (max > 0) {
			//print name file
			ifstream fin;
			fin.open("data/Search Engine-Data/" + wordfiles[index_max]);
			fileNamePush.push_back(wordfiles[index_max]);
			string text;
			getline(fin, text);
			//print title
			titlePush.push_back(text);

			//print some text of title's file
			int maxSize = 60;
			getline(fin, text);
			if (text.length() > maxSize)
				text.erase(maxSize, text.length() - maxSize);
			text = text + "...";
			wordPush.push_back(text);
			fin.close();
		}
	}

}

void System::process_plus(string s) {
	int *check = new int[12000];
	for (int i = 0; i < 12000; i++) check[i] = 0;
	vector<string> word = CutWord(s, " +");

	Rank_files(check, word);
	
	vector<string> ans;
	int co = 0;
	for (int i = 0; i < 12000; i++)
	{
		if (check[i] >= (int)word.size()) {
			co++;
			ans.push_back(files[i]);
		}
		if (co == 5) break;
	}

	vector<string> ans_key; vector<string> ans_Title;
	for (int i = 0; i < (int)ans.size(); i++)
	{
		vector<string> tmp = Print(ans[i], word);
		ans_key.push_back(tmp[0]);
		ans_Title.push_back(tmp[1]);
	}
}

void System::process_type(string s) {
	vector<string> fileNamePush;
	vector<string> titlePush;
	vector<string> wordPush;

	//from list of file, return file that same type as query
	vector<string> word = CutWord(s, "filetype:");

	if (word[0] == "txt")
		for (int i = 1; i < 6; i++)	//5 first files
		{
			//print name file
			fileNamePush.push_back(files[i]);
			ifstream fin;
			fin.open("data/Search Engine-Data/" + files[i]);
			string text;

			getline(fin, text);
			titlePush.push_back(text);
			//print title
			cout << text << endl;

			//print some text of title's file
			int maxSize = 60;
			getline(fin, text);
			if (text.length() > maxSize)
				text.erase(maxSize, text.length() - maxSize);
			text = text + "...";
			wordPush.push_back(text);
			fin.close();
		}
	else {
		string text = "There's no " + word[0] + " file!";
		wordPush.push_back(text);
	}
}

void System::process_a_price() {
	string query = searchString;
	string price = "";
	vector<string > words;
	for (int i = 0; i < (int)query.size(); ++i) {
		if (query[i] != '$') continue;
		for (int j = i; j < (int)query.size(); ++j) {
			if (query[j] == ' ') break;
			price += query[j];
		}
		break;
	}
	query = " " + query;
	for (int i = 0; i < (int)query.size(); ++i) {
		if (query[i] == ' ') words.push_back("");
		if (query[i] == '$') {
			words.pop_back();
			++i;
			while (i < (int)query.size() && query[i] >= '0'&&query[i] <= '9')
				i++;
			--i;
		}
		if (query[i] >= 'a'&&query[i] <= 'z')
			words.back() += query[i];
	}
	vector<string > file_name = root->get_files_from_word(price);
	vector<string> res;
	vector<fn> q;
	for (int i = 0; i < (int)file_name.size(); ++i) {
		int val = 0;
		ifstream fin("data/Search Engine-Data/" + file_name[i]);
		string s;
		while (fin >> s) {
			change(s, 0);
			for (auto it : words)
				if (it == s) {
					++val;
					break;
				}
		}
		fin.close();
		q.push_back({ file_name[i],val });
	}
	for (int i = 0; i < (int)q.size(); ++i)
		for (int j = i + 1; j < (int)q.size(); ++j)
			if (q[i].num < q[j].num) swap(q[i], q[j]);
	for (int i = 0; i < min(4, (int)q.size()); ++i)
		res.push_back(q[i].file);
	//res is answer
	for (int i = 0; i < (int)res.size(); ++i)
		cout << res[i] << "\n";
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

void System::pushtoFrontEnd(vector<string> fileName, vector<string> titleName, vector<string> shortWord) {

}
