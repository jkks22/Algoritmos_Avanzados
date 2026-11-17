/*
? PART 3.
Reads a second N x N matrix with the maximum data transmission capacity between
neighborhood i and neighborhood j and displays the maximum information flow
from the initial node to the final node.
*/

#ifndef max_flow_H
#define max_flow_H

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

//^ Ford-Fulkerson with BFS (Edmonds-Karp)

void maxFlow(const vector<vector<int>>& capacity){
    int n = capacity.size();
    int source = 0;    //initial node
    int sink = n - 1;  //final node

    //~ step 1: the residual graph starts as a copy of the capacities
    vector<vector<int>> residual = capacity;
    int totalFlow = 0;

    while(true){
        //~ step 2: BFS to find the shortest path from source to sink with capacity left
        vector<int> parent(n, -1);
        parent[source] = source;
        queue<int> q;
        q.push(source);
        while(!q.empty() && parent[sink] == -1){
            int u = q.front();
            q.pop();
            for(int v = 0; v < n; v++){
                if(parent[v] == -1 && residual[u][v] > 0){
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if(parent[sink] == -1){ //no more paths, the flow is the maximum
            break;
        }

        //~ step 3: the flow of the path is its smallest capacity (bottleneck)
        int pathFlow = INT_MAX;
        for(int v = sink; v != source; v = parent[v]){
            pathFlow = min(pathFlow, residual[parent[v]][v]);
        }

        //~ step 4: update the residual graph, the reverse edge lets us undo flow later
        for(int v = sink; v != source; v = parent[v]){
            residual[parent[v]][v] -= pathFlow;
            residual[v][parent[v]] += pathFlow;
        }
        totalFlow += pathFlow;
    }

    cout << "Max flow from " << char('A' + source) << " to " << char('A' + sink) << ": " << totalFlow << endl;
};
#endif
