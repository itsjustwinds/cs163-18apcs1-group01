void System::Find_keyword(ifstream &fin, vector<string> word) {
	bool check = true;
	for (int i = 0; i < (int)word.size(); i++)
	{
		string key = " " + word[i] + " ";
		string read; cout << "...";
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
				if ((int)read.size() < 250) cout << str; else {
					if (pos < 100) pos = 0; else pos = pos - 100;
					for (int w = pos; (w < pos + 200) && (w < (int)str.size()); w++)
						cout << str[w];
				}
				check = false;
				break;
			}
			if (!check) break;
		}
		if (!check) break;
	}
	cout << "..." << endl;
}
