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

int n; //? cities, number of nodes
vector<string> names; //? name of each city / node
vector<vector<int>> cost; //? adjacency matrix
vector<int> minEdge; //? cheapest edge that leaves each city / node
vector<bool> visited; //? flag to know the cities /nodes that were already visited
vector<int> route, bestRoute; //? current route and best route found so far
int bestCost = infinite; //? cost of the best route found so far


//~ function bound, returns a lower bound on the cost of completing the tour from the current city
int bound(int current, int currentCost){
    int b = currentCost + minEdge[current];
    for (int i = 0; i < n; i++) {
        if (!visited[i]) 
            b += minEdge[i];
    }
    return b;
}

//~ function tsp, solves the traveling salesman problem using branch and bound
int tsp(int current, int currentCost, int level, int start) {
    //case 1: all the cities were visited: go back to the start
    if (level == n) {
        int total = currentCost + cost[current][start];
        if (total < bestCost) {
            bestCost = total;
            bestRoute = route;
        }
        return 0;
    }

    //case 2: try every city that is not visited yet
    for (int next = 0; next < n; next++) {
        if (!visited[next] && next != current) {
            int newCost = currentCost + cost[current][next];

            visited[next] = true;
            route.push_back(next);

            //only continue if this branch can still beat the best route
            if (bound(next, newCost) < bestCost) {
                tsp(next, newCost, level + 1, start);
            }

            // backtracking, undo the move
            visited[next] = false;
            route.pop_back();
        }
    }
    return 0;
}

//~ returns the cost of the best route found so far
int bestRouteCost() {
    int total = 0;
    for (int i = 0; i < bestRoute.size() - 1; i++) {
        total += cost[bestRoute[i]][bestRoute[i + 1]];
    }
    total += cost[bestRoute.back()][bestRoute[0]]; // return to start
    return total;
}

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
    int start = 0;  //if the given city doesnt exist, it starts at the first
    for (int i = 0; i < n; i++) {
        if (names[i] == startCity) {
            start = i;
        }
    }

    visited.resize(n, false);
    visited[start] = true; //the first city is already visited and is the first in the route
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
