#include <vector>
#include <iostream>
#include <cmath>
#define infinity 2000000000
int N,idNodes;
std::vector<double> matrizRaiz;
struct Node {
    int id, idVertice;
    std::vector<Node> filhos;
    std::vector<double> matriz;
    std::vector<int> caminho;
    struct Node pai;
    bool folha;
    double custo;
    Node() = default;
    public Node(int id, int idV);
};
Node::Node(int id, int idv) : id(id), idVertice(idV) {}
Node::Node(int id, int idv, std::vector<int>caminho, Node pai) : id(id), idVertice(idV) folha(true){
    this->pai = pai;
    this->caminho = caminho;
}
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
bool contains(std::vector<int> caminho,int buscado) {
    int i = 0;
    bool resp = false;
    while (i < caminho.size() && !resp) {
        if (caminho[i] == buscando) resp = true;
        i++;
    }
    return resp;
}
void expand(Node& node) {
    if (node.folha == true) {
        node.folha = false;
        std::cout << "Node " << node.id << "id no longer a leaf node" << std::endl;
        for (int i = 0; i < N; i++) {
            if (!contains(node.caminho, i)) {
                Node novo(idNodes,i,node.caminho,node);
                novo.caminho.push_back(i);
                novo.custo = node.custo + matrizRaiz[(N * node.idVertice) + novo.idVertice] + reduceMatrix(novo.matriz);
                node.filhos.push_back(novo);
                std::cout << "Created node" << idNodes << ", representing path from vertices " 
                    << node.pai.idVertice << "to " << i << ", with cost " << novo.custo << std::endl;
                idNodes++;
            }
        }
    }
}
double reduceMatrix(std::vector<double>& matriz) {
    //std::vector<double> reducedMatrix = matriz;
    double valorReducao = 0, menor = 0;
    for (int i = 0; i < N; i++) {
        menor = infinity;
        for (int j = 0; j < N; j++) {
            if (matriz[(i * N) + j] < menor) menor = matriz[(i * N) + j];
        }
        for (int j = 0; j < N; j++) {
            if (matriz[(i * N) + j] != infinity) matriz[(i * N) + j] -= menor;
        }
        valorReducao += menor;
    }
    for (int i = 0; i < N; i++) {
        menor = infinity;
        for (int j = 0; j < N; j++) {
            if (matriz[(j * N) + i] < menor) menor = matriz[(j * N) + i];
        }
        for (int j = 0; j < N; j++) {
            if (matriz[(j * N) + i] != infinity) matriz[(j * N) + i] -= menor;
        }
        valorReducao += menor;
    }
    //std::cout << "cost: " << valorReducao << std::endl;
    return valorReducao;
}
int main() {
    idNodes = 0;
    int X, Y;
    std::cin >> N;
    std::vector<Vertice> grafo;
    std::vector<double> matrizAdj(N * N, infinity);
    for (int i = 0; i < N; i++) {
        std::cin >> X;
        std::cin >> Y;
        grafo.push_back(Vertice(X, Y));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                matrizAdj[(i * N) + j] = grafo[i].distance(grafo[j]);
            }
            else matrizAdj[(i * N) + j] = infinity;
            //std::cout << matrizAdj[(i * N) + j] << " ";
        }
    }
    double custo = reduceMatrix(matrizAdj);
    matrizRaiz = matrizAdj;
    Node raiz(idNodes, 0);
    idNodes++;
    raiz.custo = custo;
    raiz.matriz = matrizAdj;
    raiz.caminho.push_back(0);
    return 0;
}
