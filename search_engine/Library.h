#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <conio.h>
using namespace std;

int Choose_Scene(vector <string> list, int maxSelect, int x, int y, int h, bool NumAtBegin, int xx, int yy);
void Input(string &s);
void PrStr(const char* name, int x, int y, int color);
void OutputFunction(const char* name, int x, int y, bool chosen);
void OutputString(string name, int x, int y, bool chosen);
void ClearFrame(int x, int y, int h, int w);
void CPointer(int x, int y);
void ChangeText(string &s);
void OutText(const char* name, int x, int y, const char* size);
void OutPicture(const char* name, int x, int y);
void ChangeTextColor(int color);
void PaintFrame(int x, int y, int h, int w);
bool InputChar(string &res, int x, int y, bool password, int bound, bool edit); 
int Select(int r, int c, int &Pos);
