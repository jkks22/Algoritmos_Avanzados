#include <iostream>
#include <vector>
using namespace std;

int main() {
    //! step 1: problem data (position 0 is not used)
    int W = 8; //? knapsack capacity
    vector<int> v = {0, 2, 4, 7, 10};   //? values
    vector<int> w = {0, 1, 3, 5, 7};    //? weights
    int n = v.size() - 1;               //? number of items

    //! step 2: create the table A[i][x] filled with zeros
    vector<vector<int>> A(n + 1, vector<int>(W + 1, 0));

    //! step 3: fill the table
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= W; x++) {
            A[i][x] = A[i - 1][x];                    //? do not take item i
            if (w[i] <= x && A[i - 1][x - w[i]] + v[i] > A[i][x]) {
                A[i][x] = A[i - 1][x - w[i]] + v[i];  //? take item i
            }
        }
    }

    //! step 4: print the max value
    cout << "Max value: " << A[n][W] << "\n";

    //! step 5: go back to find which items were taken
    int x = W;
    cout << "Items: ";
    for (int i = n; i >= 1; i--) {
        if (A[i][x] != A[i - 1][x]) {   //? the value changed: item i was taken
            cout << i << " ";
            x = x - w[i];
        }
    }
    cout << "\n";
    return 0;
}