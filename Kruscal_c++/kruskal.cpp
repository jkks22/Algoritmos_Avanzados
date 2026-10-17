#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

//? function to sort edges from smallest to biggest weight
bool byWeight(vector<int> a, vector<int> b) {
    return a[2] < b[2]; // a goes before b if it's lighter
}

int main() {
    fstream file("graph.txt"); // open and read the file
    if (!file) { // just making sure it actually opened
        cout << "Can't open graph.txt\n";
        return 1;
    }

    // set up a fresh vector and the variables we need
    vector<vector<int>> edges;
    int node1, node2, weight;

    while (file >> node1 >> node2 >> weight) { // read into the variables
        edges.push_back({node1, node2, weight});
    }
    file.close();

    // sort edges by weight
    sort(edges.begin(), edges.end(), byWeight);

    // hash table: which group each node belongs to
    // at the start every node is in its own group
    map<int, int> group;
    int nextGroup = 1;

    vector<vector<int>> selected;
    int totalWeight = 0;

    // go through every edge from cheapest to priciest
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int weight = edges[i][2];

        // if a node doesn't have a group yet, give it one
        if (group.count(a) == 0) group[a] = nextGroup++;
        if (group.count(b) == 0) group[b] = nextGroup++;

        // if they're already in the same group -> joining them would make a cycle -> skip it
        if (group[a] == group[b]) {
            cout << "Skipped [" << a << "," << b << "," << weight << "]  (already connected)\n";
            continue;
        }

        // otherwise, use the edge and merge both groups into one
        cout << "used       [" << a << "," << b << "," << weight << "]\n";
        selected.push_back(edges[i]);
        totalWeight += weight;

        // everyone in b's old group now belongs to a's group
        int oldGroup = group[b];
        int newGroup = group[a];
        for (auto& pair : group) {
            if (pair.second == oldGroup) {
                pair.second = newGroup;
            }
        }
    }

    // 5. print the final result
    cout << "\nSelected edges: ";
    for (int i = 0; i < selected.size(); i++) {
        cout << "\n" << "[" << selected[i][0] << ","
             << selected[i][1] << ","
             << selected[i][2] << "]";
        if (i + 1 < selected.size()) cout << ", ";
    }
    cout << "\n" << "Final weight: " << totalWeight << "\n";

    return 0;
}
