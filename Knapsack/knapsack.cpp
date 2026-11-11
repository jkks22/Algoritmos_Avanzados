#include <iostream>
#include <vector>
using namespace std;

int main() {
    //! 1. datos del problema (posicion 0 no se usa)
    int W = 8; //capacidad de la mochila
    vector<int> v = {0, 2, 4, 7, 10};   //valores
    vector<int> w = {0, 1, 3, 5, 7};    //pesos
    int n = v.size() - 1;               //numero de objetos

    //2. crear la tabla A[i][x] llena de ceros
    vector<vector<int>> A(n + 1, vector<int>(W + 1, 0));

    //3. llenar la tabla
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= W; x++) {
            A[i][x] = A[i - 1][x];                    //no tomar el objeto i
            if (w[i] <= x && A[i - 1][x - w[i]] + v[i] > A[i][x]) {
                A[i][x] = A[i - 1][x - w[i]] + v[i];  //tomar el objeto i
            }
        }
    }

    //4. mostrar el valor maximo
    cout << "Valor maximo: " << A[n][W] << "\n";

    //5. regresar para saber que objetos se tomaron
    int x = W;
    cout << "Objetos: ";
    for (int i = n; i >= 1; i--) {
        if (A[i][x] != A[i - 1][x]) {   //cambio el valor: se tomo el objeto i
            cout << i << " ";
            x = x - w[i];
        }
    }
    cout << "\n";
    return 0;
}