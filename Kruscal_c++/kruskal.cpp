#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

//one edge of the graph: it connects "from" and "to" and costs "weight"
//kruskal only cares about these three numbers, so a small struct is enough
struct Edge {
    int from, to, weight;
};

//comparator used by sort() so the edges end up ordered from cheapest to most expensive
//this is the greedy part of kruskal, we always want the cheapest edge available first
bool byWeight(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
//step 1: read the graph from a text file
//each line in graph.txt is expected to be: from to weight
    fstream file("graph.txt");
    if (!file) {
        cout << "Could not open graph.txt\n";
        return 1;
    }

    vector<Edge> edges;
    int from, to, weight;
    while (file >> from >> to >> weight) {
        Edge e;
        e.from = from;
        e.to = to;
        e.weight = weight;
        edges.push_back(e);
    }
    file.close();

//step 2: sort all edges from cheapest to most expensive
    sort(edges.begin(), edges.end(), byWeight);

/*step 3: keep track of which "group" (connected component) each node belongs to
this is basically a poor-man's version of union find: instead of a proper
disjoint set structure with path compression, we just use a map<node, groupId>
it is less efficient, but it is easier to reason about and works fine for small graphs
a node that has not appeared yet simply has no entry in the map,
meaning it doesn't belong to any group yet */

    map<int, int> group;
    int nextGroupId = 1;

    vector<Edge> selectedEdges;
    int totalWeight = 0;

//step 4: go through every edge, from cheapest to most expensive,
//and decide whether to keep it or discard it
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i].from;
        int b = edges[i].to;
        int w = edges[i].weight;

//if a node shows up for the first time, give it a brand new group
        if (group.count(a) == 0) group[a] = nextGroupId++;
        if (group.count(b) == 0) group[b] = nextGroupId++;

//if both endpoints are already in the same group, it means there is
//already a path connecting them, adding this edge would just close
//a cycle without connecting anything new, so we discard it
        if (group[a] == group[b]) {
            cout << "Discarded  [" << a << "," << b << "," << w << "]  (already connected)\n";
            continue;
        }

//otherwise, the edge connects two different groups, so it is safe to use:
//it will connect two pieces of the graph that were separate and can never create a cycle
        cout << "Selected   [" << a << "," << b << "," << w << "]\n";
        selectedEdges.push_back(edges[i]);
        totalWeight += w;

//merge the two groups into one: every node that used to be in b's group
//now belongs to a's group, this is the expensive part of this simple
//approach: we scan the whole map, but it keeps the "who is connected
//to whom" information correct for the next edges
        int oldGroup = group[b];
        int newGroup = group[a];
        for (auto& node : group) {
            if (node.second == oldGroup) {
                node.second = newGroup;
            }
        }
    }

//step 5: print the final minimum spanning tree, the edges that we kept and its total weight
    cout << "\nSelected edges: ";
    for (int i = 0; i < selectedEdges.size(); i++) {
        cout << "[" << selectedEdges[i].from << ","
             << selectedEdges[i].to << ","
             << selectedEdges[i].weight << "]";
        if (i + 1 < selectedEdges.size()) cout << ", ";
    }
    cout << ". Final weight: " << totalWeight << "\n";

    return 0;
}
