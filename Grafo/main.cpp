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


void printSol(vector<int> solucion){
    cout << impacto(solucion) << endl;
    for (int i = 0; i < solucion.size(); ++i) {
        cout << solucion[i] << ", ";
    }
}

bool colorValido(grafo G, vector<int> colores, int nodo, int color) {
    vector<int> listaAdyacencia = G.listaAdyacencia()[nodo];
    if (colores[nodo] != -1) {
        return false;
    }
    for (int i = 0; i < listaAdyacencia.size(); ++i) {
        if (colores[listaAdyacencia[i]] == color)
            return false;
    }
    return true;
}


vector<int> maximoImpacto(grafo G, grafo H) {
    vector<int> colores(H.cantDeNodos(), -1);    // colores de cada nodo, -1 si no esta coloreado
    vector<pair<int, int>> grados;
    // ordeno los vertices por grado
    for (int i = 0; i < H.cantDeNodos(); ++i) {
        grados.push_back(make_pair(H.grado(i), i));
    }
    sort(grados.begin(), grados.end());

    // posible optimizacion con priorida de colores

    for (int i = H.cantDeNodos() - 1; i >= 0; --i) {
        if (colores[grados[i].second] == -1) {   // me fijo si i ya esta coloreado
            colores[grados[i].second] = i;
            vector<int> listaAdyacencia = H.listaAdyacencia()[grados[i].second];
            // recorro los adyacentes al vertice i
            for (int j = 0; j < listaAdyacencia.size(); ++j) {
                if (colorValido(G, colores, listaAdyacencia[j], colores[grados[i].second])) {
                    colores[listaAdyacencia[j]] = colores[grados[i].second];
                }
            }
        }
    }

    // asigno colores distintos a los que quedan sin colorear
    int colorDistinto = -2;
    for (int i = 0; i < colores.size(); ++i) {
        if (colores[i] == -1) {
            colores[i] = colorDistinto;
            colorDistinto--;
        }
    }

    for (int i = 0; i < colores.size(); ++i) {
        cout << colores[i] << ", ";
    }
    return colores;

}

vector<pair<int, int>> vecindad(int n) {

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    vector<pair<int, int>> swaps;
    const double &cota = (double) (n * (n - 1) / 2) * 0.2;
    double cantIt = 0;
    for (int i = 0; i < n && cantIt < cota; i++) {
        for (int j = i + 1; j < n && cantIt < cota; ++j) {
            swaps.emplace_back(v[i], v[j]);
            cantIt++;
        }
    }
    return swaps;
}

bool estadoValido(grafo &G, const vector<int> &colores) {
    vector<vector<int>> listaAdyacencia = G.listaAdyacencia();
    for (int i = 0; i < G.cantDeNodos(); ++i) {
        int colorVertice = colores[i];
        for (int j = 0; j < listaAdyacencia[i].size(); ++j) {
            if (colorVertice == colores[listaAdyacencia[i][j]]) {
                return false;
            }
        }
    }
    return true;
}

void quitarInvalidos(vector<pair<int, int>> &vecinos, grafo &G, const vector<int> &coloreoActual) {
    for (int i = 0; i < vecinos.size(); i++) {
        vector<int> posibleColoreo = coloreoActual;
        posibleColoreo[vecinos[i].first] = coloreoActual[vecinos[i].second];
        posibleColoreo[vecinos[i].second] = coloreoActual[vecinos[i].first];
        if (!estadoValido(G, posibleColoreo)) {
            vecinos.erase(vecinos.begin() + i);
        }
    }
}



vector<int> buscarMaximo(vector<pair<int, int>> &vecinos, vector<int> coloreoActual, grafo &H){
    vector<int> maximoActual = coloreoActual;
    int maximo = impacto(H, coloreoActual);
    for(int i = 0; i < vecinos.size(); ++i){
        vector<int> posibleColoreo = coloreoActual;
        posibleColoreo[vecinos[i].first] = coloreoActual[vecinos[i].second];
        posibleColoreo[vecinos[i].second] = coloreoActual[vecinos[i].first];
        int impactoActual = impacto(H, posibleColoreo);
        if(maximo < impactoActual){
            maximo = impactoActual;
            maximoActual = posibleColoreo;
        }
    }
    return maximoActual;
}

void filtrarTabu(vector<vector<int>> tabuList, vector<pair<int, int>>& vecinos, vector<int> coloreoActual) {
    for (int i = 0; i < vecinos.size(); i++) {
        vector<int> posibleColoreo = coloreoActual;
        posibleColoreo[vecinos[i].first] = coloreoActual[vecinos[i].second];
        posibleColoreo[vecinos[i].second] = coloreoActual[vecinos[i].first];

        if(std::find(tabuList.begin(), tabuList.end(), posibleColoreo) != tabuList.end()) {
            vecinos.erase(vecinos.begin() + i);
        }
    }
}

vector<int> tabuSearch_allColors(grafo G, grafo H) {
    vector<vector<int>> tabuList;
    vector<int> coloreoActual = maximoImpacto(G, H);
    tabuList.push_back(coloreoActual);
    int cantSinSol = 0;
//    vector<int> v(G.cantDeNodos());
//    iota(v.begin(), v.end(), 1);
    vector<int> optimoActual = coloreoActual;
    while (cantSinSol < 1000) {
        //shuffle(v.begin(), v.endpai(), std::mt19937(std::random_device()()));
        vector<pair<int, int>> vecinos = vecindad(G.cantDeNodos());
        quitarInvalidos(vecinos, G, coloreoActual);
        filtrarTabu(tabuList, vecinos, coloreoActual);
        vector<int> maximo = buscarMaximo(vecinos, coloreoActual, H);
        tabuList.push_back(maximo);
        if(maximo> optimoActual){
            optimoActual = maximo;
        } else{
            cantSinSol++;
        }
    }

    printSol(optimoActual);
    return optimoActual;
}


int main() {
    int cant_vertices = 0;
    int cant_aristas_G = 0;
    int cant_aristas_H = 0;
    std::cin >> cant_vertices;
    std::cin >> cant_aristas_G;
    std::cin >> cant_aristas_H;
    grafo G = grafo(cant_vertices, cant_aristas_G);
    grafo H = grafo(cant_vertices, cant_aristas_H);
    maximoImpacto(G, H);
    return 0;
}
