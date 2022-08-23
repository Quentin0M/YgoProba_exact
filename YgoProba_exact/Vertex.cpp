#include "Vertex.h"
#include <iostream>

#include "util.cpp"

Vertex::Vertex() {}
Vertex::~Vertex() { for (Edge* e : this->attached_edges) delete e; }
Vertex::Vertex(const Vertex& v) {
	this->attached_edges = v.attached_edges;
}
//Vertex(const std::vector<Edge*>& e) { this->attached_edges = e; }
Vertex::Vertex(const std::vector<Edge*, std::allocator<Edge*>>& e) { this->attached_edges = std::vector<Edge*>(e); }
void Vertex::convert() {}
std::vector<Edge*> Vertex::getEdges() { return this->attached_edges; }
void Vertex::setEdges(const std::vector<Edge*>& e) { this->attached_edges = std::vector<Edge*>(e); }
Vertex* Vertex::simplify() { throw(new std::exception); }
void Vertex::wipeEdges() { this->attached_edges.clear(); }


std::vector<Vertex*> Vertex::getVertices() {
	//std::cout << "Problem" << std::endl;
	return this->vertices; 
}

void Vertex::addEdge(Edge* e) {
	this->attached_edges.push_back(e);
}

void Vertex::removeEdge(Edge* edge) {
	for (int i = 0; i < this->attached_edges.size(); i++) {
		if (this->attached_edges[i] == edge) {
			this->attached_edges.erase(this->attached_edges.begin() + i);
			return;
		}
	}
}

bool Vertex::checkEdge(Edge* e) {
	if(e)
		for (Edge* edge : this->attached_edges)
			if (edge && (edge == e))
				return true;
	return false;
}

std::string Vertex::toString() {
	std::stringstream ss;
	bool first = true;
	ss << "[V";
	for (Vertex* v : this->vertices) {
		if (!first) ss << ", ";
		ss << v->toString();
		first = false;
	}
	ss << "]";
	return ss.str();
}