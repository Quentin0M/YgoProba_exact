#include "Edge.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>
#include "util.cpp"
#include"exceptions.h"

Edge::Edge(Vertex* V1, Vertex* V2, const int& h) {
	this->V1 = V1;
	this->V2 = V2;
	this->hash = h;
}

void Edge::Vswap(Vertex* A, Vertex* B) {
	//(this->V1 == A ? this->V1 : this->V2) = B;
	if (this->V1 == A)
		this->V1 = B;
	else if (this->V2 == A)
		this->V2 = B;
	else std::cout << "No valid target" << std::endl;
	if(A) A->removeEdge(this);
	if(B) B->addEdge(this);
}

Vertex* Edge::Other(Vertex* v) {
	return (this->V1 == v ? this->V2 : this->V1);
}


void Edge::getEquivalentNodes(Vertex** v1, Vertex** v2) {
	Vertex* S = this->V1;
	Vertex* T = this->V2;
	std::cout << "Entering GEN" << std::endl;
	if (!S && !T) throw new SnT_null_exception;
	if (!S) throw new S_null_exception;
	if (!T) throw new T_null_exception;
	std::cout << "Valid edge" << std::endl;
	std::vector<std::string> Snodes;
	std::vector<std::string> Tnodes;
	for (Vertex* v : S->getVertices())
		Snodes.push_back(vtos(((Node*)v)->getColors()));
	for (Vertex* v : T->getVertices())
		Tnodes.push_back(vtos(((Node*)v)->getColors()));
	std::cout << "S has " << S->getVertices().size() << " vertices" << std::endl;
	std::cout << " " << vtos(Snodes) << std::endl;
	std::cout << "T has " << T->getVertices().size() << " vertices" << std::endl;
	std::cout << " " << vtos(Tnodes)<<std::endl;
	//std::cout << "Successfully casted v1 and v2 into graphs" << std::endl;
	for (Vertex* v : S->getVertices() ) {
		Node* vn = (Node*)v;
		if (!v) continue;
		for (Vertex* w : T->getVertices()) {
			Node* wn = (Node*)w;
			if (!w) continue;
			if (vn->getColors() == wn->getColors()) {
				std::cout << "HERE!!!" << std::endl;
				*v1 = v;
				*v2 = w;
				return;
			}
		}
	}
}

void Edge::selfdestruct() {
	if(V1) this->V1->removeEdge(this);
	if(V2) this->V2->removeEdge(this);
	delete this;
}

bool Edge::isMinimal() {
	return ((this->V1->getVertices().size() == 1) && (this->V2->getVertices().size() == 1));
}