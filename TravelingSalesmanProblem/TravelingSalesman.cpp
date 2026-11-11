#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int INF = 1000000000;

int n;                        //number of cities
vector<string> names;         //name of each city
vector<vector<int>> cost;     //adjacency matrix
vector<int> minEdge;          //cheapest edge that leaves each city

vector<bool> visited;
vector<int> route, bestRoute;
int bestCost = INF;

//lower bound: what we already paid + the cheapest way to leave
//the current city and every city that is still not visited
int bound(int current, int currentCost) {
    int b = currentCost + minEdge[current];
    for (int i = 0; i < n; i++) {
        if (!visited[i]) b += minEdge[i];
    }
    return b;
}

void tsp(int current, int currentCost, int level, int start) {
    //all the cities were visited: go back to the start
    if (level == n) {
        int total = currentCost + cost[current][start];
        if (total < bestCost) {
            bestCost = total;
            bestRoute = route;
        }
        return;
    }

    //branch: try every city that is not visited yet
    for (int next = 0; next < n; next++) {
        if (!visited[next] && next != current) {
            int newCost = currentCost + cost[current][next];

            visited[next] = true;
            route.push_back(next);

            //bound: only continue if this branch can still beat the best route
            if (bound(next, newCost) < bestCost) {
                tsp(next, newCost, level + 1, start);
            }

            //backtracking: undo the move
            visited[next] = false;
            route.pop_back();
        }
    }
}

int main() {
    //1. read the matrix
    ifstream file("matrix.txt");
    if (!file) {
        cout << "Could not open matrix.txt\n";
        return 1;
    }
    file >> n;
    names.resize(n);
    for (int i = 0; i < n; i++) file >> names[i];
    cost.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> cost[i][j];
    file.close();

    //2. cheapest edge that leaves each city (used by the bound)
    minEdge.assign(n, INF);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && cost[i][j] < minEdge[i]) minEdge[i] = cost[i][j];

    //3. ask for the start city
    string startName;
    cout << "Start city: ";
    cin >> startName;
    int start = -1;
    for (int i = 0; i < n; i++)
        if (names[i] == startName) start = i;
    if (start == -1) {
        cout << "That city is not in the matrix\n";
        return 1;
    }

    //4. solve
    visited.assign(n, false);
    visited[start] = true;
    route.push_back(start);
    tsp(start, 0, 1, start);

    //5. print the route and its cost
    cout << "Route: ";
    for (int i = 0; i < bestRoute.size(); i++) cout << names[bestRoute[i]] << " > ";
    cout << names[start] << "\n";
    cout << "Total cost: " << bestCost << "\n";
    return 0;
}