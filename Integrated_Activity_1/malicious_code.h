/*
? PART 1. 
The program must analyze if the contents of the files mcode1.txt, mcode2.txt, 
and mcode3.txt are contained in the files transmission1.txt and transmission2.txt and 
display a true or false if the chars sequences are contained or not. If true, it displays true,
followed by exactly one space, followed by the position in the transmissionX.txt file where 
the mcodeY.txt code starts.

*/

#ifndef malicious_code_H  
#define malicious_code_H

#include <iostream>
#include <string>
using namespace std;

//^ KMP algorithm

void mcode(const string& transmissions, const string& pattern){
    int patternSize = pattern.size();
    int transmissionSize = transmission.size();

    //~ step 1: make the lps array to know how much of the pattern can be reused
    vector<int> lps(patternSize, 0);
    int len = 0;
    for(int k = 1; k < patternSize; k++){
        while(len > 0 && pattern[k] != pattern[len]){ //if there's a mismatch...
            len = lps[len - 1]; //...len goes back to check past chars
        }

        if(pattern[k] == pattern[len]){ //if current char match len char, prefix expand
            len++;
        }

        lps[k] = len;  //stores the value
    }

    //~ step 2: compare the pattern (mcode) with the transmission
    int j = 0; //number of mcode chars matched
    for(int i = 0; i < transmissionSize; i++){ //for every char in the transmission
        while(j > 0 && transmissions[i] != pattern[j]){ //mismatch after some chars of the pattern matched
            j = lps[j - 1]; //"backtrack" to the prefix of the char, i stays the same
        }

        if(transmissions[i] == pattern[j]){ //both chars match
            j++; //both j and i continue
        }

        if(j == patternSize){ //~ complete mcode found
            cout << "true " << i - patternSize + 2 << endl;
            return;
        }
    }

    cout << "false" << endl;  //~ mcode not found
};
#endif