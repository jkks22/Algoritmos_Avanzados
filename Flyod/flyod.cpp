#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 1000000000; //? infinity: there is no edge

int main() {
    //! step 1: open and read the file
    //? each line in graph.txt is: node1 node2 weight
    ifstream file("graph.txt");
    vector<int> n1, n2, weight;
    int a, b, w, n = 0;
    while (file >> a >> b >> w) {
        n1.push_back(a);
        n2.push_back(b);
        weight.push_back(w);
        if (a + 1 > n) n = a + 1;
        if (b + 1 > n) n = b + 1;
    }
    file.close();

    //! step 2: build the matrix: 0 on the diagonal, INF where there is no edge
    vector<vector<int>> A(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) A[i][i] = 0;
    for (int i = 0; i < n1.size(); i++) {
        A[n1[i]][n2[i]] = weight[i];
        A[n2[i]][n1[i]] = weight[i]; //? remove this line if the graph is directed
    }

    //! step 3: try going through every node k
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //? A[i][j] = min(A[i][j], A[i][k] + A[k][j])
                if (A[i][k] != INF && A[k][j] != INF && A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }

    //! step 4: print the final matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INF) cout << "INF\t";
            else cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
    return 0;
}