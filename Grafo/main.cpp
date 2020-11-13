#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

//GLOBAL VAR:
int CICLOS_MAX_SIN_MEJORAS;
int MAX_CANT_ITERACIONES;
int CANT_INTENTOS;
int CANT_TOPS;
int CANT_NODOS_A_ELEJIR;




void hacerSwap(vector<int> &coloreoAuxiliar,const &pair<int,int> swapeo){
int aux = coloreoAuxiliar[swapeo.first - 1 ];
coloreoAuxiliar[swapeo.first - 1 ] = coloreoAuxiliar[swapeo.second - 1 ];
coloreoAuxiliar[swapeo.second - 1 ] = aux;
}

void borrarElementos(vector<int> &nodos_no_visitados, int cant_a_borrar){
    while(cant_a_borrar > 0){
        nodos_no_visitados.erase(nodos_no_visitados.begin()); //Borro el primer elemento
        cant_a_borrar--;
    }
}
vector<pair<int,int>> generarPosiblesSwapeos(const &grafo G, const vector<int> todos_los_nodos, int cant_nodos){
vector<pair<int,int>> swaps;
vector<vector<int>> adyacencias = G.listaAdyacencia();
for(int i = 0 ; i < cant_nodos; i++){
for(int j = 0; j < adyacencias[i]; j++){
pair<int,int> par = make_pair(todos_los_nodos[i], adyacencias[todos_los_nodos[i]][j]);
swaps.pushback(par);
}
}
return swaps;
}



void tabu_search_vertices(grafo G,grafo H,vector<int> coloreo,int impacto){
    int n= G.cantDeNodos();
    vector<int> todos_los_nodos(n,0);
    //lleno todos_los_nodos con la pos i = i
    for(int i = 0 ; i < n ; i++){
        todos_los_nodos[i] = i+1;
    }
    vector<pair<int,int>> memoria;
    int cant_iteraciones = 0;
    int ciclos_sin_mejoras = 0;
    int intentos = 0;
    bool noHayOpciones = true;
    int mejorSol = impacto;
    vector<int> mejorColoreo = coloreo;
    while(ciclos_sin_mejoras < CICLOS_MAX_SIN_MEJORAS && cant_iteraciones < MAX_CANT_ITERACIONES ){//faltaria agregar el tiempo (nosPasamosDeTiempo)
        vector<int> nodos_no_visitados = shuffle(todos_los_nodos.begin(),todos_los_nodos.end());
        intentos = 0;
        while(noHayOpciones && intentos < CANT_INTENTOS ){
            noHayOpciones = true;
            //Busco nodos a los cuales hacerles swap
            arregloDeAdyacentes = generarPosiblesSwapeos(&G,&nodos_no_visitados,CANT_NODOS_A_ELEJIR);
            //Descarto posibles swap que estan en la lista taboo o no sean validas
            sacarInvalidas(arregloDeAdyacentes,NECESITA UN GRAFO?);//sacarInvalidas saca los coloreos invalidos
            filtrar(arregloDeAdyacentes,memoria);
            if(arregloDeAdyacentes.size() == 0){
                borrarElementos(nodos_no_visitados,CANT_NODOS_A_ELEJIR);
                intentos++;
            }
            else
                noHayOpciones = false;
        }
        //Evaluo la funcion objetivo para ver si hay mejoras o no
        bool cambie = false;
        vector<int> coloreoAuxiliar;
        pair<int,int> intercambio;
        for(pair<int,int> swapeo: arregloDeAdyacentes){
            coloreoAuxiliar = coloreo;
            hacerSwap(coloreoAuxiliar,swapeo);
            //impact se fija asi nomas el maximo impacto suponiendo que el coloreo ya es valido
            int impactoAuxiliar =impacto(H,coloreoAuxiliar);
            if(impactoAuxiliar > mejorSol){
                pair<int,int> intercambio = swapeo;
                mejorSol = impactoAuxiliar;
                mejorColoreo = coloreoAuxiliar;
                cambie = true;
            }
        }
        if(!cambie){
            ciclos_sin_mejoras++;
            coloreo = hacerSwap(colores,arregloDeAdyacentes[0]);
            memoria.pushback(arregloDeAdyacentes[0]);
        }
        else{
            memoria.pushback(intercambio);
            ciclos_sin_mejoras = 0;
        }
        cant_iteraciones++;
    }
    cout<<mejorSol <<endl;
    cout << mejorColoreo << endl;

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
