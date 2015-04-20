/* 
 * File:   main.cpp
 * Author: ervin
 *
 * Created on February 19, 2015, 10:25 AM
 */

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
        int t1 = (a * i);
        int t2 = t1 % 26;
        if((a * i) % 26 == 1) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char** argv) {

    ifstream file_in("input.txt");
    ifstream key_in("key.txt");
    ofstream file_out("output.txt", ofstream::out);
    string line, crypted, decrypted;
    vector<string>vanilla;
    
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
            slice(j, 0) = 'Y';
        }
        MatrixXi res(keySize, 1);
        res = (*key) * res;
        printMatrix(res, crypted);
    }
    
    file_out << crypted;
    cout << endl << crypted << endl;
    
    //calculate inverse
    
    MatrixXf fl = key->template cast<float>();
    
    int det = round(fl.determinant());
    int inv = find_inv(det % 26, 26);
    
    MatrixXi inv_mat = (inv * key->adjoint());
    
    for(int i = 0; i < keySize; ++i) {
        for(int j = 0; j < keySize; ++j) {
            inv_mat(i, j) = inv_mat(i, j) % 26;
        }
    }
    
    cout << inv_mat;
    
    file_out.close();
    delete key;
    
    return 0;
}

