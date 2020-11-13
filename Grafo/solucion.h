#ifndef PRUEBASGRAFOS_SOLUCION_H
#define PRUEBASGRAFOS_SOLUCION_H


#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;


class grafo {

public:
    int cantDeNodos() { return _cantNodos; }

    int sizeVector() { return relaciones.size(); }

    int grado(const int &nodo) { return relaciones[nodo].size(); }

    vector<vector<int>> listaAdyacencia() { return relaciones; }


    grafo(int nodos, int aristas) : _cantNodos(nodos), _cantAristas(aristas) {
        int src;
        int dst;
        relaciones = std::vector<std::vector<int>>(_cantNodos);
        std::cout << "Vaya ingresandolas de forma v1 v2 e" << std::endl;
        for (int i = 0; i < aristas; i++) {
            std::cin >> src >> dst;
            relaciones[src - 1].push_back(dst - 1);
            relaciones[dst - 1].push_back(src - 1);
        }


    }

    void mostrarAdyacencia() {
        for (std::vector<int> v : relaciones) {
            std::cout << "[";
            for (int i = 0; i < v.size() - 1; ++i) {
                std::cout << v[i] << ", ";
            }
            std::cout << v[v.size() - 1] << "]";
        }

    }

private:
    int &_cantAristas;
    int &_cantNodos;
    std::vector<std::vector<int>> relaciones;
};



int impacto(grafo H, vector<int> coloreo);
void printSol(grafo H, vector<int> solucion);
bool colorValido(grafo G, vector<int> colores, int nodo, int color);
vector<int> maximoImpacto(grafo G, grafo H);
vector<pair<int, int>> vecindad(int n);
bool estadoValido(grafo &G, const vector<int> &colores);
void quitarInvalidos(vector<pair<int, int>> &vecinos, grafo &G, const vector<int> &coloreoActual);
vector<int> buscarMaximo(vector<pair<int, int>> &vecinos, vector<int> coloreoActual, grafo &H);
void filtrarTabu(vector<vector<int>> tabuList, vector<pair<int, int>>& vecinos, vector<int> coloreoActual);
vector<int> tabuSearch_allColors(grafo G, grafo H);

#endif //PRUEBASGRAFOS_SOLUCION_H
