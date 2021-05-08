#include"caixeiro.cpp"
#include<cmath>
#include<chrono>

struct Ponto{
    double x;
    double y;

    //Calcula a distância entre o ponto referido e um ponto p parametrizado.
    double distancia(const Ponto& p){
        //Função que calcula a hipotenusa de dois pontos:
        return std::hypot((p.x - x), (p.y - y));
    }//end of distancia
};//end of Ponto

int main(){
    int vertices;
    //Obtem a quantidade de vértices do grafo:
    std::cin>>vertices;

    std::vector<Ponto> pontos;
    Ponto p;

    //Obtem todos as posições dos vértices do grafo:
    for(int i = 0; i < vertices; i++){
        std::cin>>p.x>>p.y;
        pontos.push_back(p);
    }//end of for

    Grafo g(vertices);

    double dist;

    //Gera o grafo completo.
    for(int i = 0; i < pontos.size(); i++){
        for(int j = i+1; j < pontos.size(); j++){
            //Calcula a distância entre o ponto i e o ponto j
            dist = pontos[i].distancia(pontos[j]);
            //Insere a aresta i-j e j-i no grafo:
            g.inserirAresta(j, i, dist);
            g.inserirAresta(i, j, dist);
        }//end of for
    }//end of for

    Caixeiro c(g);

    std::cout<<"Tempos de execução: "<<std::endl;

    for(int i = 0; i < 100; i++){
        auto inicio = std::chrono::high_resolution_clock::now();

        //Calcula a distância do menor caminho do caixeiro viajante:
        c.viajar();
        auto fim = std::chrono::high_resolution_clock::now();

        double tempo = std::chrono::duration<double, std::chrono::seconds::period>(fim - inicio).count();

        std::cout<<tempo<<std::endl;
    }//end of for

    std::cout<<"========================="<<std::endl;

    std::cout<<"Valor do caminho: "<<c.getViagem().peso<<std::endl;

    std::cout<<"Caminho: "<<std::endl;
    c.printarViagem();

    return 0;
}//end of main