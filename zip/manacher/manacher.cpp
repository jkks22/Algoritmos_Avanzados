//Manacher pseudo code
/*  
function (main string):
    max counter = 0
    L = array[] 
    length of main string
    new string = $ + i of main string + $
    variable pointer = 0
    mirror = pointer - 1
    for i = 1 to length of new string - 1:
        if mirror = i:
            counter++
            mirror--
            i++
            else:
            L.push(counter)
            if counter > max counter:
                max counter = counter
                start = ceil( (maxIndex - maxLen) / 2 )
                end   = start + maxLen - 1
                new array = main string[start:end]
            pointer++
            mirror = pointer - 1
            i = pointer + 1
    return L
    return new array

    */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//? returns the longest palindrome inside the main string
string manacher(const string& mainString) {
    //! step 1: new string with $ between each char, so even and odd palindromes are the same case
    string newString = "$";
    for (char c : mainString) {
        newString += c;
        newString += '$';
    }
    int n = newString.size();

    //! step 2: L[i] = radius of the longest palindrome centered on i
    vector<int> L(n, 0);
    int center = 0, right = 0;  //? palindrome that reaches the furthest to the right
    int maxLen = 0, maxIndex = 0; //? longest palindrome found so far

    for (int i = 0; i < n; i++) {
        //! step 3: reuse the value of the mirror inside the big palindrome
        int mirror = 2 * center - i;
        if (i < right) L[i] = min(L[mirror], right - i);

        //! step 4: expand to both sides
        while (i - L[i] - 1 >= 0 && i + L[i] + 1 < n && newString[i - L[i] - 1] == newString[i + L[i] + 1]) {
            L[i]++;
        }

        //! step 5: this palindrome goes further to the right, it becomes the new big one
        if (i + L[i] > right) {
            center = i;
            right = i + L[i];
        }
        if (L[i] > maxLen) {
            maxLen = L[i];
            maxIndex = i;
        }
    }

    //! step 6: convert the position in the new string to the main string
    return mainString.substr((maxIndex - maxLen) / 2, maxLen);
}

int main() {
    string mainString;
    cout << "Enter the main string: ";
    cin >> mainString;

    string palindrome = manacher(mainString);
    cout << "Longest palindrome: " << palindrome << " (length " << palindrome.size() << ")\n";
    return 0;
}
