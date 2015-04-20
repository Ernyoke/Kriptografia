/* 
 * File:   main.cpp
 * Author: ervin
 *
 * Created on February 12, 2015, 11:30 AM
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/*
 * 
 */

int find_inv(int a, int x) {
    for(int i = 1; i < x; ++i) {
        if((a * i) % x == 1) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char** argv) {
    ifstream file_in("input.txt");
    ofstream file_out("output.txt", ofstream::out);
    vector<string>lines;
    if(file_in.is_open() && file_out.is_open()) {
        string line;
        while(getline(file_in, line)) {
            lines.push_back(line);
        }
        for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
            for(int a = 1; a < 26; a = a + 2) {
                for(int b = 0; b < 26; ++b) {
                    int inv = find_inv(a, 26);
                    if(inv > 0) {
                        file_out << "Key(" << a << "," << b << ")" << endl;
                        for(int i = 0; i < (*it).length(); ++i) {
                            char c = (*it)[i];
                            if(c >= 65 && c <= 90) {
                                char p = inv * ((c - 65) - b) % 26;
                                if(p < 0) {
                                    p += 26;
                                }
                                p += 65;
                                file_out << p;
                            }
                            else {
                                file_out << c;
                            }
                        }
                        file_out << endl << endl;
                    }
                }
            }
        }
    file_out.close();
    }
    return 0;
}

