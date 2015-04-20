/* 
 * File:   main.cpp
 * Author: ervin
 *
 * Created on February 11, 2015, 10:57 AM
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

/*
 * 
 */

bool duplicate(string keyword, char c, int pos) {
    for(int i = 0; i < pos; ++i) {
        if(keyword[i] == c) {
            return true;
        }
    }
    return false;
}


int main(int argc, char** argv) {
    string keyword;
    int key;
    map<char, char>table;
    cout << "Please insert the key:";
    cin >> key;
    cout << "Please insert the keystring:";
    cin >> keyword;
    int loc = 0;
    int k = 0;
    loc = 'A' + key;
    for(int i = 0; i < keyword.length(); ++i) {
        char c = keyword[i];
        if(!duplicate(keyword, c, i)) {
            if(loc >= 'Z' + 1) {
                loc = 'A';
            }
            table.insert(make_pair<char, char>(loc, c));
            loc++;
        }
    }
    for(int i = 0; i < 26; ++i) {
        if(loc >= 'Z' + 1) {
            loc = 'A';
        }
        char c = i + 'A';
        if(keyword.find(c) == string::npos) {
            table.insert(make_pair<char, char>(loc, c));
            loc++;
        }
    }
    for(map<char, char>::iterator it = table.begin(); it != table.end(); ++it) {
        cout << (*it).first << " " << (*it).second << endl;
    }
    
    ifstream file("input.txt");
    ofstream file_out("output.txt", std::ofstream::out);
    string line;
    vector<string> crypted_vec;
    vector<string> decrypted_vec;
    string crypted;
    if(file.is_open()) {
        while(getline(file, line)) {
            crypted.clear();
            for(int i = 0; i < line.length(); ++i) {
                if(line[i] >= 'A' && line[i] <= 'Z') {
                   crypted += table[line[i]]; 
                }
                else {
                    crypted += line[i];
                }
            }
            crypted_vec.push_back(crypted);
            cout << crypted << endl;
            file_out << crypted << endl;
        }
    }
    
    //decrypt
    for(vector<string>::iterator vecIt = crypted_vec.begin(); vecIt != crypted_vec.end(); ++vecIt) {
        crypted = (*vecIt);
        for(int i = 0; i < crypted.length(); ++i) {
            if(crypted[i] >= 'A' && crypted[i] <= 'Z') {
                for(map<char, char>::iterator it = table.begin(); it != table.end(); ++it) {
                    if(crypted[i] >= 'A' && crypted[i] <= 'Z') {
                        if((*it).second == crypted[i]) {
                            cout << (*it).first;
                            file_out << (*it).first;
                        }
                    }
                }
            }
            else {
                cout << crypted[i];
                file_out << crypted[i];
            }
        }
        cout << endl;
        file_out << endl;
    }
    file_out.close();
}


