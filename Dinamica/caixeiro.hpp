#ifndef _CAIXEIRO_HPP_
#define _CAIXEIRO_HPP_

#include"grafo.cpp"
#include<utility>
#include<algorithm>
#include<limits>

struct Melhor{
    std::vector<int> caminho;
    double peso;
};

/*
    Classe responsável por gerar o menor caminho possível que o caixeiro viajante pode passar,
    utilizando programação dinâmica.
    O algoritmo consiste em criar a árvore de recursividade do nível das folhas em direção a
    raíz, reutilizando os cálculos. Para isso básicamente é utilizado a seguinte fórmula:
    caminho(i, s) = min(aresta(i, k) + caminho(k, s - {k})) ∀ k ∈ s.
    Onde caminho representa o peso do menor caminho do vértice de "i" até o "s" vértices restantes;
    onde aresta representa o peso da aresta existente entre o vértice "i" até o "k"
    i representa o vértice atualmente o atual a ser verificado;
    s representa os possíveis vértices que o vértice i pode passar;
    k representa o vértice que será vértice que atualmente será verificado pelo caminho.

    O algoritmo não funciona corretamente caso o grafo enviado não seja completo.
    Para isso é necessário efetuar uma pequena alteração no código.
 */
class Caixeiro{
private:
    //Grafo de cidades e caminhos que o caixeiro pode passar.
    Grafo p_grafo;
    //Armazena os dados do melhor caminho existente no grafo atual.
    Melhor p_melhor;

    Melhor viajar(int vertice, const std::vector<int>& subset);
public:
    Caixeiro(const Grafo& grafo);

    //Calcula a distância do menor caminho do caixeiro viajante.
    void viajar();

    //Retorna os dados do melhor caminho
    Melhor getViagem();
    
    //Imprime o caminho percorrido pelo caixeiro viajante.
    void printarViagem();
};//end of Caixeiro

#endif