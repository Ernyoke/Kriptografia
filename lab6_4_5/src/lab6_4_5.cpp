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

pair<NTL::ZZ, NTL::ZZ> fermatfactor(NTL::ZZ &n)
{
	NTL::ZZ p, q;
	NTL::ZZ a = NTL::SqrRoot(n) + 1;
	//cout<<a<<endl;
	NTL::ZZ b1 = a * a - n;
	//cout<<b1<<endl;
	NTL::ZZ temp;
	while (true)
	{
		temp = squareNumber(b1);
		if (temp != 1)
		{
			p = a + temp;
			q = a - temp;
			return make_pair(p, q);
		}
		a = a + 1;
		b1 = a * a - n;
	}
}


int main() {
	ifstream in4("cryptFermat_UgyanazAKonyv", ifstream::binary);
	ifstream in5("cryptFermat_UgyanazAKonyv", ifstream::binary);
//	feladat 4-5
	NTL::ZZ n = NTL::to_ZZ("5490825390594314933635556892029728299068042651056400882476464354295557367845507812388397619028076478525907246249712811666357715361147612799089176536622391");
	NTL::ZZ IV_origin = NTL::to_ZZ("437295282950606442428069717814641185553876309614812522540939103487329333558670543642449576173158069601951913444279257903961994867883400923858709488");
	NTL::ZZ p, q;

//	feladat 4-5
	pair<NTL::ZZ, NTL::ZZ> result = fermatfactor(n);

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
	if(!in4.is_open()) {
		cout<<"Error opening in_file\n";
		return 0;
	}

	if(!in5.is_open()) {
		cout<<"Error opening in_file\n";
		return 0;
	}

	ofstream out4("Decrypted_fermat_4.gif", ifstream::binary);
	if(!out4.is_open()) {
		cout << "Error opening out_file\n";
		return 0;
	}

	ofstream out5("Decrypted_fermat_5.gif", ifstream::binary);
	if(!out5.is_open()) {
		cout << "Error opening out_file\n";
		return 0;
	}

	unsigned char * fsize = new unsigned char[4];
	in4.read((char*)fsize, 4);
	in5.read((char*)fsize, 4);
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

	//feladat 4.
	clock_t begin = clock();
	NTL::ZZ IV = IV_origin;
	for (int i = 0; i < k2 + 2; i++)
	{

		in4.read(memblock, k + 1);
		ZZFromBytes(nr, (unsigned char*)memblock, k + 1);
		NTL::ZZ dnr = PowerMod(nr, d, n);
		dnr = dnr ^ IV;
		IV = nr;

		if (i != k2 + 1)
		{
			BytesFromZZ((unsigned char*)memblock, dnr, k);
			out4.write(memblock, k);
		}
		else
		{
			BytesFromZZ((unsigned char*)memblock, dnr, k1);
			out4.write(memblock, k1);
		}

	}
	clock_t end = clock();

	cout << "Fel4 time: " << double(end - begin) / CLOCKS_PER_SEC << endl;

	//feladat 5
	begin = clock();
	IV = IV_origin;
	for (int i = 0; i < k2 + 2; i++)
	{

		in5.read(memblock, k + 1);
		ZZFromBytes(nr, (unsigned char*)memblock, k + 1);
		NTL::ZZ	xp = PowerMod(nr % p, dp, p);
		NTL::ZZ	xq = PowerMod(nr % q, dq, q);
		NTL::ZZ dnr = (Mq * q * xp + Mp * p * xq ) % n;
		dnr = dnr ^ IV;
		IV = nr;

		if (i != k2 + 1)
		{
			BytesFromZZ((unsigned char*)memblock, dnr, k);
			out5.write(memblock,k);
		}
		else
		{
			BytesFromZZ((unsigned char*)memblock, dnr, k1);
			out5.write(memblock, k1);
		}

	}
	end = clock();

	cout << "Fel5 time: " << double(end - begin) / CLOCKS_PER_SEC << endl;

	in4.close();
	in5.close();
	out4.close();
	out5.close();
}
