#include"grafo.hpp"

Grafo::Grafo(int size) :
    p_adjascencia(size, std::vector<double>(size))
{

}//end of constructor

void Grafo::inserirAresta(int x, int y, double peso){
    //Verifica se a aresta inserida é válida:
    if(x < 0 || x >= p_adjascencia.size() || y < 0 || y > p_adjascencia.size())
        std::invalid_argument("Erro ao inserir aresta, indice de inserção inválido.");

    p_adjascencia[x][y] = peso;
}//end of inserirAresta

std::vector<std::vector<double>> Grafo::getMatriz(){
    return p_adjascencia;
}//end of getMatriz

std::vector<double> Grafo::at(int x){
    //Verifica se a linha desejada existe na matriz:
    if(x < 0 || x >= p_adjascencia.size())
        std::invalid_argument("Erro ao obter valor, indice inválido.");

    return p_adjascencia[x];
}//end of get

size_t Grafo::size(){
    return p_adjascencia[0].size();
}//end of getSize