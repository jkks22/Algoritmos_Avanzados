/*
Traveling Salesman Problem
- Input: An N x N adjacency matrix, where N is the number of cities to visit.
- Output: The route to be taken and its total cost.

Team: Daniela Angulo, Uriel Anzures, Josue Gomez
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int infinite = 1000000000;

int n; //? cities
vector<string> names; //? name of each city
vector<vector<int>> cost; //? adjacency matrix
vector<int> minEdge; //? cheapest edge that leaves each city
vector<bool> visited; //? flag to know the cities that were already visited
vector<int> route, bestRoute; //? current route and best route found so far
int bestCost = infinite; //? cost of the best route found so far

//header with the functions
#include "tsp.h"

int main() {
    //~ open the file with the matrix
    ifstream file("matrix.txt");

    //~ read the number of cities
    file >> n;

    //~ read the names of the cities
    names.resize(n); //make space for n names
    for (int i = 0; i < n; i++) {
        file >> names[i];
    }

    //~ read the adjacency matrix
    cost.resize(n, vector<int>(n)); //make an n x n matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> cost[i][j];
        }
    }

    //~ cheapest edge that leaves each city
    minEdge.resize(n, infinite);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && cost[i][j] < minEdge[i]) {
                minEdge[i] = cost[i][j];
            }
        }
    }

    //~ ask for the starting city
    string startCity;
    cout << "Enter the starting city: ";
    cin >> startCity;

    //~ find the index of that city
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (names[i] == startCity) {
            start = i;
        }
    }

    //~ the starting city is already visited and is the first in the route
    visited.resize(n, false);
    visited[start] = true;
    route.push_back(start);

    //~ solve
    tsp(start, 0, 1, start);

    //~ print the route and its total cost
    cout << "Route: ";
    for (int i = 0; i < bestRoute.size(); i++) {
        cout << names[bestRoute[i]] << " -> ";
    }
    cout << names[start] << endl;
    cout << "Total cost: " << bestCost << endl;

    return 0;
}