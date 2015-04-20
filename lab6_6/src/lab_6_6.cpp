//============================================================================
// Name        : lab6_4_5.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <ctime>
#include <NTL/ZZ.h>

using namespace std;

NTL::ZZ squareNumber(NTL::ZZ b)
{
	NTL::ZZ tmp = NTL::SqrRoot(b);
	if (tmp * tmp == b) {
		return tmp;
	}
	else {
		return NTL::to_ZZ(1);
	}
}

pair<NTL::ZZ, NTL::ZZ> pollard_rho(NTL::ZZ& n) {
	NTL::ZZ a(1);
	NTL::ZZ b(1); // b = a * a + 1
	NTL::ZZ d;
	while (true) {
		a = (a * a + 1) % n;
		b = (b * b + 1) % n;
		b = (b * b + 1) % n;
		d = NTL::GCD(a - b, n);
		if ((1 < d) && (d < n)) {
			return make_pair(d, n / d);
		}
		if (d == n) {
			return make_pair(1, 1);
		}
		}
}

int main() {
	ifstream in("cryptPollard_EbresztoOra", ifstream::binary);
	NTL::ZZ n = NTL::to_ZZ("17748036239379766307931692520738980005896746909927296278072673012492440057754176594936965133972986983854651605003199844923434396894098575074131383792758978666207827");
	NTL::ZZ IV_origin = NTL::to_ZZ("16577606975862568612085801182442414811717940161171064671");
	NTL::ZZ p, q;

//	feladat 6.
	pair<NTL::ZZ, NTL::ZZ> result = pollard_rho(n);

	p = result.first;
	q = result.second;
	cout<<"p= "<<p<<endl<<"q= "<<q<<endl;

	NTL::ZZ d, e = NTL::to_ZZ("65537");

	InvMod(d, e, (p - 1) * (q - 1));
	cout << "d= " << d << endl;
	//feladat 5 ---------------------
	NTL::ZZ dp = d % (p-1);
	NTL::ZZ dq = d % (q-1);
	NTL::ZZ Mq, Mp;

	InvMod(Mq, q % p, p);
	InvMod(Mp, p % q, q);
	//-------------------------------
	if(!in.is_open()) {
		cout<<"Error opening in_file\n";
		return 0;
	}

	ofstream out("Decrypted_pollard.jpg", ifstream::binary);
	if(!out.is_open()) {
		cout << "Error opening out_file\n";
		return 0;
	}

	unsigned char * fsize = new unsigned char[4];
	in.read((char*)fsize, 4);
	long fs = 0, prod = 1;
	for (int i = 0; i < 4; i++)
	{
		fs += fsize[i] * prod;
		prod *= 256;
	}

	cout<<"File size = "<< fs <<endl;

	long k = ceil(log(n) / log(NTL::to_ZZ(256))) - 1;
	long k1 = fs % k;
	long k2 = fs / k;

	char* memblock = new char[k+1];
	NTL::ZZ nr;

	clock_t begin = clock();
	NTL::ZZ IV = IV_origin;
	for (int i = 0; i < k2 + 2; i++)
	{

		in.read(memblock, k + 1);
		ZZFromBytes(nr, (unsigned char*)memblock, k + 1);
		NTL::ZZ	xp = PowerMod(nr % p, dp, p);
		NTL::ZZ	xq = PowerMod(nr % q, dq, q);
		NTL::ZZ dnr = (Mq * q * xp + Mp * p * xq ) % n;
		dnr = dnr ^ IV;
		IV = nr;

		if (i != k2 + 1)
		{
			BytesFromZZ((unsigned char*)memblock, dnr, k);
			out.write(memblock,k);
		}
		else
		{
			BytesFromZZ((unsigned char*)memblock, dnr, k1);
			out.write(memblock, k1);
		}

	}
	clock_t end = clock();

	cout << "Fel5 time: " << double(end - begin) / CLOCKS_PER_SEC << endl;

	in.close();
	out.close();
}
