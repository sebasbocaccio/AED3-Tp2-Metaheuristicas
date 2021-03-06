#include "solucion.h"

int CICLOS_MAX_SIN_MEJORAS = 1000;
int MAX_CANT_ITERACIONES = 5000;
int CANT_INTENTOS = 100;
int CANT_TOPS = 250;
int CANT_NODOS_A_ELEJIR;
float PORCENTAJE_NODOS = 0.8;
bool hayquePrintear = true;


void noPrintear_Heuristica() {
    hayquePrintear = false;
}

// Muy parecida a la heuristica uno, la diferencia es que no asigna color nuevo cada vez que cambia de vertice, sino que trata de reutilizar los que ya tiene.
vector<int> heuristica_2(grafo &G, grafo &H) {

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
    if (hayquePrintear) printSol(colores, H);
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

    if (hayquePrintear) printSol(colores, H);
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
    cout << impacto(H, solucion);
    for (int i = 0; i < solucion.size(); ++i) {
        cout << " " << solucion[i];
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


vector<vector<int>> vecindad(int n, string criterio, int colorMaximo, int colorMinimo) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i;
    }
    vector<vector<int>> vecinos;
    int cota = (int) floor((n * (n - 1) / 2) * PORCENTAJE_NODOS);
    if (criterio == "swap_y_change") {
        cota /= 2;
    }
    int cantIt = 0;
    if (criterio == "swap" || criterio == "swap_y_change") {
        while (cantIt < cota) {
            vector<int> newSwap;
            int i = rand() % n;
            int j = rand() % n;
            newSwap.insert(newSwap.end(), {1, i, j});
            if (i != j && count(vecinos.begin(), vecinos.end(), newSwap) == 0) {
                vecinos.push_back(newSwap);
                cantIt++;
            }
        }
    }
    cantIt = 0;
    if (criterio == "change" || criterio == "swap_y_change") {
        while (cantIt < cota) {
            int newColor = rand() % (colorMaximo * 2);
            vector<int> newChange;
            if (newColor > colorMaximo) {
                newChange.insert(newChange.end(), {0, rand() % n, colorMaximo + 1});
                if (count(vecinos.begin(), vecinos.end(), newChange) == 0) {
                    vecinos.push_back(newChange);
                    cantIt++;
                }
            } else {
                newChange.insert(newChange.end(), {0, rand() % n, newColor});
                vecinos.push_back(newChange);
                cantIt++;
            }
        }
    }
    return vecinos;
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

void quitarInvalidos(vector<vector<int>> &vecinos, grafo &G, const vector<int> &coloreoActual) {
    auto it = vecinos.begin();
    while(it != vecinos.end()) {
        vector<int> posibleColoreo = coloreoActual;
        if ((*it)[0] == 1) {
            posibleColoreo[(*it)[1]] = coloreoActual[(*it)[2]];
            posibleColoreo[(*it)[2]] = coloreoActual[(*it)[1]];
            if (!estadoValido(G, posibleColoreo)) {
                it = vecinos.erase(it);
            } else {
                it++;
            }
        } else if ((*it)[0] == 0) {
            posibleColoreo[(*it)[1]] = (*it)[2];
            if (!estadoValido(G, posibleColoreo)) {
                it = vecinos.erase(it);
            } else{
                it++;
            }
        }

    }
}



vector<int> buscarMaximo(vector<vector<int>> &vecinos, vector<int> &coloreoActual, grafo &H, string modo) {
    if (modo == "random") {
        vector<int> posibleColoreo = coloreoActual;
        int random = rand() % vecinos.size();
        if (vecinos[random][0] == 1) {
            posibleColoreo[vecinos[random][1]] = coloreoActual[vecinos[random][2]];
            posibleColoreo[vecinos[random][2]] = coloreoActual[vecinos[random][1]];
        } else if (vecinos[random][0] == 0) {
            posibleColoreo[vecinos[random][1]] = vecinos[random][2];
        }
        return posibleColoreo;
    } else {
        vector<int> maximoActual = coloreoActual;
        int maximo = impacto(H, coloreoActual);

        for (int i = 0; i < vecinos.size(); ++i) {
            vector<int> posibleColoreo = coloreoActual;
            if (vecinos[i][0] == 1) {
                posibleColoreo[vecinos[i][1]] = coloreoActual[vecinos[i][2]];
                posibleColoreo[vecinos[i][2]] = coloreoActual[vecinos[i][1]];
                int impactoActual = impacto(H, posibleColoreo);
                if (maximo <= impactoActual) {
                    maximo = impactoActual;
                    maximoActual = posibleColoreo;
                }
            } else if (vecinos[i][0] == 0) {
                posibleColoreo[vecinos[i][1]] = vecinos[i][2];
                int impactoActual = impacto(H, posibleColoreo);
                if (maximo <= impactoActual) {
                    maximo = impactoActual;
                    maximoActual = posibleColoreo;
                }
            }
        }
        return maximoActual;
    }
}


void filtrarTabu_allColors(vector<vector<int>> &tabuList, vector<vector<int>> &vecinos, vector<int> &coloreoActual) {
    for (int i = 0; i < vecinos.size(); i++) {
        vector<int> posibleColoreo = coloreoActual;
        if (vecinos[i][0] == 1) {
            posibleColoreo[vecinos[i][1]] = coloreoActual[vecinos[i][2]];
            posibleColoreo[vecinos[i][2]] = coloreoActual[vecinos[i][1]];
            if (std::find(tabuList.begin(), tabuList.end(), posibleColoreo) != tabuList.end()) {
                vecinos.erase(vecinos.begin() + i);
            } else if (vecinos[i][0] == 0) {
                posibleColoreo[vecinos[i][1]] = vecinos[i][2];
                if (std::find(tabuList.begin(), tabuList.end(), posibleColoreo) != tabuList.end()) {
                    vecinos.erase(vecinos.begin() + i);
                }
            }
        }
    }
}

// tipo change [0, nodo, color]
// tipo swap [1, nodo1, nodo2]
vector<int> tabuSearch_allColors(grafo &G, grafo &H, string criterio, int heuristica, float porcentajeNodos, int interacionesSinMejoras) {
    PORCENTAJE_NODOS = porcentajeNodos;
    CICLOS_MAX_SIN_MEJORAS = interacionesSinMejoras; //variables con las que vamos a experimentar
    noPrintear_Heuristica();    //es para que no se printeen los valores que den las heurisiticas
    vector<int> coloreoActual;
    vector<vector<int>> tabuList;
    if(heuristica == 1){
        coloreoActual = heuristica_1(G, H);
    } else if(heuristica == 2) {
        coloreoActual = heuristica_2(G, H);
    }
    int cantSinSol = 0;
    vector<int> optimoActual = coloreoActual;
    int cantItRandom = 0;
    string modo = "random";
    
    while (cantSinSol < CICLOS_MAX_SIN_MEJORAS || cantItRandom < 1000) {
        if (cantItRandom == 1000) {
            modo = "max";
        }
        int colorMax = *max_element(coloreoActual.begin(), coloreoActual.end());
        int colorMin = *min_element(coloreoActual.begin(), coloreoActual.end());
        vector<vector<int>> vecinos = vecindad(G.cantDeNodos(), criterio, colorMax, colorMin);
        quitarInvalidos(vecinos, G, coloreoActual);
        filtrarTabu_allColors(tabuList, vecinos, coloreoActual);
        if(!vecinos.empty()) {
            vector<int> maximo = buscarMaximo(vecinos, coloreoActual, H, modo);
            tabuList.push_back(maximo);

            if (impacto(H,maximo) > impacto(H,optimoActual)) {
                optimoActual = maximo;
                cantSinSol = 0;
            }
            else {
                cantSinSol++;
            }
            coloreoActual = maximo;
        } else{
            cantSinSol++;
        }

        cantItRandom++;
    }
    printSol(optimoActual, H);
    // cout << endl << boolalpha << estadoValido(G,optimoActual);
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

void hacerSwap(vector<int> &coloreoAuxiliar, const pair<int, int> &swapeo) {
    int aux = coloreoAuxiliar[swapeo.first];
    coloreoAuxiliar[swapeo.first] = coloreoAuxiliar[swapeo.second];
    coloreoAuxiliar[swapeo.second] = aux;
}

void borrarElementos(vector<int> &nodos_no_visitados, int cant_a_borrar) {
    while (cant_a_borrar > 0 && !nodos_no_visitados.empty()) {
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

vector<int> crear_vector_nodos(int n) {
    vector<int> todos_los_nodos(n, 0);
    //lleno todos_los_nodos con la pos i = i
    for (int i = 0; i < n; i++) {
        todos_los_nodos[i] = i;
    }
    return todos_los_nodos;
}

vector<pair<int, int>> generarSwapeosValidos(vector<int> &nodos_no_visitados, grafo &G, vector<pair<int, int>> &memoria,
                                             vector<int> &coloreo) {

    bool noHayOpciones = true;
    int intentos = 0;
    vector<pair<int, int>> arregloDeAdyacentes;
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


bool cambieOptimo(vector<pair<int, int>> &swapeosValidos, grafo &H, vector<int> &coloreo, int &mejorSol,
                  pair<int, int> &intercambio, grafo &G ) {

    bool cambie = false;
    vector<int> coloreoAuxiliar;
    vector<int> mejorColoreo = coloreo;

    for (pair<int, int> swapeo : swapeosValidos) {
        coloreoAuxiliar = coloreo;
            hacerSwap(coloreoAuxiliar, swapeo);
            if(estadoValido(G,coloreoAuxiliar)) {
                //impact se fija asi nomas el maximo impacto suponiendo que el coloreo ya es valido
                int impactoAuxiliar = impacto(H, coloreoAuxiliar);
                if (impactoAuxiliar > mejorSol) {
                    intercambio = swapeo;
                    mejorSol = impactoAuxiliar;
                    mejorColoreo = coloreoAuxiliar;
                    cambie = true;
                }
            }
    }
    if (coloreo != mejorColoreo)
        coloreo = mejorColoreo;

    return cambie;

}

void quitarInvalidos(vector<pair<int, int>> &vecinos, grafo &G, const vector<int> &coloreoActual) {
    auto it = vecinos.begin();
    while(it != vecinos.end()) {
        vector<int> posibleColoreo = coloreoActual;

        posibleColoreo[(*it).first] = coloreoActual[(*it).second] ;
        posibleColoreo[(*it).second] = coloreoActual[(*it).first];
        if (!estadoValido(G, posibleColoreo)) {
            it = vecinos.erase(it);
        }
        else it++;
    }
}


void tabu_search_vertices(grafo &G, grafo &H, int heuristica, float porcentajeNodos, int interacionesSinMejoras){
    PORCENTAJE_NODOS = porcentajeNodos;
    CICLOS_MAX_SIN_MEJORAS = interacionesSinMejoras; //variables con las que vamos a experimentar
    //Temas burocatricos
    noPrintear_Heuristica();
    CANT_NODOS_A_ELEJIR = (int) (G.cantDeNodos() * PORCENTAJE_NODOS);

    vector<int> coloreo;
    if(heuristica == 1){
        coloreo = heuristica_1(G, H);
    } else if(heuristica == 2) {
        coloreo = heuristica_2(G, H);
    }
    int impacto_input = impacto(H, coloreo);
    int n = G.cantDeNodos();

    vector<int> todos_los_nodos = crear_vector_nodos(n);
    vector<pair<int, int>> memoria;


    int cant_iteraciones = 0;
    int ciclos_sin_mejoras = 0;
    int mejorSol = impacto_input;
    vector<int> mejorColoreo = coloreo;
    while (ciclos_sin_mejoras < CICLOS_MAX_SIN_MEJORAS &&
           cant_iteraciones < MAX_CANT_ITERACIONES) { //faltaria agregar el tiempo (nosPasamosDeTiempo)

        vector<int> nodos_no_visitados = todos_los_nodos;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle(nodos_no_visitados.begin(), nodos_no_visitados.end(), std::default_random_engine(seed));

        //Creo Swapeos, eliminando los que estan en la lista tabu y los que producen coloreos invalidos
        vector<pair<int, int>> swapeosValidos = generarSwapeosValidos(nodos_no_visitados, G, memoria, coloreo);

        if (swapeosValidos.size() != 0) {

            //Busca el swap mas optimo posible para cambiar coloreo. Si no hay uno mejor, lo cambia por un intercambio cualquiera.
            pair<int, int> intercambio;
            if (cambieOptimo(swapeosValidos, H, coloreo, mejorSol, intercambio,G)) {
                mejorColoreo = coloreo;
                memoria.push_back(intercambio);
                ciclos_sin_mejoras = 0;
            } else {
                ciclos_sin_mejoras++;
                //hacerSwap(coloreo, swapeosValidos[0]);
                //memoria.push_back(swapeosValidos[0]);
            }
        } else ciclos_sin_mejoras++;
        cant_iteraciones++;
    }
    printSol(mejorColoreo, H);


}

