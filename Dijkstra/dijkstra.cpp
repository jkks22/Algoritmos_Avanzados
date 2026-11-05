#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 1000000000; //? infinity

//? prints the path from the start node to "node" following the previous[] array
void printPath(vector<int>& previous, int node) {
    if (previous[node] != -1) {
        printPath(previous, previous[node]); //? first print how we got to the previous node
        cout << " -> ";
    }
    cout << node;
}

int main() {
    //! step 1: read the graph from a text file
    //? each line in graph.txt is: from to weight
    ifstream file("graph.txt");
    if (!file) {
        cout << "Could not open graph.txt\n";
        return 1;
    }

    //! step 2: save all the edges in three vectors (same position = same edge)
    vector<int> fromList, toList, weightList;
    int from, to, weight;
    int n = 0; //? number of nodes, biggest node + 1
    while (file >> from >> to >> weight) {
        fromList.push_back(from);
        toList.push_back(to);
        weightList.push_back(weight);
        if (from + 1 > n) n = from + 1;
        if (to + 1 > n) n = to + 1;
    }
    file.close();

    //! step 3: build the adjacency matrix: graph[i][j] = weight between i and j (0 = no edge)
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < fromList.size(); i++) {
        graph[fromList[i]][toList[i]] = weightList[i];
        graph[toList[i]][fromList[i]] = weightList[i]; //? not directed: both ways
    }

    //! step 3: prepare the arrays
    int start;
    cout << "Start node: ";
    cin >> start;

    vector<int> distance(n, INF);     //? best distance found from start to each node
    vector<bool> visited(n, false);   //? if the node is already final
    vector<int> previous(n, -1);      //? from which node we arrive (to build the path)
    distance[start] = 0;

    //! step 4: repeat until all the nodes are visited
    for (int step = 1; step <= n; step++) {

        //! step 5: select the not visited node with the minimum distance
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (current == -1 || distance[i] < distance[current])) {
                current = i;
            }
        }

        //? if the minimum is infinity, the rest of the nodes can not be reached
        if (distance[current] == INF) break;

        visited[current] = true;
        cout << "Step " << step << ": visit node " << current
             << " (distance " << distance[current] << ")\n";

        //! step 6: update the distance of the neighbors of current
        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (graph[current][neighbor] != 0 && !visited[neighbor] &&
                distance[current] + graph[current][neighbor] < distance[neighbor]) {
                distance[neighbor] = distance[current] + graph[current][neighbor];
                previous[neighbor] = current;
            }
        }
    }

    //! step 7: print the result
    cout << "\nNode\tDistance\tPath\n";
    for (int i = 0; i < n; i++) {
        cout << i << "\t";
        if (distance[i] == INF) {
            cout << "INF\t\tno path\n";
        } else {
            cout << distance[i] << "\t\t";
            printPath(previous, i);
            cout << "\n";
        }
    }

    return 0;
}