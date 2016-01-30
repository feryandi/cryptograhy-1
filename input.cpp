#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>

#include "algorithm.h"
#include "tools.h"
using namespace std;

typedef unsigned char BYTE;

long getFileSize(FILE *file) {
	long lCurPos, lEndPos;
	lCurPos = ftell(file);
	fseek(file, 0, 2);
	lEndPos = ftell(file);
	fseek(file, lCurPos, 0);
	return lEndPos;
}

vector<char> readFile(string path) {
	BYTE *fileBuf;
	FILE *file = NULL;

	vector<char> plaintxt;

	if ((file = fopen(path.c_str(), "rb")) == NULL)
		cout << "Could not open specified file" << endl;
	
	long fileSize = getFileSize(file);

	fileBuf = new BYTE[fileSize];
	fread(fileBuf, fileSize, 1, file);

	for (long i = 0; i < fileSize; i++) {
		plaintxt.push_back(fileBuf[i]);
	}

	delete[]fileBuf;
    fclose(file);   
	return plaintxt;
}

void saveFile(string path, string text) {
	FILE * pFile;
	pFile = fopen (path.c_str(), "wb");
	fwrite (text.c_str() , sizeof(BYTE), (text).length(), pFile);
	fclose (pFile);
}

string algoOption(vector<char> plaintxt, int encrypt, string key) {
	int option = -1;
	int format = -1;
	cout << endl;
	cout << "-------------------" << endl;
	cout << "* Choose Cipher   *" << endl;
	cout << "-------------------" << endl;
	cout << "1. Vigenere Standard" << endl;
	cout << "2. Vigenere Extended" << endl;
	cout << "3. Playfair" << endl;
	cin >> option;

	switch (option) {
		case 1:
			if (encrypt) {
				cout << endl;
				cout << "-------------------" << endl;
				cout << "* Choose Output   *" << endl;
				cout << "-------------------" << endl;
				cout << "1. Original" << endl;
				cout << "2. Remove Space" << endl;
				cout << "3. Space every 5 char" << endl;
				cin >> format;

				return vectorToString(vigenereStdEncrypt(plaintxt, format-1, 1, key));
			} else {
				return vectorToString(vigenereStdDecrypt(plaintxt, key));
			}
			break;
		case 2:
			if (encrypt) {
				return vectorToString(vigenereExtEncrypt(plaintxt, 0, 0, key));
			} else {
				return vectorToString(vigenereExtDecrypt(plaintxt, key));
			}
			break;
		case 3:
			if (encrypt) {
				cout << endl;
				cout << "-------------------" << endl;
				cout << "* Choose Output   *" << endl;
				cout << "-------------------" << endl;
				cout << "1. Original" << endl;
				cout << "2. Remove Space" << endl;
				cout << "3. Space every 5 char" << endl;
				cin >> format;

				return vectorToString(playfair(plaintxt, format-1, key, 0));
			} else { 
				return vectorToString(playfair(plaintxt, 0, key, 1));
			}
			break;
	}	
}

string typeOption(vector<char> plaintxt, string key) {
	int option = -1;
	cout << endl;
	cout << "-------------------" << endl;
	cout << "* Choose Type     *" << endl;
	cout << "-------------------" << endl;
	cout << "1. Encrypt" << endl;
	cout << "2. Decrypt" << endl;
	cin >> option;

	switch (option) {
		case 1:
			return algoOption(plaintxt, 1, key);
			break;
		case 2:
			return algoOption(plaintxt, 0, key);
			break;
	}
}

void textOption() {
	int option = -1;
	string text;
	string out;
	string path;
	string key;

	cout << "-------------------" << endl;
	cout << "* Input Text      *" << endl;
	cout << "-------------------" << endl;
	cout << "1. From File" << endl;
	cout << "2. Write" << endl;
	cin >> option;

	switch (option) {
		case 1:
			cin.ignore();

			cout << endl;
			cout << "-------------------" << endl;
			cout << "* Input           *" << endl;
			cout << "-------------------" << endl;

			cout << "File path:" << endl;
			getline(cin, text);
			cout << "Key: " << endl;
			getline(cin, key);

			out = typeOption(readFile(text), key);
			//out = vectorToString(readFile(text));

			cout << "Input: " << text << endl;
			cout << "Key: " << key << endl;
			//cout << "Output: " << out << endl;
			break;

		case 2:
			cin.ignore();

			cout << endl;
			cout << "-------------------" << endl;
			cout << "* Input           *" << endl;
			cout << "-------------------" << endl;

			cout << "Plain text:" << endl;
			getline(cin, text);
			cout << "Key: " << endl;
			getline(cin, key);
			
			vector<char> data(text.begin(), text.end());
			out = typeOption(data, key);

			cout << "Input: " << text << endl;
			cout << "Key: " << key << endl;
			cout << "Output: " << out << endl;
			break;
	}

	cin.ignore();
	cout << endl;
	cout << endl;
	cout << "-------------------" << endl;
	cout << "* Save to File    *" << endl;
	cout << "-------------------" << endl;
	cout << "File path:" << endl;
	getline(cin, path);

	saveFile(path, out);
}