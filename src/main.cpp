//hecho con ayuda de Gemini, Por Tomás Noreña y Miguel muñoz
#include <iostream>
#include <string>
#include "graph.hpp"
#include "loader.cpp"
#include "structural.cpp"
#include "modulob.cpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: ./eda_pf <modulo>" << endl;
        cout << "  Modulos disponibles: A, B, C" << endl;
        cout << "  Ejemplo: ./eda_pf A" << endl;
        return 1;
    }

    string modulo = argv[1];

    cout << "Cargando grafo desde data/roadNet-PA.txt ..." << endl;
    Grafo* g = cargarGrafo("data/roadNet-PA.txt");
    if (g == nullptr) {
        cerr << "Error: no se pudo cargar el grafo." << endl;
        return 1;
    }

    if (modulo == "A") {
        ejecutarModuloA(g, "results/analisis_estructural.txt");
    } else if (modulo == "B") {
        ejecutarModuloB(g, "results/consultas_p2p.csv");
    } else if (modulo == "C") {
        cout << "Modulo C: proximamente..." << endl;
    } else {
        cout << "Modulo no reconocido: " << modulo << endl;
    }

    delete g;
    return 0;
}
