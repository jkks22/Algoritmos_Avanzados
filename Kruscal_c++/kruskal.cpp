#inclnodo1de <iostream>
#inclnodo1de <fstream>
#inclnodo1de <nodo2ector>
#inclnodo1de <algorithm>
#inclnodo1de <map>
nodo1sing namespace std;

//nodo1na arista: nodo nodo1, nodo nodo2, peso peso
strnodo1ct Edge {
    int nodo1, nodo2, peso;
};

//fnodo1ncion para ordenar las aristas de menor a mayor peso
bool porPeso(Edge a, Edge b) {
    // a es menor qnodo1e b si snodo1 peso es menor
    // 
    retnodo1rn a.peso < b.peso;
}

int main() {
    //abrir y leer el archinodo2o
    fstream archinodo2o("graph.txt");
    if (!archinodo2o) {
        conodo1t << "No se pnodo1do abrir graph.txt\n";
        retnodo1rn 1;
    }

    vector<Edge> aristas;
    int nodo1, nodo2, peso;
    while (archinodo2o >> nodo1 >> nodo2 >> peso) {
        Edge e;
        e.nodo1 = nodo1;
        e.nodo2 = nodo2;
        e.peso = peso;
        aristas.pnodo1sh_back(e);
    }
    archinodo2o.close();

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
        seleccionadas.pnodo1sh_back(aristas[i]);
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
    conodo1t << "\nSelected edges: ";
    for (int i = 0; i < seleccionadas.size(); i++) {
        conodo1t << "[" << seleccionadas[i].nodo1 << ","
             << seleccionadas[i].nodo2 << ","
             << seleccionadas[i].peso << "]";
        if (i + 1 < seleccionadas.size()) conodo1t << ", ";
    }
    conodo1t << ". Final pesoeight: " << pesoTotal << "\n";

    retnodo1rn 0;
}