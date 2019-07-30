#include <windows.h>
#include "Library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <conio.h>
using namespace std;
//                    A,B,C,D,E,F,G,F,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
const int num[26] = { 7,7,7,7,7,7,7,7,3,7,7,7,9,8,7,7,7,7,7,7,7,7,7,7,7,7 };

void Input(string &s)
{
	system("CLS");
	s = "";
	CPointer(75, 15);
	ChangeTextColor(15);
	OutText("SUPER", 14, 3, "L");
	ChangeTextColor(11);
	OutText("SEARCH", 69, 3, "L");
	ChangeTextColor(13);
	OutText("ENGINE", 55, 11, "L");
	ChangeTextColor(14);
	CPointer(74, 19);
	PaintFrame(10, 21, 35, 110);
	PaintFrame(20, 22, 1, 98);
	PaintFrame(12, 25, 29, 106);
	CPointer(14, 23);
	cout << "Key: ";
	CPointer(57, 26);
	InputChar(s, 22, 23, false, 30, true);

	ChangeTextColor(15);
	return;
}

void GraphicLogin()
{
	CPointer(75, 15);
	ChangeTextColor(15);
	OutText("STUDENT", 14, 3, "L");
	ChangeTextColor(11);
	OutText("MANAGEMENT", 69, 3, "L");
	ChangeTextColor(13);
	OutText("SYSTEM", 55, 11, "L");
	ChangeTextColor(14);
	CPointer(74, 19);
	cout << "Login";
	PaintFrame(55, 21, 6, 40);
	PaintFrame(67, 22, 1, 27);
	PaintFrame(67, 25, 1, 27);
	CPointer(57, 23);
	cout << "User ID: ";
	CPointer(57, 26);
	cout << "Password: ";
	PrStr("Press enter to log in", 65, 33, 12);
	PrStr("  Press ESC to exit", 65, 35, 12);
	ChangeTextColor(15);
	return;
}
void PrStr(const char* name, int x, int y, int color) //prt str
{
	ChangeTextColor(color);
	CPointer(x, y);
	cout << name;
	return;
}
void OutputFunction(const char* name, int x, int y, bool chosen)
{
	if (!chosen)
		ChangeTextColor(15);
	else ChangeTextColor(13);
	OutPicture(name, x, y);
	return;
}

void OutputString(string name, int x, int y, bool chosen)
{
	if (!chosen)
		ChangeTextColor(15);
	else ChangeTextColor(13);
	CPointer(x, y);
	cout << name;
	return;
}

void ClearFrame(int x, int y, int h, int w)
{
	for (int i = y; i <= y + h - 1; i++)
	{
		CPointer(x, i);
		for (int j = x; j < x + w - 1; j++) cout << " ";
	}
	return;
}

void CPointer(int x, int y) //Change Pointer
{
	COORD pt = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pt);
	return;
}


void ChangeText(string &s)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] == 'H') s[i] = char(219);
		else if (s[i] == 'W') s[i] = char(220);
		else if (s[i] == 'F') s[i] = char(223);
		else if (s[i] == '|') s[i] = char(248);
		else if (s[i] == '+') s[i] = char(176);
		else if (s[i] == 'X') s[i] = char(254);
	return;
}

