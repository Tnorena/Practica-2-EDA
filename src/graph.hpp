// graph.hpp - Tomás Noreña y Miguel Muñoz
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
using namespace std;

// cada nodo guarda una lista de vecino y peso
// usamos lista de adyacencia porque la matriz sería inviable para grafos grandes
struct Grafo {
    int numNodos;
    int numAristas;
    vector<vector<pair<int,int>>> adj;

    Grafo(int n) : numNodos(n), numAristas(0), adj(n) {}

    // arista no dirigida: la agregamos en los dos sentidos
    void agregarArista(int u, int v, int peso) {
        adj[u].push_back({v, peso});
        adj[v].push_back({u, peso});
        numAristas++;
    }
};

struct ResultadoDijkstra {
    long long distancia; // en metros (o la unidad del peso)
    int nodosExplorados;
    double tiempoMs;
    vector<int> camino; // vacío si no se pidió o no hay camino
};

struct ResultadoBFS {
    int saltos; // -1 si no hay camino
    int nodosExplorados;
    double tiempoMs;
    vector<int> camino; // vacío si no se pidió o no hay camino
};

#endif