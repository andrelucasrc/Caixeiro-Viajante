#include <vector>
#include <iostream>

class Node {
public:
	int id, idVertice;
	std::vector<Node> filhos;
	Node pai;
	bool folha;
	double custo;
	public Node() = default;
	public Node(int id,int idV);
};
Node(int id, int idv) : id(id), idVertice(idV), folha(false){}