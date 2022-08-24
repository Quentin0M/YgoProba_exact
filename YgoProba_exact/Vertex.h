#pragma once

#include <vector>
#include <iostream>
#include "Edge.h"

class Edge;
class Vertex
{
private:
	//std::vector<Vertex*> _vertices;
	std::vector<Edge*> attached_edges;
protected:
	std::vector<Vertex*> vertices;
	long double P = 1.L;
public:
	Vertex();
	~Vertex();
	Vertex(const Vertex& v);
	//Vertex(const std::vector<Edge*>& e) { this->attached_edges = e; }
	Vertex(const std::vector<Edge*, std::allocator<Edge*>>& e);
	void convert();
	std::vector<Edge*> getEdges();
	void setEdges(const std::vector<Edge*>& e);
	void addEdge(Edge* e);
	Vertex* simplify();
	void wipeEdges();
	void removeEdge(Edge* e);

	bool checkEdge(Edge* e);


	std::string typeCheck() { return "Vertex"; }

	std::vector<int> getColors() { return std::vector<int>(); }

	std::vector<Vertex*> getVertices();

	void setP(long double p) { this->P = p; }

	long double getP() { return this->P; }

	std::string toString();

	bool isNode() { return this->vertices.back() == this; }
};

