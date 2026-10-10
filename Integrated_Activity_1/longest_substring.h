/*
? PART 3. 
The program analyzes how similar the transmission files are, it 
should display the starting position and the ending position (starting at 1) 
of the first file where the longest common substring between both stream files is found.
*/

#ifndef longest_substring_H
#define longest_substring_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//^ Dynamic programming

void longestsub(const string& transmission1, const string& transmission2){
    int trans1_size = transmission1.size(); //rows of the table
    int trans2_size = transmission2.size(); //columns of the table

    //~ step 1: create two rows we'll compare 
    vector<int> prev(trans2_size + 1, 0); //starts as the extra row of zeros (0)
    vector<int> curr(trans2_size + 1, 0); //the row we are filling now (1)

    int longest = 0; //length of the longest common substring found so far
    int end_longest = 0; //position in transmission1 where it ends (starting at 1)

    //~ step 2: compare every char of transmission1 with every char of transmission2
    for(int i = 1; i <= trans1_size; i++){ //for every char in transmission1 (row)
        for(int j = 1; j <= trans2_size; j++){ //for every char in transmission2 (column)

            //~ step 3: check if both chars are equal
            //-1 because we have an extra column to check the first row
            if(transmission1[i - 1] == transmission2[j - 1]){ 
                curr[j] = prev[j - 1] + 1; //what the diagonal has plus 1 

                //~ step 4: check if its the longest one
                if(curr[j] > longest){ //if this match is longer than the old one, save it
                    longest = curr[j]; //new biggest size...
                    end_longest = i; //...and where it ends in transmission1
                }
            } else {
                curr[j] = 0; //chars are different, so the match is broken
            }
        }

        //~ step 5: swap the rows to overwrite the new ones
        swap(prev, curr); 
    }


    int start_longest = end_longest - longest + 1;

    cout << start_longest << " " << end_longest << endl;
}

#endif