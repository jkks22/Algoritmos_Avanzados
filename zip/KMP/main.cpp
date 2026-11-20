/*
? KMP algorithm
Searches a pattern inside a text and displays true followed by the position
(starting at 1) where the pattern starts, or false if it is not in the text.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void kmp(const string& text, const string& pattern){
    int patternSize = pattern.size();
    int textSize = text.size();

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

    //~ step 2: compare the pattern with the text
    int j = 0; //number of pattern chars matched
    for(int i = 0; i < textSize; i++){ //for every char in the text
        while(j > 0 && text[i] != pattern[j]){ //mismatch after some chars of the pattern matched
            j = lps[j - 1]; //"backtrack" to the prefix of the char, i stays the same
        }

        if(text[i] == pattern[j]){ //both chars match
            j++; //both j and i continue
        }

        if(j == patternSize){ //~ complete pattern found
            cout << "true " << i - patternSize + 2 << endl;
            return;
        }
    }

    cout << "false" << endl;  //~ pattern not found
};

int main(){
    string text = "abxabcabcaby";

    kmp(text, "abcaby"); //true 7
    kmp(text, "abd");    //false

    return 0;
};
