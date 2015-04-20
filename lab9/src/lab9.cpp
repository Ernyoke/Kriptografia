//============================================================================
// Name        : lab9.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>

using namespace std;

int main() {

	ifstream file;
	file.open("gen.txt", ios::in);

	NTL::ZZ p;
	NTL::ZZ q;
	NTL::ZZ gen;

	if(file.is_open()) {
		file >> p;
		q = (p - 1) / 2;
		while(!file.eof()) {
			file >> gen;
			if(NTL::PowerMod(gen, q, p) == p - 1) {
				break;
			}
		}
	}
	else {
		cerr << "gen.txt" << " " << "could not be opened!" << endl;
		return -1;
	}

	cout << p << endl;
	cout << gen << endl;

	NTL::ZZ b = NTL::RandomBnd(p - 1);

	cout << "b= " << b << endl;

	NTL::ZZ B = NTL::PowerMod(gen, b, p);

	cout << "B = " << B << endl;

	cout << "" << endl; // prints

//	NTL::ZZ A = NTL::to_ZZ("1400707708742705595642720076587623587669759696580297258315010107758915221428592391512525905289778305880210281848897746702834949095945342393080218461647201");

//	b = NTL::to_ZZ("4776521974413516149762174423126622498056368893792704647845491258154083508055735479932843495741283561575898737099611367291994114002623710430078361853640842");

//	NTL::ZZ K = NTL::PowerMod(A, b, p);

//	cout << "K = " << K << endl;

	NTL::ZZ A = NTL::to_ZZ("2472369130535599958160492470336063582250225793855896772273031369079804253109617539125306090552636696036966688932544077934231138916538241109796485725613976");
	b = NTL::to_ZZ("5088292884022003089654614061600363675621740590132794198429143941228481325211296289806956479182264863828829662814283956323627061972318585006915816578478196");
	NTL::ZZ K = NTL::PowerMod(A, b, p);
	cout << "K = " << K << endl;
	return 0;
}
