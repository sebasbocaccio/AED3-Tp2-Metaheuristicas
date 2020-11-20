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
<<<<<<< HEAD
   // tabu_search_vertices(G, H);
    tabuSearch_allColors(G, H, "swap_y_change");
=======
  //  heuristica_2(G,H);
   // heuristica_1(G,H);
   tabu_search_vertices(G, H);
   // tabuSearch_allColors(G, H);
>>>>>>> 3f3a282fd3e92db8f1bc353ab9fa164b7ed31dbb
    return 0;
}
