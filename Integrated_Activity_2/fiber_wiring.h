/*
? PART 1.
Reads the graph of distances (km) between neighborhoods and displays the optimal
way to wire them with optical fiber, so information can be shared between any
two neighborhoods (list of arcs of the form (A,B)).
*/

#ifndef fiber_wiring_H
#define fiber_wiring_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//^ Kruskal algorithm

void fiberWiring(const vector<vector<int>>& distance){
    int n = distance.size();

    //~ step 1: save every edge as {weight, from, to}, only once because the graph is not directed
    vector<vector<int>> edges;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(distance[i][j] > 0){ //0 means there is no cable possible
                edges.push_back({distance[i][j], i, j});
            }
        }
    }

    //~ step 2: sort the edges from cheapest to priciest
    sort(edges.begin(), edges.end());

    //~ step 3: at the start every neighborhood is in its own group
    vector<int> group(n);
    for(int i = 0; i < n; i++){
        group[i] = i;
    }

    //~ step 4: take every edge that joins two different groups
    int totalKm = 0;
    for(int e = 0; e < edges.size(); e++){
        int weight = edges[e][0];
        int a = edges[e][1];
        int b = edges[e][2];

        if(group[a] == group[b]){ //already connected, the edge would make a cycle
            continue;
        }

        cout << "(" << char('A' + a) << "," << char('A' + b) << ")" << endl;
        totalKm += weight;

        int oldGroup = group[b]; //everyone in b's group now belongs to a's group
        for(int i = 0; i < n; i++){
            if(group[i] == oldGroup){
                group[i] = group[a];
            }
        }
    }

    cout << "Total fiber: " << totalKm << " km" << endl;
};
#endif
