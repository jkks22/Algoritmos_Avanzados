/*
? DESCRIPTION
Program that analyzes two data transmissions looking for malicious code.
It reads 5 fixed-name files and:
    - Part 1. Checks if each mcode is contained in each transmission 
    and reports the starting position.
    - Part 2. Finds the longest palindrome in each transmission and 
    reports its start and end positions.
    - Part 3. Finds the longest common substring between both transmissions
    and reports its start and end positions in transmission1.

? INPUT
None. The 5.txt files must exist in the same folder as the executable.

? OUTPUT
6 lines -> (true | false) if the file transmission1/2.txt contains the code 
    (sequence of chars) contained in the file mcode1/2/3.txt
2 lines -> startPosition endPosition (for transmission1/2.txt) 
1 line -> startPosition endPosition (for longest common substring between stream files) 

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "malicious_code.h"
#include "longest_palindrome.h"
#include "longest_substring.h"

using namespace std;

//Opens and reads the given .txt file and returns its content as a string
//  so it can be analyzed easily
string readFile(const string& n){
    ifstream file(n);  //open the given file

    string line;  //stores every line read
    string content = ""; //final string

    while(getline(file, line)){
        //appends each line read to the final string without the line break
        content += line; 
    }
    return content;
};

int main(){

    string transmission_1 = readFile("tran.txt");
    string transmission_2 = readFile("transmission2.txt");
    string mcode_1 = readFile("mcode1.txt");
    string mcode_2 = readFile("mcode2.txt");
    string mcode_3 = readFile("mcode3.txt");

    cout << "--- Part 1. mcode in transmissions: ---" << endl;
    mcode(transmission_1, mcode_1);
    mcode(transmission_1, mcode_2);
    mcode(transmission_1, mcode_3);
    mcode(transmission_2, mcode_1);
    mcode(transmission_2, mcode_2);
    mcode(transmission_2, mcode_3);
    cout << endl;

    cout << "--- Part 2. longest palindrome in both transmissions: ---" << endl;
    longestPalindrome(transmission_1);
    longestPalindrome(transmission_2);
    cout << endl;

    cout << "--- Part 3. longest substring between transmissions: ---" << endl;
    longestsub(transmission_1, transmission_2);
    cout << endl;

    return 0; 
};