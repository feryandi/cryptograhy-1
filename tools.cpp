#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstddef>
using namespace std;

int mod(int x, int m) {
    int r = x%m;
    return r<0 ? r+m : r;
}

string vectorToString(vector<char> text) {
	string txt(text.begin(), text.end());
	return txt;
}

void eraseSpace(vector<char> *text) {
	for (int i=0; i<text->size(); i++) {
		if(text->at(i) == ' ') text->erase(text->begin()+i);
	}	
}

void addSpace(vector<char> *text, int n) {
	int i = 0;
	int x = 0;
	while (i < text->size()) {
		if (x == n) {
			text->insert(text->begin()+i, ' ');
			++i;
			x = 0;
		}
		++x;
		++i;
	}
}

void eraseExceptAlphabet(vector<char> *text) {
	for (int i=0; i<text->size(); i++) {
		if(text->at(i) < 65 || text->at(i) > 90) {
			text->erase(text->begin()+i);
			--i;
		}
	}	
}

int XFromInt(int i, int l) {
	return (i - (i / l) * l );
}

int YFromInt(int i, int l) {
	return (i / l);
}

void toUpperCase(vector<char> *text) {
	for (int i=0; i<text->size(); i++) {
		int t = (int)text->at(i);
		if( 97 <= t && t <= 122 ) {
			char c = text->at(i) - 32;
			text->erase(text->begin()+i);
			text->insert(text->begin()+i, c);
		} 
	}		
}

void stringToUpper(string &s) {
	for (int i=0; i<s.length(); i++) {
		int t = (int)s[i];
		if( 97 <= t && t <= 122 ) {
			s[i] -= 32;
		}
	}		
}
