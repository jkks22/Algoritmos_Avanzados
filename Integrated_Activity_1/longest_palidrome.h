/*
& Change history:
Created by: Daniela Angulo on October 4th, 2026
Modified by: Josue Gomez on October 6th, 2026
Added longestPalindrome(string s) using the Manacher algorithm
Returns a vector {start, end} with positions starting at 1

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
#include <string>

using namespace std;

//returns a vector with 2 numbers: {start, end} starting at 1
vector<int> longestPalindrome(string s) {
    //new string with $ between each char
    //ABBA = $A$B$B$A$
    string t = "$";
    for (int i = 0; i < s.length(); i++) {
        t = t + s[i] + "$";
    }

    int n = t.length();
    vector<int> L(n, 0);

    int center = 0;
    int right = 0;
    int maxLen = 0;
    int maxIndex = 0;

    for (int i = 0; i < n; i++) {

        //if i is inside a palindrome we already found, copy the value of its mirror
        if (i < right) {
            int mirror = 2 * center - i;
            L[i] = right - i;
            if (L[mirror] < L[i]) {
                L[i] = L[mirror];
            }
        }

        //expand to the left and to the right while the chars are the same
        int left = i - L[i] - 1;
        int rightSide = i + L[i] + 1;
        while (left >= 0 && rightSide < n && t[left] == t[rightSide]) {
            L[i]++;
            left--;
            rightSide++;
        }

        //if this palindrome goes further to the right, it is the new center
        if (i + L[i] > right) {
            center = i;
            right = i + L[i];
        }

        //save the longest palindrome
        if (L[i] > maxLen) {
            maxLen = L[i];
            maxIndex = i;
        }
    }

    //convert to the positions of the original string (starting at 1)
    int start = (maxIndex - maxLen) / 2 + 1;
    int end = start + maxLen - 1;

    vector<int> result = {start, end};
    return result;
}

#endif