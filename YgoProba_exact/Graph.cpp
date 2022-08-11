#include "Graph.h"
#include <algorithm>


Graph::Graph(const std::vector<Vertex*>& v, const std::vector<Edge*> e, const std::vector<Edge*> ae):Vertex(ae) {
	this->vertices = v;
	this->edges = e;
}

Vertex* Graph::simplify() {
	if (this->vertices.size() > 1) return NULL;
	Node* n = (Node*)this->vertices[0];
	return  (Vertex*)n;
}

void Graph::simplifyAll() {
	Vertex* tmp;
	for (int i = 0; i < vertices.size(); i++) {
		if (tmp = vertices[i]->simplify()) {
			for (Edge* e : vertices[i]->getEdges()) {
				e->Vswap(vertices[i], tmp);
			}
			delete(vertices[i]);
			vertices[i] = tmp;
		}
	}
}


std::vector<Edge*> Graph::merge(Edge* E) {
	Vertex* V1, * V2;
	E->getEquivalentNodes(V1, V2);
	Node tmp = (*((Node*)V1)) * (*((Node*)V1));
	Vertex* Vm =(Vertex*) new Node(tmp);
	V1->getEdges().erase(std::find(V1->getEdges().begin(), V1->getEdges().end(), E));
	V2->getEdges().erase(std::find(V2->getEdges().begin(), V2->getEdges().end(), E));
	this->edges.erase(std::find(this->edges.begin(), this->edges.end(), E));
	for (Edge* e : V1->getEdges())
		e->Vswap(V1, Vm);
	for (Edge* e : V2->getEdges())
		e->Vswap(V2, Vm);
	std::vector<Edge*> newEdge;
	std::set_union(V1->getEdges().begin(), V1->getEdges().end(), V2->getEdges().begin(), V2->getEdges().end(), newEdge);
	Vm->setEdges(newEdge);
	delete(V1);
	delete(V2);

	return newEdge;
}

void Graph::mergeAll() {
	std::vector<Edge*> fresh;
	for (Edge* e : this->edges) {
		std::vector<Edge*> tmp = this->merge(e);
		std::set_union(fresh.begin(), fresh.end(), tmp.begin(), tmp.end(), fresh);
	}
	this->edges = fresh;
}