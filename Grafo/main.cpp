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
            relaciones[src-1].push_back(dst-1);
            relaciones[dst-1].push_back(src-1);
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




bool colorValido(grafo G, vector<int> colores, int nodo, int color) {
    vector<int> listaAdyacencia = G.listaAdyacencia()[nodo];
    if(colores[nodo] != -1){
       return false;
    }
    for (int i = 0; i < listaAdyacencia.size(); ++i) {
        if (colores[listaAdyacencia[i]] == color)
            return false;
    }
    return true;
}


void maximoImpacto(grafo G, grafo H) {
    vector<int> colores(H.cantDeNodos(), -1);    // colores de cada nodo, -1 si no esta coloreado
    vector<pair<int, int>> grados;
    // ordeno los vertices por grado
    for (int i = 0; i < H.cantDeNodos(); ++i) {
        grados.push_back(make_pair(H.grado(i), i));
    }
    sort(grados.begin(), grados.end());

    // posible optimizacion con priorida de colores

    for (int i = H.cantDeNodos()-1; i >= 0; --i) {
        if(colores[grados[i].second] == -1) {   // me fijo si i ya esta coloreado
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
        if(colores[i] == -1){
            colores[i] = colorDistinto;
            colorDistinto--;
        }
    }

    for (int i = 0; i < colores.size(); ++i) {
        cout << colores[i] << ", ";
    }

}
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
//--------------------ESTO NO VA A COMPILARRR COMENTENLOOOO POR FAVOR -------------//
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
			arregloDeAdyacentes = generarPosiblesSwapeos(nodos_no_visitados,CANT_NODOS_A_ELEJIR);
			//Descarto posibles swap que estan en la lista taboo o no sean validas
			sacarInvalidas(arregloDeAdyacentes,NECESITA UN GRAFO?);//sacarInvalidas saca los coloreos invalidos
			filtrar(arregloDeAdyacentes,memoria);
			if(arregloDeAdyacentes.size() == 0){
				borrar(nodos_no_visitados,0,CANT_NODOS_A_ELEJIR);
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
			int impactoAuxiliar =impact(coloreoAuxiliar,G?,H?);
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
