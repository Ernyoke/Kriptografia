//============================================================================
// Name        : lab3_hill_eclipse.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hill algorithm
//============================================================================

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <eigen3/Eigen/Eigen>

using namespace std;
using namespace Eigen;
/*
 *
 */


void printMatrix(MatrixXi &mat, string &crypted) {
    int n = mat.rows();
    for(int i = 0; i < n; ++i) {
        char c = (mat(i, 0) % 26) + 65;
        crypted += c;
    }
}

int find_inv(int a, int x) {
    for(int i = 1; i <= x; ++i) {
        if((a * i) % 26 == 1) {
            return i;
        }
    }
    return -1;
}

pair<int, pair<int, int> > extendedEuclid(int a, int b) {
    int x = 1, y = 0;
    int xLast = 0, yLast = 1;
    int q, r, m, n;
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

int modInverse(int a, int m) {
    return (extendedEuclid(a,m).second.first + m) % m;
}

int main(int argc, char** argv) {

    ifstream file_in("in.txt");
    ifstream key_in("key.txt");
    ofstream file_out("out.txt", ofstream::out);
    string line, crypted, decrypted;
    vector<string>vanilla;
    int cryptedNr = 0, decryptedNr = 0;

    MatrixXi *key;
    int keySize;

    if(key_in.is_open()) {
        key_in >> keySize;
        int aux;
        key = new MatrixXi(keySize, keySize);
        for(int i = 0; i < keySize; ++i) {
            for(int j = 0; j < keySize; ++j) {
                key_in >> aux;
                (*key)(i, j) = aux;
            }
        }

        cout << *key;
    }

    if(file_in.is_open() && file_out.is_open()) {
        while(getline(file_in, line)) {
            vanilla.push_back(line);
        }
    }

    int j = 0;
    MatrixXi slice(keySize, 1);
    for(vector<string>::iterator it = vanilla.begin(); it != vanilla.end(); ++it) {
        for(int i = 0; i < (*it).length(); ++i) {
            char c = (*it)[i];
            if(c >= 'a' && c <= 'z') {
                c = c - 32;
            }
            if(c >= 'A' && c <= 'Z') {
                slice(j++, 0) = c - 'A';
                cryptedNr++;
            }
            if(j == keySize) {
                MatrixXi res(keySize, 1);
                res = (*key) * slice;
                j = 0;
                printMatrix(res, crypted);
            }
        }
    }
    if(j > 0) {
        for(; j < keySize; ++j) {
            slice(j, 0) = 'Y' - 'A';
        }
        cout << slice << endl;
        MatrixXi res(keySize, 1);
        res = (*key) * slice;
        printMatrix(res, crypted);
    }

    file_out << crypted;
    cout << endl << crypted << endl;

    //calculate inverse

    MatrixXf fl = key->template cast<float>();

    int det = round(fl.determinant());
    int inv = modInverse(det, 26);

    MatrixXf adjugate = det * fl.inverse();
    cout << "Adjugate:" << endl;
    cout << adjugate;

    MatrixXi inv_mat(keySize, keySize);
    for(int i = 0; i < keySize; ++i) {
    	for(int k = 0; k < keySize; ++k) {
    		double aux = adjugate(i, k);
    		inv_mat(i, k) = round(aux);
    	}
    }
    inv_mat = inv * inv_mat;

    for(int i = 0; i < keySize; ++i) {
        for(int j = 0; j < keySize; ++j) {
        	inv_mat(i, j) = inv_mat(i, j) % 26;
        	if(inv_mat(i, j) < 0) {
        		inv_mat(i, j) = inv_mat(i, j) + 26;
        	}
        }
    }

    cout << endl << "Inv mat:" << endl;
    cout << inv_mat << endl;

    //decrypt text
    MatrixXi mat(keySize, 1);
    j = 0;
    for(int i = 0; i < crypted.length(); ++i) {
    	if(j < keySize) {
    		mat(j++, 0) = crypted[i] - 'A';
    	}
    	else {
    		MatrixXi res = inv_mat * mat;
    		for(int k = 0; k < keySize; ++k) {
    			int c = (res(k, 0) % 26);
    			if(c < 0) {
    				c += 26;
    			}
				char ch = c + 'A';
				cout << ch;
				decryptedNr++;
    		}
    		j = 0;
    		mat(j++, 0) = crypted[i] - 'A';

    	}
    }

    if(j >= keySize) {
    	MatrixXi res = inv_mat * mat;
//    	cout << endl << mat << endl;
    	for(int k = 0; k < keySize; ++k) {
    		int c = (res(k, 0) % 26);
    		if(c < 0) {
    			c += 26;
    		}
    		if(decryptedNr < cryptedNr) {
				char ch = c + 'A';
				cout << ch;
				decryptedNr++;
    		}
    	}
    }
    cout << endl;

    file_out.close();
    delete key;

    return 0;
}
