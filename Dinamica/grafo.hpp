#ifndef _GRAFO_HPP_
#define _GRAFO_HPP_

#include<iostream>
#include<vector>
#include<stdexcept>

class Grafo{
private:
    //Matriz de adjascência do grafo:
    std::vector<std::vector<double>> p_adjascencia;
public:
    Grafo(int n);

    //Insere uma nova aresta no grafo
    //A aresta inserida tem direção de x -> y
    void inserirAresta(int x, int y, double peso);

    //Retorna a matriz de adjascência do grafo:
    std::vector<std::vector<double>> getMatriz();

    //Retorna a linha x da matriz de adjascência:
    std::vector<double> at(int x);

    //Retorna o quantidade de vértices no grafo:
    size_t size();
};//end of class grafo

#endif