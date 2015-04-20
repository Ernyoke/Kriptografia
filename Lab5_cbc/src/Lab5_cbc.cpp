//============================================================================
// Name        : Lab5_cbc.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Affine.h"
#include "Hill.h"
#include "Cbc.h"

using namespace std;

int main() {
	string fileAffine = "cryptAffine256_Tanacs";
	string keyAffine = "key_affin.txt";
	string outputAffine = "decrypted_affine.jpg";

	string keyHill = "key_hill.txt";
	string fileHill = "cryptHill256_Ikrek";
	string outputHill = "decrypted_hill.jpg";

	char ivAffin[1];
	ivAffin[0] = 19;

	char ivHill[2];
	ivHill[0] = 129;
	ivHill[1] = 131;

//	Affine *affine =  new Affine();
//	affine->setKey(keyAffine);

//	Cbc cbc(affine);
//	cbc.decrypt(ivAffin, fileAffine, outputAffine);

//	Hill *hill = new Hill();
//	hill->setKey(keyHill);
//	Cbc cbc(hill);
//	cbc.decrypt(ivHill, fileHill, outputHill);

	return 0;
}
