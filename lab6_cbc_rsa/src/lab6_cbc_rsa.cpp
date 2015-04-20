//============================================================================
// Name        : lab6_cbc_rsa.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <NTL/ZZ.h>
#include <vector>
#include <fstream>

using namespace std;
using namespace NTL;

bool isSquareNumber(long a) {
	long sqr = std::sqrt(a);
	if(sqr * sqr == a) {
		return true;
	}
	return false;
}

pair<long, long> fermatfaktor(long n) {
	long a = std::ceil(std::sqrt(n));
//	ZZ a = NTL::ro
	long b = a * a - n;
	while(!isSquareNumber(b)) {
		a = a + 1;
		b = a * a - n;
	}
	return make_pair<long, long>(a + sqrt(b), a - sqrt(b));
}

pair<long, pair<long, long> > extendedEuclid(long a, long b) {
	long x = 1, y = 0;
	long xLast = 0, yLast = 1;
	long q, r, m, n;
    while(a != 0) {
        q = b / a;
        r = b % a;
        m = xLast - q * x;
        n = yLast - q * y;
        xLast = x, yLast = y;
        x = m, y = n;
        b = a, a = r;
    }
    return make_pair(b, make_pair(xLast, yLast));
}

long modInverse(long a, long m) {
    return (extendedEuclid(a,m).second.first + m) % m;
}

long breakSecretKey(long key1, long key2) {
	pair<long, long> res = fermatfaktor(key1);
	long phi = (res.first - 1) * (res.second - 1);
	long sec_key = modInverse(key2, phi);
	return sec_key;
}

int charToNr(char c) {
	if(c >= 'A' && c <= 'Z') {
		return c - 'A';
	}
	if(c == ' ') {
		return 26;
	}
	return -1;
}

char nrToChar(int &c) {
	if(c >= 0 && c < 26) {
			return c + 'A';
		}
		if(c == 26) {
			return ' ';
		}
		cout << "Error" << endl;
		return ' ';
}

ZZ makeZZ(string &line) {
	ZZ nr;
	ZZ pw(1);
	for(unsigned int i = 0; i < line.size(); ++i) {
		int v = charToNr(line[i]);
		if(v >= 0) {
			nr = nr + (pw * v);
			pw = pw * 27;
		}
	}
	return nr;
}

void outputToFile(ZZ& nr, ofstream& file) {
	vector<ZZ> mod_res;
	ZZ div(27);
	int res;
	int i = 0;
	while(nr > 0) {
		i++;
		NTL::conv(res, nr % div);
		nr = nr / div;
		cout << nrToChar(res);
	}
	while(i < 5) {
		cout << "A";
		++i;
	}
}

int main() {
	long n = 117909607;
	long e = 65537;
	ZZ iv(123456);
	ZZ n_ZZ(n);

	string file_in = "in.txt";
	string file_out = "out.txt";

	string text;
	string clean_text;

	//read from file
	ifstream input_stream;
	input_stream.open("in.txt", ios::in);
	ofstream result;
	result.open("out.txt", ios::out);

	if(!input_stream.is_open()) {
		cout << "Input file is not opened!";
		return -1;
	}

	if(!result.is_open()) {
		cout << "Output file is not opened!";
		return -1;
	}

	long secretKey = breakSecretKey(n, e);
	ZZ secretZZ(secretKey);
	cout << "Secret key: " << secretKey << endl;

	string line;
	while(getline(input_stream, line)) {
		text.append(line);
	}

	for(unsigned int i = 0; i < text.size(); ++i) {
		if(text[i] >= 'A' && text[i] <= 'Z') {
			clean_text += text[i];
		}
		else {
			if(text[i] == ' ') {
				clean_text += text[i];
			}
		}
	}

	cout << clean_text << endl;

	for(unsigned int i = 0; i < clean_text.size(); i = i + 6) {
		string conv = clean_text.substr(i, 6);
		ZZ nr = makeZZ(conv);
		ZZ decrypted;
//		cout << nr << " " << " " << n_ZZ << endl;
		ZZ nnr = NTL::PowerMod(nr, secretZZ, n_ZZ);
		NTL::bit_xor(decrypted, iv, nnr);
		iv = nr;
		outputToFile(decrypted, result);
	}

	return 0;
}
