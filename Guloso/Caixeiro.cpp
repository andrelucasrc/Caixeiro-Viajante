#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
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
int main() {
    int N, X, Y;
    std::cin >> N;
    std::vector<Vertice> grafo;
    for (int i = 0; i < N; i++) {
        std::cin >> X;
        std::cin >> Y;
        grafo.push_back(Vertice(X, Y));
    }
    std::vector<int> refs,menorCaminho;
    double soma = 0, menor = 1000000000;
    for (int i = 1; i < N; i++) {
        refs.push_back(i);
    }
    do {
        soma = 0;
        soma += grafo[0].distance(grafo[refs[0]]);
        for (int i = 0; i < N-2; i++) soma += grafo[refs[i]].distance(grafo[refs[i+1]]);
        soma += grafo[refs[refs.size()-1]].distance(grafo[0]);
        if (soma < menor) {
            menor = soma;
            menorCaminho = refs;
        }
    } while (std::next_permutation(refs.begin(),refs.end()));
    std::cout << std::fixed << std::setprecision(2) << menor << std::endl;
    std::cout << "1 ";
    for (int i = 0; i < N-1; i++) {
        std::cout << menorCaminho[i]+1 << " ";
    }
    return 0;
}