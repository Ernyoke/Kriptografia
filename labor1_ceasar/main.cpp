/* 
 * File:   main.cpp
 * Author: ervin
 *
 * Created on February 11, 2015, 10:18 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    string line;
    string hidden;
    string visible;
    ifstream file("input.txt");
    int key = 0;
    cout << "Please enter the key:";
    cin >> key;
    if(file.is_open()) {
        while(getline(file, line)) {
//            cout << line << endl;
            int i = 0;
            while(i < line.length()) {
                char b = line.at(i);
                if(b != ' ') {
                    char tb = ((b - 65) + key) % 26 + 65;
                    hidden += tb;
                }
                else {
                    hidden += b;
                }
                ++i;
            }
        }
        hidden += '\n';
    }
    
    cout << hidden;
    
    //decrypt
    
    for(int i = 0; i < hidden.length(); ++i) {
        char tb = hidden.at(i);
        if(tb >= 'A' && tb <= 'Z') {
            char tmp = tb - 65 - key;
            if(tmp < 0) {
                tmp += 26;
            }
            visible += tmp + 65;
        }
        else {
            visible += tb;
        }
    }
    
    cout << visible;
    
    return 0;
}

