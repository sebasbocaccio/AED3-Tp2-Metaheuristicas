#include "solucion.h"

//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//

/*
Funciones a implementar yet:

-generarPosiblesSwapeos
-sacarInvalidas AGUS&TIN 
-filtrar AGUS&TIN  
-borrarElementos DONE 
-hacerSwap DONE 
-impacto AGUS&TIN 
*/


int main() {
    int cant_vertices = 0;
    int cant_aristas_G = 0;
    int cant_aristas_H = 0;
    std::cin >> cant_vertices;
    std::cin >> cant_aristas_G;
    std::cin >> cant_aristas_H;
    grafo G = grafo(cant_vertices, cant_aristas_G);
    grafo H = grafo(cant_vertices, cant_aristas_H);
  //  heuristica_2(G,H);
   // heuristica_1(G,H);
   tabu_search_vertices(G, H);
   // tabuSearch_allColors(G, H);
    return 0;
}
