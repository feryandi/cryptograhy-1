#ifndef input_H
#define input_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

long getFileSize(FILE *file);
vector<char> readFile(string path);
void saveFile(string path, string text);
string algoOption(vector<char> plaintxt, int encrypt, string key);
string typeOption(vector<char> plaintxt, string key);
void textOption();

#endif