// bfs.cpp - Tomás Noreña y Miguel Muñoz
#include "graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
using namespace std;

// sigue los punteros prev desde el destino hasta el inicio
// y voltea el vector al final para que quede en orden
vector<int> reconstruirCaminoBFS(const vector<int>& prev, int inicio, int destino) {
    vector<int> camino;
    int actual = destino;

    // si destino no tiene padre y tampoco es el inicio, no hay camino
    if (prev[destino] == -1 && destino != inicio) {
        return camino;
    }

    while (actual != -1) {
        camino.push_back(actual);
        actual = prev[actual];
    }
    reverse(camino.begin(), camino.end());
    return camino;
}

ResultadoBFS bfs(const Grafo* g, int inicio, int destino, bool guardarCamino) {
    ResultadoBFS resultado;
    resultado.saltos = -1; // -1 = sin camino
    resultado.nodosExplorados = 0;
    resultado.tiempoMs = 0;

    int n = g->numNodos;

    if (inicio < 0 || inicio >= n || destino < 0 || destino >= n) {
        cout << "Error: nodo fuera de rango." << endl;
        return resultado;
    }

    vector<int> dist(n, -1); // -1 = no visitado
    vector<int> prev(n, -1); // -1 = sin padre (nodo raíz o no alcanzado)

    dist[inicio] = 0;
    queue<int> cola;
    cola.push(inicio);

    auto tiempoInicio = chrono::high_resolution_clock::now();

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        resultado.nodosExplorados++;

        if (actual == destino) break;

        for (auto& arista : g->adj[actual]) {
            int vecino = arista.first;
            // solo encolamos si no fue visitado antes
            if (dist[vecino] == -1) {
                dist[vecino] = dist[actual] + 1;
                prev[vecino] = actual;
                cola.push(vecino);
            }
        }
    }

    auto tiempoFin = chrono::high_resolution_clock::now();
    resultado.tiempoMs = chrono::duration<double, milli>(tiempoFin - tiempoInicio).count();

    if (dist[destino] != -1) {
        resultado.saltos = dist[destino];
        if (guardarCamino) {
            resultado.camino = reconstruirCaminoBFS(prev, inicio, destino);
        }
    }

    return resultado;
}