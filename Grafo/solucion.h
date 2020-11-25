#ifndef SOLUCION_H
#define SOLUCION_H

#include <string>
#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;


class grafo {

public:
    int cantDeNodos() { return _cantNodos; }

    int sizeVector() { return relaciones.size(); }

    int grado(const int &nodo) { return relaciones[nodo].size(); }

    vector<vector<int>> listaAdyacencia() const { return relaciones; }


    grafo(int nodos, int aristas) : _cantNodos(nodos), _cantAristas(aristas) {
        int src;
        int dst;
        relaciones = std::vector<std::vector<int>>(_cantNodos);
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
    int _cantAristas;
    int _cantNodos;
    std::vector<std::vector<int>> relaciones;
};

//GLOBAL VAR:
extern int CICLOS_MAX_SIN_MEJORAS;
extern int MAX_CANT_ITERACIONES;
extern int CANT_INTENTOS;
extern int CANT_TOPS;
extern int CANT_NODOS_A_ELEJIR;

void noPrintear_Heuristica();
void printSol(vector<int> solucion, grafo H);
void hacerSwap(vector<int> &coloreoAuxiliar,const pair<int,int>& swapeo);
void borrarElementos(vector<int> &nodos_no_visitados, int cant_a_borrar);
vector<pair<int,int>> generarPosiblesSwapeos(const grafo& G, const vector<int> &todos_los_nodos, int cant_nodos);
void tabu_search_vertices(grafo &G,grafo &H);


int impacto(grafo H, vector<int> coloreo);

bool colorValido(grafo G, vector<int> colores, int nodo, int color);
vector<int> heuristica_2(grafo&G,grafo &H);
vector<int> heuristica_1(grafo &G, grafo &H);
vector<vector<int>> vecindad(int n, string criterio, int colorMaximo, int colorMinimo);
bool estadoValido(grafo &G, const vector<int> &colores);
void quitarInvalidos(vector<vector<int>> &vecinos, grafo &G, const vector<int> &coloreoActual);
void quitarInvalidos(vector<pair<int, int>> &vecinos, grafo &G, const vector<int> &coloreoActual);
vector<int> buscarMaximo(vector<vector<int>> &vecinos, vector<int> &coloreoActual, grafo &H, string modo);
void filtrarTabu_allColors(vector<vector<int>> &tabuList, vector<vector<int>> &vecinos, vector<int> &coloreoActual);
vector<int> tabuSearch_allColors(grafo &G, grafo &H, string criterio);



#endif //SOLUCION_H
