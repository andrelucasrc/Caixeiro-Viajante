#include"caixeiro.hpp"

//Função de DEBUG
//Printa a matriz de par de int e double.
void printarVetorDeVetor(const std::vector<std::vector<std::pair<int, double>>>& vec){
    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec[i].size(); j++){
            std::cout<<vec[i][j].first<<","<<vec[i][j].second<<" ";
        }//end of for
        std::cout<<std::endl;
    }//end of for
}//end of printarVetorDeVetor

void printarVetorDeVetor(const std::vector<std::vector<int>>& vec){
    for(int i = 0; i < vec.size(); i++){
        std::cout<<"Tamanho do vetor: "<<vec[i].size()<<std::endl;
        for(int j = 0; j < vec[i].size(); j++){
            std::cout<<vec[i][j]<<" ";
        }//end of for
        std::cout<<std::endl;
    }//end of for
}//end of printarVetorDeVetor

void printarVetorDeVetor(const std::vector<std::vector<double>>& vec){
    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec[i].size(); j++){
            std::cout<<vec[i][j]<<" ";
        }//end of for
        std::cout<<std::endl;
    }//end of for
}//end of printarVetorDeVetor

void printarVetorDeVetor(const std::vector<std::vector<Melhor>>& vec){
    for(int i = 0; i < vec.size(); i++){
        std::cout<<"Tamanho do vetor: "<<vec[i].size()<<std::endl;
        for(int j = 0; j < vec[i].size(); j++){
            std::cout<<vec[i][j].peso;
            if(i > 0){
                std::cout<<","<<vec[i][j].caminho.back()+1;
            }
            std::cout<<" ";
        }//end of for
        std::cout<<std::endl;
    }//end of for
}//end of printarVetorDeVetor

void printarVetor(const std::vector<int>& vec){
    for(int i = 0; i < vec.size(); i++){
        std::cout<<vec[i]<<" ";
    }//end of for
    std::cout<<std::endl;
}//end of printarVetor

Caixeiro::Caixeiro(const Grafo& grafo)
    :
    p_grafo(grafo)
{
}//end of contructor

void Caixeiro::viajar(){
    std::vector<int> disponiveis;
    for(int i = 1; i < p_grafo.size(); i++){
        disponiveis.push_back(i);
    }//end of for

    p_melhor = viajar(0, disponiveis);
}//end of viajar

Melhor Caixeiro::viajar(int atual, const std::vector<int>& disponiveis){
    Melhor melhor = { std::vector<int>(), p_grafo.at(atual).at(0)};

    //Verifica se existe algum vértice que necessita ser verificado:
    if(disponiveis.size() != 0){
        //Se existir algum vértice disponível,
        //inicializa o melhor caminho com o peso do primeiro subcaminho:
        melhor.caminho = disponiveis;
        //Remove o vértice atual do subcaminho:
        melhor.caminho.erase(
            std::find(melhor.caminho.begin(), melhor.caminho.end(), disponiveis[0])
        );

        //Obtem o caminho do primeiro vértice disponível,
        //através da árvore de recursividade:
        melhor = viajar(disponiveis[0], melhor.caminho);
        //Atualiza com o valor da aresta do primeiro vértice disponível até o vértice atual:
        melhor.peso += p_grafo.at(disponiveis[0]).at(atual);

        Melhor viagem;
        //Passar por todos os vértices disponíveis verificando qual o menor subcaminho dos vértices existentes:
        for(int i = 1; i < disponiveis.size(); i++){
            //Inicializa o novo caminho a ser verifica:
            viagem.caminho = disponiveis;
            //Remove o vértice sendo atualmente verificado do caminho:
            viagem.caminho.erase(
                std::find(viagem.caminho.begin(), viagem.caminho.end(), disponiveis[i])
            );

            //Obtem o peso do subcaminho do vértice atualmente verificado e o seu subcaminho,
            //através da árvore de recursividade:
            viagem = viajar(disponiveis[i], viagem.caminho);
            //Atualiza com o valor da aresta do atualmente verificado vértice disponível até o vértice atual:
            viagem.peso += p_grafo.at(disponiveis[i]).at(atual);

            //Verifica se o peso do vértice verificado é menor do que o peso do vértice salvo:
            if(viagem.peso < melhor.peso){
                melhor = viagem;
            }//end of if
        }//end of for
    }//end of if

    //Insere o vértice atual no caminho dos vértices visitados
    melhor.caminho.push_back(atual);

    return melhor;
}//end of viajar

Melhor Caixeiro::getViagem(){
    return p_melhor;
}//end of getViagem

void Caixeiro::printarViagem(){
    std::vector<int> viagem = p_melhor.caminho;

    for(int i = 0; i < viagem.size(); i++){
        std::cout<<viagem[i] + 1<<" ";
    }//end of for

    std::cout<<std::endl;
}//end of viagem