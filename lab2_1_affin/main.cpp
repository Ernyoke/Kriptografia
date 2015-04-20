/* 
 * File:   main.cpp
 * Author: ervin
 *
 * Created on February 12, 2015, 10:25 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */


//int inv_euclid(int a, int b) {
//    int x0 = 1;
//    int x1 = 0;
//    int y0 = 0;
//    int y1 = 1;
//    int sign = 1;
//    while(b > 0) {
//        int r = a % b;
//        int q = a / b;
//        a = b;
//        b = r;
//        int xx = x1;
//        int yy = y1;
//        x1 = q * x1 + x0;
//        y1 = q * y1 + y0;
//        x0 = xx; 
//        y0 = yy;
//        sign = -sign;
//    }
//    cout << x0 << endl;
//    cout << y0 << endl;
//    return a;
//}

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

    int key_a, key_b;
    ifstream file_in("input.txt");
    ofstream file_out("output_txt", ofstream::out);
    string line, crypted, decrypted;
    cout << "Key_a:";
    cin >> key_a;
    cout << "Key_b:";
    cin >> key_b;
    
    char inv = find_inv(key_a, 26);
    cout << "Inverz:" << (int)inv << endl;
    
    if(inv > 0) {
    
    if(file_in.is_open() && file_out.is_open()) {
        //encryption
        while(getline(file_in, line)) {
            for(int i = 0; i < line.length(); ++i) {
                if(line[i] >= 'A' && line[i] <= 'Z') {
                    char c = (key_a * (line[i] - 'A') + key_b) % 26;
                    c = c + 'A';
                    crypted += c;
                }
            }
        }
        file_out << crypted;
        //decryption
       
       
        for(int i = 0; i < crypted.length(); ++i) {
            char c = crypted[i] - 'A';
            char p = (inv * c - inv * key_b) % 26;
            if(p < 0) {
                p += 26;
            }
            p = p + 'A';
            decrypted += p;
        }
        
        cout << decrypted; 
        
    }
    else {
        cout << "Error opening file!";
    }
    }
    else {
        cout << "Invalid key combination!";
    }
    
    return 0;
}

