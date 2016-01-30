#ifndef algorithm_H
#define algorithm_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

vector<char> vigenereStdEncrypt(vector<char> &plaintxt, int option, int upper_case, string key);
vector<char> vigenereStdDecrypt(vector<char> &ciphertxt, string key);
vector<char> vigenereExtEncrypt(vector<char> &plaintxt, int option, int upper_case, string key);
vector<char> vigenereExtDecrypt(vector<char> &ciphertxt, string key);
vector<char> playfairKey(vector<char> &plaintxt);
vector<char> playfair(vector<char> &plaintxt, int option, string key, int decrypt);

#endif