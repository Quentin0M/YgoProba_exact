#include "Edge.h"
#include "Graph.h"
#include "Node.h"
#include "Node.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
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
	else {
					}
	if(A) A->removeEdge(this);
	if(B) B->addEdge(this);
	}

Vertex* Edge::Other(Vertex* v) {
	return (this->V1 == v ? this->V2 : this->V1);
}


void Edge::getEquivalentNodes(Vertex** v1, Vertex** v2) {
	Vertex* S = this->V1;
	Vertex* T = this->V2;
		if (!S && !T) throw new SnT_null_exception;
	if (!S) throw new S_null_exception;
	if (!T) throw new T_null_exception;
		if (S->getVertices().empty()) {
				S->getVertices().push_back(S);
	}
	if (T->getVertices().empty()) {
				T->getVertices().push_back(T);
	}
											//std::cout << "Successfully casted v1 and v2 into graphs" << std::endl;
	for (Vertex* v : S->getVertices() ) {
		Node* vn = (Node*)v;
		if (!v) continue;
		for (Vertex* w : T->getVertices()) {
			Node* wn = (Node*)w;
			if (!w) continue;
			if (vn->getColors() == wn->getColors()) {
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
	for (Vertex* g : this->containers)
		((Graph*)g)->removeinneredge(this);
		}

bool Edge::isMinimal() {
	return ((((Node*)this->getV1())->getColors().size()) && (((Node*)this->getV2())->getColors().size()));
}

std::string Edge::toString() {
	std::stringstream ss;
	ss       << ((((Node*)this->getV1())->toString() != "[]") ? ((Node*)this->getV1())->toString() : ((Graph*)this->getV1())->toString())
	<< "---" << ((((Node*)this->getV2())->toString() != "[]") ? ((Node*)this->getV2())->toString() : ((Graph*)this->getV2())->toString());
	return ss.str();
}

std::vector<Vertex*> Edge::getContainers() {
	return this->containers;
}