#include <iostream>
#include <list>
#include <vector>
class pair{
public :
    pair(int a,int b) : adyacente(a),peso(b) {}
    int adyacente;
    int peso;
};

class grafo{

public:
    int numerito;
    int cantDeNodos(){return _cantNodos ;}
    int sizeVector(){return relaciones.size();}
    grafo(int nodos) : _cantNodos(nodos){
            int cant_relaciones;
            int src;
            int dst;
            int peso;
            relaciones = std::vector<std::vector<pair>> (_cantNodos);
            std::cout << "Ingrese cantidad de relaciones" << std::endl;
            std::cin >> cant_relaciones;
            std::cout << "Vaya ingresandolas de forma v1 v2 e" << std::endl;
            for(int i = 0 ; i < cant_relaciones ; i++){
                std::cin >> src >> dst >> peso;
                relaciones[src].push_back(pair(dst,peso));
                relaciones[dst].push_back(pair(src,peso));
            }


    }
    void mostrarAdyacencia(){
        for( std::vector<pair> v : relaciones){
            std::cout << "[";
            for( pair p : v){
                std::cout << p.adyacente << ",";
            }
            std::cout << "]" << std::endl ;
        }

    }
private:
    int _cantNodos;
    std::vector<std::vector<pair>> relaciones;
};
int main() {
    int cant_vertices;
    std::cin >> cant_vertices;
    grafo grafito = grafo(cant_vertices);
    grafito.cantDeNodos();
    grafito.mostrarAdyacencia();
    std::list<pair> listita;
    std::cout << grafito.sizeVector() << std::endl;

    return 0;
}
