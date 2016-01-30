#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>

#include "tools.h"
using namespace std;

vector<char> vigenereStdEncrypt(vector<char> &plaintxt, int option, int upper_case, string key) {
	if (upper_case)	{
		toUpperCase(&plaintxt);
	}
	stringToUpper(key);

	switch (option) {
		case 0:
			break;
		case 1:
			eraseSpace(&plaintxt);
			break;
		case 2:
			eraseSpace(&plaintxt);
			addSpace(&plaintxt, 5);
			break;
	}

	int i = 0; 
	int n = 0;
	while (i < plaintxt.size()) {
		int total = (90 - 65 + 1);

		if ( 65 <= plaintxt.at(i) && plaintxt.at(i) <= 90 ) {
			char cipher = (mod((plaintxt.at(i) - 65 + key[n] - 65), total)) + 65;
			++n;
			if ( n >= key.length() ) n = 0;

			plaintxt.erase(plaintxt.begin()+i);
			plaintxt.insert(plaintxt.begin()+i, cipher);
		}
		++i;
	}

	return plaintxt;
} 

vector<char> vigenereStdDecrypt(vector<char> &ciphertxt, string key) {
	stringToUpper(key);
	int i = 0; 
	int n = 0;
	while (i < ciphertxt.size()) {
		int total = (90 - 65 + 1);

		if ( 65 <= ciphertxt.at(i) && ciphertxt.at(i) <= 90 ) {
			char cipher = (mod((ciphertxt.at(i) - 65 - (key[n] - 65)), total)) + 65;
			++n;
			if ( n >= key.length() ) n = 0;

			ciphertxt.erase(ciphertxt.begin()+i);
			ciphertxt.insert(ciphertxt.begin()+i, cipher);
		}
		++i;
	}

	return ciphertxt;
} 

vector<char> vigenereExtEncrypt(vector<char> &plaintxt, int option, int upper_case, string key) {
	if (upper_case)	{
		toUpperCase(&plaintxt);
	}
	stringToUpper(key);

	switch (option) {
		case 0:
			break;
		case 1:
			eraseSpace(&plaintxt);
			break;
		case 2:
			eraseSpace(&plaintxt);
			addSpace(&plaintxt, 5);
			break;
	}

	int i = 0; 
	int n = 0;
	while (i < plaintxt.size()) {
		int total = (255 - 0 + 1);
		
		if ( 0 <= mod(plaintxt.at(i), total) && mod(plaintxt.at(i), total) <= 255 ) {
			char cipher = (mod((plaintxt.at(i) - 0 + key[n] - 0), total)) + 0;
			++n;
			if ( n >= key.length() ) n = 0;

			plaintxt.erase(plaintxt.begin()+i);
			plaintxt.insert(plaintxt.begin()+i, cipher);
		}
		++i;
	}

	return plaintxt;
} 

vector<char> vigenereExtDecrypt(vector<char> &ciphertxt, string key) {
	stringToUpper(key);
	int i = 0; 
	int n = 0;
	while (i < ciphertxt.size()) {
		int total = (255 - 0 + 1);

		if ( 0 <= mod(ciphertxt.at(i), total) && mod(ciphertxt.at(i), total) <= 255 ) {
			char cipher = (mod((ciphertxt.at(i) - 0 - (key[n] - 0)), total)) + 0;
			++n;
			if ( n >= key.length() ) n = 0;

			ciphertxt.erase(ciphertxt.begin()+i);
			ciphertxt.insert(ciphertxt.begin()+i, cipher);
		}
		++i;
	}

	return ciphertxt;
} 

void preventDouble(vector<char> *text, char c) {
	int i = 0;
	while ( i < text->size() ) {
		if ( !(i + 1 >= text->size()) ) {
			if(text->at(i) == text->at(i+1)) {
				text->insert(text->begin()+i+1, c);	
			}
		} else {
			text->insert(text->begin()+i+1, c);		
		}
		i += 2;
	}	
}

vector<char> playfairKey(vector<char> &plaintxt) {
	/* SANITIZE */
	toUpperCase(&plaintxt);
	eraseExceptAlphabet(&plaintxt);

	vector<char> alphabet;
	vector<char> key;
	for (int i = 1; i <= 26; i++) {
		alphabet.push_back(i+64);
	}

	while (!plaintxt.empty()) {
		alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), plaintxt.at(0)), alphabet.end());
		key.push_back(plaintxt.at(0));
		char temp = plaintxt.at(0);
		plaintxt.erase(std::remove(plaintxt.begin(), plaintxt.end(), temp), plaintxt.end());
	}

	key.insert( key.end(), alphabet.begin(), alphabet.end() );
	
	/* Erase J */
	key.erase(std::remove(key.begin(), key.end(), 'J'), key.end());

	return key;
}

vector<char> playfair(vector<char> &plaintxt, int option, string key, int decrypt) {
	vector<char> keys;
	vector<char> encrypted;
	int i = 0;
	while (i < key.length()) {
		keys.push_back(key[i]);
		++i;
	}

	/* Making playfair key */
	keys = playfairKey(keys);
	cout << "[key] " << vectorToString(keys) << endl;

	/* Make plaintext ready to Encrypt */
	toUpperCase(&plaintxt);
	eraseExceptAlphabet(&plaintxt);
	eraseSpace(&plaintxt);
	preventDouble(&plaintxt, 'X');


	int n = 0;
	int size = 5;
	while ( n < plaintxt.size() ) {
		if ( n + 1 < plaintxt.size() ) {
			int pos1, pos2;

			if (plaintxt.at(n) != 'J') {
				pos1 = distance(keys.begin(), find(keys.begin(), keys.end(), plaintxt.at(n)));
			} else {
				pos1 = distance(keys.begin(), find(keys.begin(), keys.end(), 'I'));
			}

			if (plaintxt.at(n+1) != 'J') {
				pos2 = distance(keys.begin(), find(keys.begin(), keys.end(), plaintxt.at(n+1)));
			} else {
				pos2 = distance(keys.begin(), find(keys.begin(), keys.end(), 'I'));				
			}			

			int x = 1;
			if(decrypt) { x = -1; }

			if ( YFromInt(pos1, size) == YFromInt(pos2, size) ) {
				encrypted.push_back(keys.at( YFromInt(pos1,size) * size + mod(XFromInt(pos1, size)+x, size) ));
				encrypted.push_back(keys.at( YFromInt(pos2,size) * size + mod(XFromInt(pos2, size)+x, size) ));
			} else if ( XFromInt(pos1, size) == XFromInt(pos2, size) ) {
				encrypted.push_back(keys.at( mod(YFromInt(pos1,size)+x, size) * size + XFromInt(pos1, size) ));
				encrypted.push_back(keys.at( mod(YFromInt(pos2,size)+x, size) * size + XFromInt(pos2, size) ));
			} else {
				encrypted.push_back(keys.at( YFromInt(pos1,size) * size + XFromInt(pos2, size) ));
				encrypted.push_back(keys.at( YFromInt(pos2,size) * size + XFromInt(pos1, size) ));		
			}
		}

		n += 2;
	}
	
	switch (option) {
		case 0:
			break;
		case 1:
			eraseSpace(&encrypted);
			break;
		case 2:
			eraseSpace(&encrypted);
			addSpace(&encrypted, 5);
			break;
	}

	return encrypted;
}