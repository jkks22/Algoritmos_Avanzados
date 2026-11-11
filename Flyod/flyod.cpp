#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int INF = 1000000000; //"infinito": no hay arista

int main() {
    //1. abrir y leer el archivo (cada linea: nodo1 nodo2 peso)
    ifstream file("graph.txt");
    vector<int> n1, n2, peso;
    int a, b, w, n = 0;
    while (file >> a >> b >> w) {
        n1.push_back(a);
        n2.push_back(b);
        peso.push_back(w);
        if (a + 1 > n) n = a + 1;
        if (b + 1 > n) n = b + 1;
    }
    file.close();

    //2. crear la matriz: 0 en la diagonal, INF donde no hay arista
    vector<vector<int>> A(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) A[i][i] = 0;
    for (int i = 0; i < n1.size(); i++) {
        A[n1[i]][n2[i]] = peso[i];
        A[n2[i]][n1[i]] = peso[i]; //quitar esta linea si el grafo es dirigido
    }

    //3. probar pasar por cada nodo k
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //A[i][j] = min(A[i][j], A[i][k] + A[k][j])
                if (A[i][k] != INF && A[k][j] != INF && A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }

    //4. mostrar la matriz final
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INF) cout << "INF\t";
            else cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
    return 0;
}