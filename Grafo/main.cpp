#include "solucion.h"



int main() {
    int cant_vertices = 0;
    int cant_aristas_G = 0;
    int cant_aristas_H = 0;
    std::cin >> cant_vertices;
    std::cin >> cant_aristas_G;
    std::cin >> cant_aristas_H;
    grafo G = grafo(cant_vertices, cant_aristas_G);
    grafo H = grafo(cant_vertices, cant_aristas_H);
    //heuristica_1(G, H);
    tabuSearch_allColors(G, H);
    return 0;
}
