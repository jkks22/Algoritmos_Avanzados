#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//? prints every subset of w that adds up exactly to target
void sumSubsets(vector<int>& w, int target, int i, int sum, int remaining, vector<int>& subset) {
    //! base case: the subset reached the target
    if (sum == target) {
        cout << "{ ";
        for (int x : subset) cout << x << " ";
        cout << "}\n";
        return;
    }

    //! bound: no more numbers, or even taking all the rest we can't reach the target
    if (i == w.size() || sum + remaining < target) return;

    //! branch 1: take w[i], only if it does not go over the target (w is sorted, so the rest won't fit either)
    if (sum + w[i] <= target) {
        subset.push_back(w[i]);
        sumSubsets(w, target, i + 1, sum + w[i], remaining - w[i], subset);
        subset.pop_back(); //? backtracking, undo the move
    }

    //! branch 2: do not take w[i]
    sumSubsets(w, target, i + 1, sum, remaining - w[i], subset);
}

int main() {
    //! step 1: problem data
    vector<int> w = {5, 10, 12, 13, 15, 18}; //? set of numbers
    int target = 30;                         //? sum we are looking for

    //! step 2: sort so we can stop when a number does not fit
    sort(w.begin(), w.end());
    int total = 0;
    for (int x : w) total += x;

    //! step 3: solve
    vector<int> subset;
    cout << "Subsets that add up to " << target << ":\n";
    sumSubsets(w, target, 0, 0, total, subset);
    return 0;
}
