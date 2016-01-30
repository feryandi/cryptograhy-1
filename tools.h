#ifndef tools_H
#define tools_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>
using namespace std;

int mod(int x, int m);
string vectorToString(vector<char> text);
void eraseSpace(vector<char> *text);
void addSpace(vector<char> *text, int n);
void eraseExceptAlphabet(vector<char> *text);
int XFromInt(int i, int l);
int YFromInt(int i, int l);
void toUpperCase(vector<char> *text);
void stringToUpper(string &s);

#endif