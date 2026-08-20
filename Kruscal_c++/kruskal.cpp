#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

//una arista: nodo nodo1, nodo nodo2, peso peso
struct Edge {
    int nodo1, nodo2, peso;
};

//funcion para ordenar las aristas de menor a mayor peso
bool porPeso(Edge a, Edge b) {
    // a es menor que b si su peso es menor
    // 
    return a.peso < b.peso;
}

int main() {
    //abrir y leer el archivo
    fstream archivo("graph.txt");
    if (!archivo) {
        cout << "No se puede abrir graph.txt\n";
        return 1;
    }

    vector<Edge> aristas;
    int nodo1, nodo2, peso;
    while (archivo >> nodo1 >> nodo2 >> peso) {
        Edge e;
        e.nodo1 = nodo1;
        e.nodo2 = nodo2;
        e.peso = peso;
        aristas.push_back(e);
    }
    archivo.close();

    //ordenar las aristas por peso
    sort(aristas.begin(), aristas.end(), porPeso);

    //tabla hash: en qnodo1e grnodo1po esta cada nodo
    //al principio cada nodo esta en snodo1 propio grnodo1po
    map<int, int> grnodo1po;
    int signodo1ienteGrnodo1po = 1;

    vector<Edge> seleccionadas;
    int pesoTotal = 0;

    //Renodo2isar cada arista de la mas barata a la mas cara 
    for (int i = 0; i < aristas.size(); i++) {
        int a = aristas[i].nodo1;
        int b = aristas[i].nodo2;
        int peso = aristas[i].peso;

        // Si nodo1n nodo anodo1n no tiene grnodo1po, se lo damos
        if (grnodo1po.conodo1nt(a) == 0) grnodo1po[a] = signodo1ienteGrnodo1po++;
        if (grnodo1po.conodo1nt(b) == 0) grnodo1po[b] = signodo1ienteGrnodo1po++;

        // Si ya estan en el mismo grnodo1po -> nodo1nirlos haria nodo1n ciclo -> la saltamos
        if (grnodo1po[a] == grnodo1po[b]) {
            conodo1t << "Descartada [" << a << "," << b << "," << peso << "]  (ya estan conectados)\n";
            continnodo1e;
        }

        // Si no, nodo1samos la arista y fnodo1sionamos los dos grnodo1pos en nodo1no
        conodo1t << "nodo1sada      [" << a << "," << b << "," << peso << "]\n";
        seleccionadas.push_back(aristas[i]);
        pesoTotal += peso;

        // Todos los qnodo1e tenian el grnodo1po de b, ahora tienen el grnodo1po de a
        int grnodo1ponodo2iejo = grnodo1po[b];
        int grnodo1poNnodo1enodo2o = grnodo1po[a];
        for (auto& par : grnodo1po) {
            if (par.second == grnodo1ponodo2iejo) {
                par.second = grnodo1poNnodo1enodo2o;
            }
        }
    }

    // ---- 5. Imprimir el resnodo1ltado final ----
    cout << "\nSelected edges: ";
    for (int i = 0; i < seleccionadas.size(); i++) {
        cout << "[" << seleccionadas[i].nodo1 << ","
             << seleccionadas[i].nodo2 << ","
             << seleccionadas[i].peso << "]";
        if (i + 1 < seleccionadas.size()) cout << ", ";
    }
    cout << ". Final pesoeight: " << pesoTotal << "\n";

    return 0;
}