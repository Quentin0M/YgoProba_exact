
#pragma once
#include "Vertex.h"
#include "Node.h"
#include "Edge.h"
#include <vector>

class Edge;
class Vertex;
class Graph: public Vertex
{
private:
	//std::vector<Vertex*> vertices;
	std::vector<Edge*> edges;
	double P = 0;

	bool flag = false;
public:
	//Graph(const std::vector<Vertex*> v,const std::vector<Edge*> e, const std::vector<Edge*> ae);
	Graph(const std::vector<Vertex*,std::allocator<Vertex*>> v, const std::vector<Edge*,std::allocator<Edge*>> e, const std::vector<Edge*,std::allocator<Edge*>> ae);

	std::vector<Edge*> getEdges();
	std::vector<Vertex*> getVertices();
	std::vector<Edge*> getinneredges() { return this->edges; }

	//function that is used to convert a hypernode of size 1 into a regular node
	Vertex* simplify();
	void simplifyAll();
	void simplifyAll(std::vector<Vertex*>);

	//functions that merge nodes and simplify the graph
	std::vector<Edge*> merge(Edge*);
	void mergeAll();

	//functions that expand the graph to the next draw
	void expand();

	void setP(double p) { this->P = p; }
	double getP() { return this->P; }

	bool isEmpty() { return vertices.empty(); }
	bool checkEdge(Edge*e);

	void removeinneredge(Edge*);
	void removeVertex(Vertex*);

};

