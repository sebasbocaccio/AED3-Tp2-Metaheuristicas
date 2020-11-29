#include "solucion.h"
#include <map>
#include <chrono>

int cant_vertices;
int cant_aristas_G;
int cant_aristas_H;

int main(int argc, char** argv) {
	
    std::cin >> cant_vertices;
    std::cin >> cant_aristas_G;
    std::cin >> cant_aristas_H;
    grafo G = grafo(cant_vertices, cant_aristas_G);
    grafo H = grafo(cant_vertices, cant_aristas_H);

    std::map<string, string> algoritmos_implementados = {
            {"H1", "Heuristica 1 "}, {"H2", "Heuristica 2"}, {"M1S", "Metaheuristica colores swap "},{"M1SC", "Metaheuristica colores swap_y_change"}, 
            {"M1SCH2", "Metaheuristica colores swap_y_change con su segunda Heuristica"},
            {"M1C", "Metaheuristica colores change"},{"M22", "Metaheuristica por vertices con heuristica_2"}, {"M21", "Metaheuristica por vertices con heuristica_1"}
    };
  	// Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    auto start = chrono::steady_clock::now();
    if (algoritmo == "H1")
    {
        heuristica_1(G, H);  
    }
    else if (algoritmo == "H2")
    {
        heuristica_2(G, H);     
    }
    else if (algoritmo == "M1S")
    {
        tabuSearch_allColors(G, H, "swap", 1, 0.3, 5000);
    }
    else if (algoritmo == "M1SC")
    {
        if(argc > 3)
            tabuSearch_allColors(G, H, "swap_y_change", 1, stof(argv[2]), stoi(argv[3]));
        else
            tabuSearch_allColors(G, H, "swap_y_change", 1, 0.3, 5000);
    }
    else if (algoritmo == "M1SCH2")
    {
        if(argc > 3)
            tabuSearch_allColors(G, H, "swap_y_change", 2, stof(argv[2]), stoi(argv[3]));
        else
            tabuSearch_allColors(G, H, "swap_y_change", 2, 0.3, 5000);
    }
    else if (algoritmo == "M1C")
    {
       
        tabuSearch_allColors(G, H, "change", 1, 0.3, 5000);
    }
    else if (algoritmo == "M21")
    {
       
        tabu_search_vertices(G,H,1, 0.8, 1000);
    }
    else if (algoritmo == "M22")
    {
        if(argc > 3)
            tabu_search_vertices(G, H, 2, stof(argv[2]), stoi(argv[3]));
        else
            tabu_search_vertices(G, H, 2, 0.8, 1000);   
        
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();
    clog << total_time << endl;

    return 0;
}
