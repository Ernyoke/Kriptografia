//============================================================================
// Name        : lab8_2.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <fstream>
#include <NTL/ZZ.h>
#include <iostream>

using namespace std;

NTL::ZZ brute_force(NTL::ZZ &g, NTL::ZZ &A, NTL::ZZ &p){
	NTL::ZZ i(1);
	while (true)
	{
		if (PowerMod(g, i, p) == A)
		{
			return i;
		}
		i++;
	}
}

int main()
{
	NTL::ZZ p = NTL::to_ZZ("1910759");
	NTL::ZZ g = NTL::to_ZZ("1548629");
	NTL::ZZ A = NTL::to_ZZ("996441");

	ifstream in_file("cryptElGamal", ifstream::binary);
	if(!in_file.is_open()) {
		cerr << "Error opening in_file cryptElGamal" << endl;
		return 0;
	}

	ofstream out_file("Decrypted.zip", ifstream::binary);
	if(!out_file.is_open()) {
		cerr << "Error opening in_file Decrypted.zip" << endl;
		return 0;
	}

	NTL::ZZ a = brute_force(g, A, p);
	cout << "Secret key: " << a << endl;

	unsigned char * fsize = new unsigned char[4];
	in_file.read((char*)fsize, 4);
	long fs = 0, prod = 1;
	for (int i = 0; i < 4; i++)
	{
		fs += fsize[i] * prod;
		prod *= 256;
	}
	cout << "File size: " << fs << endl;

	long k = log(p) / log(256);
	long k1 = fs % k;
	long k2 = fs / k;
	cout << "k= " << k << endl;
	cout << "k1= " << k1 << endl;
	cout << "k2= " << k2 << endl;

	char* buffer = new char[k + 1];
	NTL::ZZ B, C, nr;

	for(int i = 0; i <= k2; ++i)
	{
		in_file.read(buffer, k + 1);
		ZZFromBytes(B,(unsigned char*)buffer, k + 1);
		in_file.read(buffer, k + 1);
		ZZFromBytes(C,(unsigned char*)buffer, k + 1);

		NTL::ZZ a1 = p - 1 - a;
		nr = (PowerMod(B, a1, p) * C) % p;

		if (i == k2 + 1)
		{
			BytesFromZZ((unsigned char*)buffer, nr, k1);
			out_file.write(buffer, k1);
		}
		else
		{
			BytesFromZZ((unsigned char*)buffer, nr, k);
			out_file.write(buffer, k);
		}

	}

	out_file.close();
	in_file.close();

	return 0;
}
