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

    vector<vector<int>> listaAdyacencia() const { return relaciones; }


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

//GLOBAL VAR:
int CICLOS_MAX_SIN_MEJORAS;
int MAX_CANT_ITERACIONES;
int CANT_INTENTOS;
int CANT_TOPS;
int CANT_NODOS_A_ELEJIR;



void hacerSwap(vector<int> &coloreoAuxiliar,const pair<int,int>& swapeo);
void borrarElementos(vector<int> &nodos_no_visitados, int cant_a_borrar);
vector<pair<int,int>> generarPosiblesSwapeos(const grafo& G, const vector<int> todos_los_nodos, int cant_nodos);
void tabu_search_vertices(grafo G,grafo H,vector<int> coloreo,int impacto);


int impacto(grafo H, vector<int> coloreo);
void printSol(grafo H, vector<int> solucion);
bool colorValido(grafo G, vector<int> colores, int nodo, int color);
vector<int> heuristica_1(grafo G, grafo H);
vector<pair<int, int>> vecindad(int n);
bool estadoValido(grafo &G, const vector<int> &colores);
void quitarInvalidos(vector<pair<int, int>> &vecinos, grafo &G, const vector<int> &coloreoActual);
vector<int> buscarMaximo(vector<pair<int, int>> &vecinos, vector<int> coloreoActual, grafo &H);
void filtrarTabu(vector<vector<int>> tabuList, vector<pair<int, int>>& vecinos, vector<int> coloreoActual);
vector<int> tabuSearch_allColors(grafo G, grafo H);

#endif //PRUEBASGRAFOS_SOLUCION_H
