#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "bestRoute.h"
#include "bound.h"
#include "tsp.h"
using namespace std;

const int infinite = 1000000000;

int n; //? cities
vector<string> names; //? name of each city
vector<vector<int>> cost; //? adjacency matrix
vector<int> minEdge; //? cheapest edge that leaves each city
vector<bool> visited; //? cities that were already visited
vector<int> route, bestRoute; //? current route and best route found so far
int bestCost = infinite; //? cost of the best route found so far



int main() {
    fstream file("matrix.txt");
    if (!file) {
        cout << "Can't open matrix.txt\n";
        return 1;
    }
    return 0;

    string startcity;
    cout << "Enter the starting city: ";
    cin >> startcity;
     
}