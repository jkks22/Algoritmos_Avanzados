/*
& Change history:
Created by: Daniela Angulo on October 4th, 2026

? PART 2. 
Assuming that malicious code always has "mirrored" code (chars palindromes), 
it would be a good idea to look for this type of code in a transmission. The program 
should then look for "mirrored" code within the transmission files (only at chars level, 
do not look for it at bits level). The program displays in a single line (two integers 
separated by a space) the position (starting at 1) where the longest "mirrored" code 
(palindrome) for each stream file starts and ends. It can be assumed that this type of code 
will always be found.
*/

#ifndef longest_palindrome_H  
#define longest_palindrome_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//returns {startPosition, endPosition} (starting at 1) of the longest palindrome in s
//if there are two palindromes with the same length, the first one is returned
pair<int, int> longestPalindrome(const string& s) {
    int n = s.length();
    if (n == 0) return {0, 0};

    //step 1: create the new string with a special char between each char
    //ex: ABBA -> $A$B$B$A$
    //this way even and odd palindromes are handled the same way
    string t = "$";
    for (int i = 0; i < n; i++) {
        t += s[i];
        t += '$';
    }
    int m = t.length();

    //L[i] = length of the palindrome centered at i (in the original string)
    vector<int> L(m, 0);

    //center and right border of the palindrome that reaches the furthest to the right
    int center = 0, right = 0;
    int maxLen = 0, maxIndex = 0;

    for (int i = 0; i < m; i++) {
        //step 2: if i is inside a known palindrome, use its mirror
        //so we do not compare the same chars again
        int mirror = 2 * center - i;
        if (i < right) {
            L[i] = min(right - i, L[mirror]);
        }

        //step 3: expand to both sides while it is still a mirror
        while (i - L[i] - 1 >= 0 && i + L[i] + 1 < m &&
               t[i - L[i] - 1] == t[i + L[i] + 1]) {
            L[i]++;
        }

        //step 4: if this palindrome goes further to the right, it becomes the new center
        if (i + L[i] > right) {
            center = i;
            right = i + L[i];
        }

        //save the longest one (strict > keeps the first one in case of a tie)
        if (L[i] > maxLen) {
            maxLen = L[i];
            maxIndex = i;
        }
    }

    //step 5: convert the position in the new string to the original string
    int start = (maxIndex - maxLen) / 2;   //starting at 0
    return {start + 1, start + maxLen};     //starting at 1
}

#endif



#endif