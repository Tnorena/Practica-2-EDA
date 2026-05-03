//hecho con ayuda de Gemini, Por Tomás Noreña y Miguel muñoz

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// aqui estamos definiendo el mapa como una lista de adyacencia (un vector de vectores)
// Lo llamamos 'mapaDeConexiones'
vector<vector<int>> mapaDeConexiones;

int main() {
    // usamos 'archivoDelMapa' para el lector
    ifstream archivoDelMapa("datos/roadNet-PA.txt"); 
    
    if (!archivoDelMapa.is_open()) {
        cout << "Error: No se encontro el archivo en la carpeta 'datos'" << endl;
        return 1;
    }

    string linea;
    int origen, destino;
    int cantidadDeCalles = 0;
    int nodoMaximo = 1090920; // Pensilvania tiene aprox. este número de nodos

    // aquí preparamos el tamaño del mapa para que no falle la memoria
    mapaDeConexiones.resize(nodoMaximo + 1);

    cout << "Cargando el mapa de Pensilvania..." << endl;

    while (getline(archivoDelMapa, linea)) {
        if (linea.empty() || linea[0] == '#') continue;
        stringstream lectorDeLinea(linea);
        int origen, destino;

        if (lectorDeLinea >> origen >> destino) {
            int nodoMax = (origen > destino) ? origen : destino;
            if (nodoMax >= (int)mapaDeConexiones.size()) {
                mapaDeConexiones.resize(nodoMax + 1);
            }

            mapaDeConexiones[origen].push_back(destino);
            mapaDeConexiones[destino].push_back(origen); // calles bidireccionales
            cantidadDeCalles++;
        }
    }

    cout << "Se han cargado con exito " << cantidadDeCalles << " conexiones en el mapa." << endl;
    
    archivoDelMapa.close();
    // esto es para verificar que no solo cargo los datos, sino que puedo leerlos
    int nodoUsuario;
    cout << "\n¿Que nodo quieres revisar? (Escribe el numero): ";
    cin >> nodoUsuario;

    if (nodoUsuario >= 0 && nodoUsuario < mapaDeConexiones.size()) {
        if (mapaDeConexiones[nodoUsuario].empty()) {
            cout << "Ese nodo existe pero no tiene calles conectadas." << endl;
        } else {
            cout << "El nodo " << nodoUsuario << " tiene conexiones con: ";
            for (int vecino : mapaDeConexiones[nodoUsuario]) {
                cout << vecino << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Ese ID de nodo no esta en el mapa de Pensilvania." << endl;
    }
    return 0;
}