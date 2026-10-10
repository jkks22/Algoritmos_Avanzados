/*
? PART 2.
Assuming that malicious code always has "mirrored" code 
(chars palindromes), it would be a good idea to look for this type of code 
in a transmission. The program should then look for "mirrored" code within 
the transmission files (only at chars level, do not look for it at bits level). 
The program displays in a single line (two integers separated by a space) the position 
(starting at 1) where the longest "mirrored" code (palindrome) for each stream file 
starts and ends. It can be assumed that this type of code will always be found.
*/

#ifndef longest_palindrome_H
#define longest_palindrome_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//^ Manacher algorithm

void longestPalindrome(const string& transmission) {
    int transmissionLength = transmission.length();

    //~ step 1: create the new string with a special char between each char
    string newString = "$";
    for (int i = 0; i < transmissionLength; i++) { //for every char in the given string
        newString += transmission[i]; //add it into the new string ...
        newString += '$';  //... then add the special char
    }

    int newString_Length = newString.length();
    //~ step 2: create L-array where L[i] stores the lenght of the longest palindrome
    vector<int> L(newString_Length, 0); //all start at 0 because we have not checked anything yet

    //center = the middle of the palindrome that reaches the furthest to the right. 
    //right = the last position it covers
    //maxLen = size of the biggest palindrome found so far
    //maxIndex = the middle  of the longest palindrome found.
    int center = 0, right = 0, maxLen = 0, maxIndex = 0;

    for (int i = 0; i < newString_Length; i++) {  //for every position in the new string
        int mirror = center - (i - center);

        //~ step 3: check if we know the length by the "mirror"
        if (i < right) { //only if i is still inside the big palindrome
            L[i] = L[mirror]; //copy what its mirror already has
            if (i + L[i] > right) { //but if that goes past what we have already checked...
                L[i] = right - i;   //...we cut it so it only reaches right
            }
        }

        //~ step 4: expand to both sides "<- center ->"
        int nextLeft = i - L[i] - 1; //next char to the left
        int nextRight = i + L[i] + 1; //next char to the right
        while (nextLeft >= 0 && nextRight < newString_Length //its still instide de new string...
            && newString[nextLeft] == newString[nextRight]) { //... and both chars are the same
            L[i]++; //they are equal, so the palindrome grows one more
            nextLeft--; //move one to the left
            nextRight++; //move one to the right
        }

        //~ step 5: if this palindrome goes further to the right than the old one, it becomes the new big one
        if (i + L[i] > right) { 
            center = i;         //its middle is the new center...
            right = i + L[i];   //...and this is the new last position it covers
        }

        //~ step 6:save the longest one 
        if (L[i] > maxLen) {
            maxLen = L[i]; //new biggest size ...
            maxIndex = i; //..and where its middle is
        }
    }

    //~ step 7: convert the position in the new string to the given string
    int start = (maxIndex - maxLen) / 2; 
    int end = start + maxLen; 

    cout << start + 1 << " " << end << endl;
};

#endif
