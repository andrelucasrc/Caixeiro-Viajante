#include <vector>
#include <iostream>
#include <cmath>
#define infinity 2000000000
int N;
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

std::vector<double> reduceMatrix(std::vector<double>& matriz) {
    N = 5;
    std::vector<double> reducedMatrix = matriz;
    double valorReducao = 0, menor = 0;
    for (int i = 0; i < N; i++) {
        menor = infinity;
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[(i * N) + j] < menor) menor = reducedMatrix[(i * N) + j];
        }
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[(i * N) + j] != infinity) reducedMatrix[(i * N) + j] -= menor;
        }
        valorReducao += menor;
    }
    for (int i = 0; i < N; i++) {
        menor = infinity;
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[(j * N) + i] < menor) menor = reducedMatrix[(j * N) + i];
        }
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[(j * N) + i] != infinity) reducedMatrix[(j * N) + i] -= menor;
        }
        valorReducao += menor;
    }
    std::cout << "cost: " << valorReducao << std::endl;
    return reducedMatrix;
}
int main() {
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
    reduceMatrix(matrizAdj);
    return 0;
}
