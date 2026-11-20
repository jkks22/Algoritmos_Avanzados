/*
? PART 2.
Someone has to visit each neighborhood to drop off statements, advertisements and
notifications. The program displays the shortest route that visits each neighborhood
exactly once and returns to the neighborhood of origin (first city A, second B, ...).
*/

#ifndef delivery_route_H
#define delivery_route_H

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//^ Branch and bound

//calculates the minimum the whole route could cost if we keep the current path
int routeBound(int current, int currentCost, const vector<int>& minEdge, const vector<bool>& visited){
    int bound = currentCost + minEdge[current];
    for(int i = 0; i < visited.size(); i++){
        if(!visited[i]){
            bound += minEdge[i];
        }
    }
    return bound;
};

//checks every possible route, one city at a time, and keeps the shortest one
void searchRoute(const vector<vector<int>>& distance, const vector<int>& minEdge, vector<bool>& visited,
                 vector<int>& route, int currentCost, vector<int>& bestRoute, int& bestCost){
    int n = distance.size();
    int current = route.back();

    //~ step 3: all the cities were visited, go back to the start
    if(route.size() == n){
        if(distance[current][0] > 0 && currentCost + distance[current][0] < bestCost){
            bestCost = currentCost + distance[current][0];
            bestRoute = route;
        }
        return;
    }

    //~ step 4: branch, try every city that is not visited yet
    for(int next = 0; next < n; next++){
        if(visited[next] || distance[current][next] == 0){ //visited or no road
            continue;
        }
        int newCost = currentCost + distance[current][next];

        visited[next] = true;
        route.push_back(next);

        //~ step 5: bound, only continue if this branch can still beat the best route
        if(routeBound(next, newCost, minEdge, visited) < bestCost){
            searchRoute(distance, minEdge, visited, route, newCost, bestRoute, bestCost);
        }

        //~ step 6: backtracking, undo the move
        visited[next] = false;
        route.pop_back();
    }
}

//finds the route and prints it
void deliveryRoute(const vector<vector<int>>& distance){
    int n = distance.size();

    //~ step 1: cheapest edge that leaves each city (used by the bound)
    vector<int> minEdge(n, 0);
    for(int i = 0; i < n; i++){
        int cheapest = INT_MAX;
        for(int j = 0; j < n; j++){
            if (i != j && distance[i][j] > 0 && distance[i][j] < cheapest){ //skip diagonal, distance = 0, lower distance
                cheapest = distance[i][j];
            }
        }
        if (cheapest != INT_MAX){
            minEdge[i] = cheapest;
        }
    }

    //~ step 2: start in A
    vector<bool> visited(n, false);
    visited[0] = true;
    vector<int> route = {0};
    vector<int> bestRoute;
    int bestCost = INT_MAX;
    searchRoute(distance, minEdge, visited, route, 0, bestRoute, bestCost);

    //~ step 7: print the route and its cost
    if(bestRoute.empty()){
        cout << "There is no route that visits every neighborhood once" << endl;
        return;
    }
    for(int i = 0; i < bestRoute.size(); i++){
        cout << char('A' + bestRoute[i]) << " -> ";
    }
    cout << "A" << endl;
    cout << "Total distance: " << bestCost << " km" << endl;
}
#endif
