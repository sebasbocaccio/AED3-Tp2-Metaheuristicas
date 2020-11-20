
#include "solucion.h"

int CICLOS_MAX_SIN_MEJORAS = 10000;
int MAX_CANT_ITERACIONES = 5000;
int CANT_INTENTOS = 10000;
int CANT_TOPS = 250;
int CANT_NODOS_A_ELEJIR = 14;


// Muy parecida a la heuristica uno, la diferencia es que no asigna color nuevo cada vez que cambia de vertice, sino que trata de reutilizar los que ya tiene.
vector<int> heuristica_2(grafo&G,grafo &H) {

    vector<int> colores(H.cantDeNodos(), -1);    // colores de cada nodo, -1 si no esta coloreado
    vector<pair<int, int>> grados;
    // ordeno los vertices por grado
    for (int i = 0; i < H.cantDeNodos(); ++i) {
        grados.push_back(make_pair(H.grado(i), i));
    }
    sort(grados.begin(), grados.end());
    int colores_usados = 0;
    for (int i = H.cantDeNodos() - 1; i >= 0; --i) {
        if (colores[grados[i].second] == -1) {// me fijo si i ya esta coloreado
            // Me fijo si puedo asignar un color que ya fue usado
            int minimo_disponible = 0;
            vector<int> listaAdyacenciaG = G.listaAdyacencia()[grados[i].second];

            while (!colorValido(G, colores, grados[i].second, minimo_disponible)) {
                minimo_disponible++;
            }
            // A lo sumo tengo que ponerle un color nuevo
            colores[grados[i].second] = minimo_disponible;
            if (minimo_disponible > colores_usados) { colores_usados++; }


            vector<int> listaAdyacenciaH = H.listaAdyacencia()[grados[i].second];
            // recorro los adyacentes al vertice i
            for (int j = 0; j < listaAdyacenciaH.size(); ++j) {
                if (colorValido(G, colores, listaAdyacenciaH[j], colores[grados[i].second])) {
                    colores[listaAdyacenciaH[j]] = colores[grados[i].second];
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
    printSol(colores, H);
    return colores;
}

vector<int> heuristica_1(grafo &G, grafo &H) {
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

    printSol(colores, H);
    return colores;

}


int impacto(grafo H, vector<int> coloreo) {
    vector<vector<int>> listaDeAdyacencia = H.listaAdyacencia();
    int impacto = 0;
    for (int i = 0; i < listaDeAdyacencia.size(); ++i) {
        for (int j = 0; j < listaDeAdyacencia[i].size(); ++j) {
            if (coloreo[i] == coloreo[listaDeAdyacencia[i][j]]) {
                impacto++;
            }
        }
    }
    return impacto / 2;
}


void printSol(vector<int> solucion, grafo H) {
    cout << impacto(H, solucion) << endl;
    for (int i = 0; i < solucion.size(); ++i) {
        cout << solucion[i] << ", ";
    }
    cout << endl;

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


vector<pair<int, int>> vecindad(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i;
    }
    vector<pair<int, int>> swaps;
    const int &cota = (int) floor((n * (n - 1) / 2) * 0.3);
    int cantIt = 0;
   // shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
//    for (int i = 0; i < n && cantIt < cota; i++) {
//        for (int j = i + 1; j < n && cantIt < cota; ++j) {
//            swaps.emplace_back(v[i], v[j]);
//            cantIt++;
//        }
//    }dsdfsdf
    while(cantIt<cota){
        int i = rand() % n;
        int j = rand() % n;
        if(i != j && count(swaps.begin(),swaps.end(), make_pair(v[i], v[j])) == 0){
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


vector<int> buscarMaximo(vector<pair<int, int>> &vecinos, vector<int> &coloreoActual, grafo &H) {
    vector<int> maximoActual = coloreoActual;
    int maximo = impacto(H, coloreoActual);
    for (int i = 0; i < vecinos.size(); ++i) {
        vector<int> posibleColoreo = coloreoActual;
        posibleColoreo[vecinos[i].first] = coloreoActual[vecinos[i].second];
        posibleColoreo[vecinos[i].second] = coloreoActual[vecinos[i].first];
        int impactoActual = impacto(H, posibleColoreo);
        if (maximo < impactoActual) {
            maximo = impactoActual;
            maximoActual = posibleColoreo;
        }
    }
    return maximoActual;
}

void filtrarTabu_allColors(vector<vector<int>> &tabuList, vector<pair<int, int>> &vecinos, vector<int> &coloreoActual) {
    for (int i = 0; i < vecinos.size(); i++) {
        vector<int> posibleColoreo = coloreoActual;
        posibleColoreo[vecinos[i].first] = coloreoActual[vecinos[i].second];
        posibleColoreo[vecinos[i].second] = coloreoActual[vecinos[i].first];
        if (std::find(tabuList.begin(), tabuList.end(), posibleColoreo) != tabuList.end()) {
            vecinos.erase(vecinos.begin() + i);
        }
    }
}




vector<int> tabuSearch_allColors(grafo &G, grafo &H) {
    vector<vector<int>> tabuList;
    vector<int> coloreoActual = heuristica_1(G, H);
    tabuList.push_back(coloreoActual);
    int cantSinSol = 0;
//    vector<int> v(G.cantDeNodos());
//    iota(v.begin(), v.end(), 1);
    vector<int> optimoActual = coloreoActual;
    while (cantSinSol < 5000) {
        vector<pair<int, int>> vecinos = vecindad(G.cantDeNodos());
        quitarInvalidos(vecinos, G, coloreoActual);
        filtrarTabu_allColors(tabuList, vecinos, coloreoActual);
        vector<int> maximo = buscarMaximo(vecinos, coloreoActual, H);
        tabuList.push_back(maximo);
        if (maximo > optimoActual) {
            optimoActual = maximo;
            cantSinSol = 0;
        } else {
            cantSinSol++;
        }
    }
    printSol(optimoActual,H);
    return optimoActual;
}




// Unir dos filtrar
void filtrarTabu_Vertices(vector<pair<int, int>> tabuList, vector<pair<int, int>> &vecinos, vector<int> coloreoActual) {
    for (int i = 0; i < vecinos.size(); i++) {
        if (count(tabuList.begin(), tabuList.end(), vecinos[i]) != 0 ||
            count(tabuList.begin(), tabuList.end(), make_pair(vecinos[i].second, vecinos[i].first)) != 0) {
            vecinos.erase(vecinos.begin() + i);
        }
    }
}




// lo de luki y sebi






void hacerSwap(vector<int> &coloreoAuxiliar, const pair<int, int> &swapeo) {
    int aux = coloreoAuxiliar[swapeo.first];
    coloreoAuxiliar[swapeo.first] = coloreoAuxiliar[swapeo.second];
    coloreoAuxiliar[swapeo.second] = aux;
}

void borrarElementos(vector<int> &nodos_no_visitados, int cant_a_borrar) {
    while (cant_a_borrar > 0) {
        nodos_no_visitados.erase(nodos_no_visitados.begin()); //Borro el primer elemento
        cant_a_borrar--;
    }
}

vector<pair<int, int>> generarPosiblesSwapeos(const grafo &G, const vector<int> &todos_los_nodos, int cant_nodos) {
    vector<pair<int, int>> swaps;
    vector<vector<int>> adyacencias = G.listaAdyacencia();
    for (int i = 0; i < cant_nodos; i++) {
        for (int j = 0; j < adyacencias[todos_los_nodos[i]].size(); j++) {
            int first = todos_los_nodos[i];
            int sec = adyacencias[todos_los_nodos[i]][j];
            pair<int, int> par = make_pair(todos_los_nodos[i], adyacencias[todos_los_nodos[i]][j]);
            swaps.push_back(par);
        }
    }
    return swaps;
}

vector<int> crear_vector_nodos(int n){
    vector<int> todos_los_nodos(n, 0);
    //lleno todos_los_nodos con la pos i = i
    for (int i = 0; i < n; i++) {
        todos_los_nodos[i] = i;
    }
    return todos_los_nodos;
}

vector<pair<int,int>> generarSwapeosValidos(vector<int> &nodos_no_visitados, grafo &G , vector<pair<int, int>> &memoria,vector<int> &coloreo){
    bool noHayOpciones = true;
    int intentos = 0;
    vector<pair<int,int>> arregloDeAdyacentes;
    while (noHayOpciones && intentos < CANT_INTENTOS) {
            noHayOpciones = true;
            
            //Busco nodos a los cuales hacerles swap
            arregloDeAdyacentes = generarPosiblesSwapeos(G, nodos_no_visitados, CANT_NODOS_A_ELEJIR);

            //Descarto posibles swap que estan en la lista taboo o no sean validas
            quitarInvalidos(arregloDeAdyacentes, G, coloreo);//sacarInvalidas saca los coloreos invalidos
            filtrarTabu_Vertices(memoria, arregloDeAdyacentes, coloreo);
            
            if (arregloDeAdyacentes.size() == 0) {
                borrarElementos(nodos_no_visitados, CANT_NODOS_A_ELEJIR);
                intentos++;
            } else
                noHayOpciones = false;
    }
    return arregloDeAdyacentes;
}


bool cambieOptimo(vector<pair<int,int>> &swapeosValidos, grafo &H,vector<int> &coloreo,int &mejorSol, pair<int, int> &intercambio){

    bool cambie = false;
    vector<int> coloreoAuxiliar;
    vector<int> mejorColoreo = coloreo;

    for (pair<int, int> swapeo : swapeosValidos) {
            coloreoAuxiliar = coloreo;
            hacerSwap(coloreoAuxiliar, swapeo);
            //impact se fija asi nomas el maximo impacto suponiendo que el coloreo ya es valido
            int impactoAuxiliar = impacto(H, coloreoAuxiliar);
            if (impactoAuxiliar > mejorSol) {
                    intercambio = swapeo;
                    mejorSol = impactoAuxiliar;
                    mejorColoreo = coloreoAuxiliar;
                    cambie = true;
                }
    }
    if(coloreo != mejorColoreo) 
        coloreo = mejorColoreo;
    
    return cambie;

}



void tabu_search_vertices(grafo& G, grafo& H) {
    vector<int> coloreo = heuristica_1(G, H);
    int impacto_input = impacto(H,coloreo);
    int n = G.cantDeNodos();
        
    vector<int> todos_los_nodos = crear_vector_nodos(n);
    vector<pair<int, int>> memoria;


    int cant_iteraciones = 0;
    int ciclos_sin_mejoras = 0;
    int mejorSol = impacto_input;
    vector<int> mejorColoreo = coloreo;
    while (ciclos_sin_mejoras < CICLOS_MAX_SIN_MEJORAS && cant_iteraciones < MAX_CANT_ITERACIONES) { //faltaria agregar el tiempo (nosPasamosDeTiempo)

        vector<int> nodos_no_visitados = todos_los_nodos;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle(nodos_no_visitados.begin(), nodos_no_visitados.end(), std::default_random_engine(seed));
        
        //Creo Swapeos, eliminando los que estan en la lista tabu y los que producen coloreos invalidos 
        vector<pair<int,int>> swapeosValidos = generarSwapeosValidos(nodos_no_visitados,G,memoria, coloreo);

        if(swapeosValidos.size() != 0){
 
            //Busca el swap mas optimo posible para cambiar coloreo. Si no hay uno mejor, lo cambia por un intercambio cualquiera.
            pair<int, int> intercambio;
            if(cambieOptimo(swapeosValidos,H,coloreo,mejorSol,intercambio)){
                mejorColoreo = coloreo;
                memoria.push_back(intercambio);
                ciclos_sin_mejoras = 0;
            }
            else{
                ciclos_sin_mejoras++;
                hacerSwap(coloreo, swapeosValidos[0]);
                memoria.push_back(swapeosValidos[0]);
            }
        }
        else ciclos_sin_mejoras++;  
        
        cant_iteraciones++;
    }
    printSol(mejorColoreo,H);
    

}