void OutText(const char* name, int x, int y, const char* size)
{
	if (name == " ") return;

	int temp = 0;
	if (size[0] == 'M')
		temp = 2;

	for (int i = 0; i < strlen(name); i++)
	{
		string link = "";
		link += name[i];
		link += size[0];
		link += ".txt";
		OutPicture(link.c_str(), x, y);
		x += num[name[i] - 'A'] - temp;
	}
	return;
}
void OutPicture(const char* name, int x, int y)
{
	ifstream myfile(name);
	int cnt = 0;
	string s[20];
	while (getline(myfile, s[cnt]))
		++cnt;
	for (int i = 0; i < cnt; i++)
	{
		ChangeText(s[i]);
		CPointer(x, y + i);
		cout << s[i];
	}
	myfile.close();
	return;
}
void ChangeTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}
void PaintFrame(int x, int y, int h, int w) // coordinates x,y ------ height --- width
{
	for (int i = 0; i <= h + 1; i++)
		for (int j = 0; j <= w + 1; j++)
		{
			CPointer(x + j, y + i);
			if ((i == 0) && (j == 0))
			{
				cout << char(218);
				continue;
			}
			if ((i == 0) && (j == w + 1))
			{
				cout << char(191);
				continue;
			}
			if ((i == h + 1) && (j == 0))
			{
				cout << char(192);
				continue;
			}
			if ((i == h + 1) && (j == w + 1))
			{
				cout << char(217);
				continue;
			}
			if ((i == 0) || (i == h + 1)) cout << char(196);
			if ((j == 0) || (j == w + 1)) cout << char(179);
		}
	return;
}
bool InputChar(string &res, int x, int y, bool password, int bound, bool edit) //user, password
{
	string temp_res = res;
	res = "";
	char ch, temp;
	int cnt = 0;
	while (true)
	{
		CPointer(x + cnt, y);
		ch = _getch();
		temp = _getch();

		if (((ch - 'A' >= 0) && (ch - 'A' <= 25)) || ((ch - 'a' >= 0) && (ch - 'a' <= 25)) || ((ch - '0' >= 0) && (ch - '0' <= 9)) || (ch == ' ') || (ch == '(') || (ch == ')') || (ch == '/') || (ch == '.'))
		{
			if (cnt <= bound)
			{
				if (!password) cout << ch;
				else cout << "*";
				res += ch;
				++cnt;
			}
		}
		if ((cnt > 0) && (ch == 13) && (temp == 0))
			return true;
		if (cnt == 0 && ch == 13 && temp == 0 && edit == true) {
			res = temp_res;
			cout << res;
			return true;
		}
		if ((cnt > 0) && (ch == 8) && (temp == 0))
		{
			--cnt;
			CPointer(x + cnt, y);
			res.pop_back();
			cout << " ";
		}
		if ((ch == 27) && (temp == 0)) return false;
	}
	return true;
}
int Select(int r, int c, int &Pos)
{
	char ch, temp;
	int row = Pos / c, col = Pos % c;
	ch = _getch();
	temp = _getch();
	if ((ch == 27) && (temp == 0)) return 2;
	if ((ch == -32) && (temp == 72) && (row > 0))
	{
		Pos -= c;
		//up button
	}
	if ((ch == -32) && (temp == 80) && (row < r - 1))
	{
		Pos += c;
		//down button
	}
	if ((ch == -32) && (temp == 75) && (col > 0))
	{
		Pos--;
		//left button
	}
	if ((ch == -32) && (temp == 77) && (col < c - 1))
	{
		Pos++;
		//right button
	}
	if ((ch == 13) && (temp == 0))
		return 1;
	return 0;
}
int Choose_Scene(vector <string> list, int maxSelect, int x, int y, int h, bool NumAtBegin, int xx, int yy) //list, max_selections, coordinates, height, Use x. before selections or not
{
	int sz = list.size(), Pos = 0, select;
	int begin = 0, end = min(sz, maxSelect);
	do
	{
		if (Pos < begin)
		{
			begin--;
			end--;
		}
		if (Pos >= end)
		{
			begin++;
			end++;
		}
		string s;
		for (int i = begin; i < end; i++)
		{
			s = "";
			if (NumAtBegin)
			{
				s += to_string(i + 1);
				s += ". ";
			}
			s += list[i];
			ClearFrame(x, y + (i - begin) * h, xx, yy);
			OutputString(s, x, y + (i - begin) * h, (Pos == i));
		}
		select = Select(sz, 1, Pos);
	} while (!select);
	if (select == 2) return -1;
	else return Pos;


}
