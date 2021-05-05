#include <vector>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <limits>
#define infinity std::numeric_limits<double>::infinity()
/*
ALGORITMO BRANCH AND BOUND PARA O PROBLEMA DO CAXEIRO VIAJANTE
André Lucas Ribeiro Costa - 666400
Pedro Oliveira Simões - 654068
Complexidade:
*/

/*
    Estrutura de Nodo para realizar a logica branch and bound
    Cada nodo representa um passo no caminho do caxeiro a ser descoberto
    Nodos contem um vetor de nodos filhos, uma matriz da adjacencia, um vetor que 
        indica o caminho percorrido no grafo para chegar neste nodo e o custo do caminho ate
        o proprio
*/
struct Node {
    int id, idVertice;
    std::vector<Node*> filhos;
    std::vector<double> matriz;
    std::vector<int> caminho;
    struct Node* pai;
    bool folha;
    double custo;
    Node() = default;
    Node(int Id, int IdV);
    Node(int Id, int IdV, std::vector<int>Caminho, Node* Pai);
};
Node::Node(int Id, int IdV) : id(Id), idVertice(IdV) {
    this->folha = true;
}
Node::Node(int Id, int IdV, std::vector<int>Caminho, Node* Pai) : id(Id), idVertice(IdV) {
    this->folha = true;
    this->pai = Pai;
    this->caminho = Caminho;
}
/*
    Estrutura de vertice para criar o grafo a partir de entrada fornecida
    Guarda o vertice com sua cordenada(x,y)
    Para este exemplo, serve mais como abstracao, nao foi tao necessario quanto nos outros
        problemas
*/
struct Vertice {
    int x;
    int y;
    Vertice() = default;
    Vertice(int x, int y);
    double distance(Vertice V) {
        return std::sqrt((std::pow(this->x - V.x, 2) + std::pow(this->y - V.y, 2)));
    }
};
Vertice::Vertice(int x, int y) : x(x), y(y) {}

bool contains(std::vector<int> caminho, int buscado) {
    int i = 0;
    bool resp = false;
    while (i < (int)caminho.size() && !resp) {
        if (caminho[i] == buscado) resp = true;
        i++;
    }
    return resp;
}

/*
    Efetua a reducao da matriz de adjacencia fornecida, deixando pelo menos
    um zero em todas as linhas e colunas da matriz.
    Colunas e linhas com infinito sao ignoradas
*/
double reduceMatrix(std::vector<double>& matriz) {
    double valorReducao = 0, menor = 0;
    //loop for para reduzir as linhas
    for (int i = 0; i < N; i++) {
        menor = infinity;
        for (int j = 0; j < N; j++) {
            if (matriz[(i * N) + j] < menor) menor = matriz[(i * N) + j];
        }
        if (menor == infinity) menor = 0;
        for (int j = 0; j < N; j++) {
            if (matriz[(i * N) + j] != infinity) matriz[(i * N) + j] -= menor;
        }
        valorReducao += menor;
    }
    //loop for para reduzir as colunas
    for (int i = 0; i < N; i++) {
        menor = infinity;
        for (int j = 0; j < N; j++) {
            if (matriz[(j * N) + i] < menor) menor = matriz[(j * N) + i];
        }
        if (menor == infinity) menor = 0;
        for (int j = 0; j < N; j++) {
            if (matriz[(j * N) + i] != infinity) matriz[(j * N) + i] -= menor;
        }
        valorReducao += menor;
    }
    return valorReducao;
}

double menorCustoSearch = infinity;
Node* menorSearch;
void searchMinimum(Node* node) {
    if (node->folha == true) {
        if (node->custo < menorCustoSearch) {
            menorCustoSearch = node->custo;
            menorSearch = node;
        }
    }else for (int i = 0; i < node->filhos.size(); i++) {
        searchMinimum(node->filhos[i]);
    }
}

