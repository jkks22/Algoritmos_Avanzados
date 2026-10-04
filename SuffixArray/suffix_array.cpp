/* Pseudocode for Suffix Array  

null char = $
vector array = []
new string = main string + null char
for i = 0 to length of new string:
    push.back(i of new string)
sort vector array

for int i = 0; i < array.size(); i++:
    print vector array[i] and length of main string - length of vector array[i] + 1

https://www.geeksforgeeks.org/cpp/cpp-program-to-implement-suffix-array/
we consult this link to understand if our substraction is correct or not
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

char null_char = '$';

void buildSuffixArray(string main_string) {
    //add null char to the end of the main string
    string new_string = main_string + null_char; 
    vector<string> array;
    for (int i = 0; i < new_string.length(); i++) {
        //push the suffixes into the array
        array.push_back(new_string.substr(i));
    }
    sort(array.begin(), array.end());
    
    for (int i = 0; i < array.size(); i++) {
        string suffix = array[i];
        //print the suffix and its position in the original string
        cout << suffix << " " << new_string.length() - suffix.length() + 1 <<endl;

    }
}


int main(){
    string main_string;
    cout << "Enter the main string: ";
    cin >> main_string;
    
    buildSuffixArray(main_string);
    
    return 0;
}

