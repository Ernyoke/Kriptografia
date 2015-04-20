//============================================================================
// Name        : lab6_3_rsa_decrypt.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <NTL/ZZ.h>

using namespace std;

int charToNr(char c) {
	if(c >= 'A' && c <= 'Z') {
		return c - 'A';
	}
	else {
		if(c == ' ') {
			return 26;
		}
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

void outputToFile(NTL::ZZ& nr) {
	vector<NTL::ZZ> mod_res;
	//NTL::ZZ div(27);
	int div = 27;
	int res;
	int i = 0;
	while(nr > 0) {
		i++;
		//NTL::conv(res, nr % div);
		res = nr % div;
		nr = nr / div;
		cout << nrToChar(res);
	}
	while(i < 5) {
		cout << "A";
		++i;
	}
}

NTL::ZZ makeNr(string& line) {
	NTL::ZZ nr, pw(1);
	for(unsigned int i = 0; i < line.length(); ++i) {
		nr = nr + (charToNr(line[i]) * pw);
		pw = pw * 27;
	}
	return nr;
}

NTL::ZZ cubeRoot(NTL::ZZ nr) {
	NTL::ZZ x(1);
	NTL::ZZ x_n(1);
	do {
		x = x_n;
		x_n = (2 * x + nr / (x * x)) / 3;
	}
	while(x != x_n);
	return x;
}

int main() {

	string _key1 = "key1.txt";
	string _key2 = "key2.txt";
	string _key3 = "key3.txt";
	string _encrypt1 = "encrypt1.txt";
	string _encrypt2 = "encrypt2.txt";
	string _encrypt3 = "encrypt3.txt";

	NTL::ZZ key1, key2, key3;
	string enc1, enc2, enc3;


	//read from file
	ifstream file_key1;
	file_key1.open(_key1.c_str(), ios::in);
	if(file_key1.is_open()) {
		file_key1 >> key1;
		cout << key1 << endl;
	}
	else {
		cerr << _key1 << " " << "could not be opened!" << endl;
		return -1;
	}

	ifstream file_key2;
	file_key2.open(_key2.c_str(), ios::in);
	if(file_key2.is_open()) {
		file_key2 >> key2;
		cout << key2 << endl;
	}
	else {
		cerr << _key2 << " " << "could not be opened!" << endl;
		return -1;
	}

	ifstream file_key3;
	file_key3.open(_key3.c_str(), ios::in);
	if(file_key3.is_open()) {
		file_key3 >> key3;
		cout << key3 << endl;
	}
	else {
		cerr << _key3 << " " << "could not be opened!" << endl;
		return -1;
	}

	ifstream file_encrypt1;
	file_encrypt1.open(_encrypt1.c_str(), ios::in);
	if(file_encrypt1.is_open()) {
		getline(file_encrypt1, enc1);
		cout << enc1 << endl;
	}
	else {
		cerr << _encrypt1 << " " << "could not be opened!" << endl;
		return -1;
	}

	ifstream file_encrypt2;
	file_encrypt2.open(_encrypt2.c_str(), ios::in);
	if(file_encrypt2.is_open()) {
		getline(file_encrypt2, enc2);
		cout << enc2 << endl;
	}
	else {
		cerr << _encrypt2 << " " << "could not be opened!" << endl;
		return -1;
	}

	ifstream file_encrypt3;
	file_encrypt3.open(_encrypt3.c_str(), ios::in);
	if(file_encrypt3.is_open()) {
		getline(file_encrypt3, enc3);
		cout << enc3 << endl;
	}
	else {
		cerr << _encrypt3 << " " << "could not be opened!" << endl;
		return -1;
	}

	NTL::ZZ nr1, nr2, nr3;
	nr1 = makeNr(enc1);
//	cout << nr1 << endl;
	nr2 = makeNr(enc2);
//	cout << nr2 << endl;
	nr3 = makeNr(enc3);
//	cout << nr3 << endl;

	NTL::ZZ m1, m2, m3;
	NTL::ZZ inv1, inv2, inv3;
	m1 = key2 * key3;
	NTL::ZZ temp = m1 % key1;
	NTL::InvMod(inv1,temp,key1);
//	inv1 = NTL::InvMod(temp, key1);
//	cout << inv1 << endl;
	m2 = key1 * key3;
	temp = m2 % key2;
	NTL::InvMod(inv2,temp,key2);
//	inv2 = NTL::InvMod(temp, key2);
//	cout << inv2 << endl;
	m3 = key2 * key1;
	temp = m3 % key3;
	NTL::InvMod(inv3,temp,key3);
//	inv3 = NTL::InvMod(temp, key3);
//	cout << inv3 << endl;

	NTL::ZZ y = (nr1 * inv1 * m1);
	y += (nr2 * inv2 * m2);
	y += (nr3 * inv3 * m3);
	NTL::ZZ key_div = key1 * key2 * key3;

	NTL::ZZ y_fin = y % key_div;

	cout << key_div << endl;
	cout << y << endl;
	cout << y_fin << endl;
	cout << cubeRoot(y_fin) << endl;

//	NTL::ZZ nnr = NTL::PowerMod(nr1, cubeRoot(y_fin), key1);

	NTL::ZZ nnr = cubeRoot(y_fin);

	outputToFile(nnr);


	return 0;
}