/*
    Funcao de expansao de um nodo para encontrar o caminho do caxeiro
    Checa-se o caminho percorrido ate o nodo a ser expandido para ver quais
        vertices ainda sao elegiveis para continuar o caminho
    É criado um filho para cada vertice elegivel
    Cada filho recebe um custo de acordo com a matriz de adjacencia do pai
*/
void expand(Node* node) {
    if (node->caminho.size() < N && node->folha == true) {
        node->folha = false;
        for (int i = 0; i < N; i++) {
            if (!contains(node->caminho, i)) {
                Node* novo = new Node(idNodes, i, node->caminho, node);
                novo->caminho.push_back(i);
                novo->matriz = node->matriz;

                //Se a ligacao é do vertice A para o B, linha A e coluna B recebem infinito
                for (int j = 0; j < N; j++) {
                    novo->matriz[(N * node->idVertice) + j] = infinity;
                    novo->matriz[(N * j) + novo->idVertice] = infinity;
                }

                //ligacao de B para A tambem recebe infinito
                novo->matriz[(N * novo->idVertice) + node->idVertice] = infinity;

                //Custo do nodo filho = custo do pai + W(Pai,Filho) + custo de reducao da matriz
                novo->custo = node->custo + matrizRaiz[(N * node->idVertice) + novo->idVertice] + reduceMatrix(novo->matriz);
                node->filhos.push_back(novo);
                idNodes++;
            }
        }
    }
}
int N, idNodes;
std::vector<double> matrizRaiz;
int main() {
    idNodes = 0;
    int X, Y;
    std::cin >> N;
    std::vector<Vertice> grafo;
    std::vector<double> matrizAdj(N * N, infinity);
    //Criacao do grafo a partir da entrada
    for (int i = 0; i < N; i++) {
        std::cin >> X;
        std::cin >> Y;
        grafo.push_back(Vertice(X, Y));
    }
    //Criacao da matriz de adjacencia do grafo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                matrizAdj[(i * N) + j] = grafo[i].distance(grafo[j]);
            }
            else matrizAdj[(i * N) + j] = infinity;
        }
    }
    double custo = reduceMatrix(matrizAdj);
    matrizRaiz = matrizAdj;

    //Criacao da raiz da arvore com o vertice 0 de incial
    Node* raiz = new Node(idNodes, 0);
    idNodes++;
    raiz->custo = custo;
    raiz->matriz = matrizRaiz;
    raiz->caminho.push_back(0);


    
    expand(raiz);
    menorCustoSearch = infinity;
    searchMinimum(raiz);
    bool done = false;
    double menorCaminho = 0;
    /*
        Loop While para realizar a expansao da arvore ate encontrar o menor caminho
        Procura-se o vertice com menor custo(que seja uma folha), expande-se o mesmo, procura-se o menor
            custo novamente.
        Quando o vertice de menor custo tiver um caminho completo, o loop acaba.
    */
    while (!done) {
        if (menorSearch->caminho.size() == N) {
            done = true;
            for (int i = 0; i < menorSearch->caminho.size() - 1; i++) {
                menorCaminho += grafo[menorSearch->caminho[i]].distance(grafo[menorSearch->caminho[i + 1]]);
            }
            menorCaminho += grafo[menorSearch->caminho[menorSearch->caminho.size() - 1]].distance(grafo[menorSearch->caminho[0]]);
            std::cout << std::fixed << std::setprecision(2) << menorCaminho <<", "<< menorSearch->custo << std::endl;
            for (int i = 0; i < menorSearch->caminho.size(); i++) {
                std::cout << menorSearch->caminho[i] + 1 << " ";
            }
            menorCaminho += grafo[menorSearch->caminho[menorSearch->caminho.size() - 1]].distance(grafo[menorSearch->caminho[0]]);
        }
        else {
            menorCustoSearch = infinity;
            expand(menorSearch);
            searchMinimum(raiz);
        }
    }

    return 0;
}
