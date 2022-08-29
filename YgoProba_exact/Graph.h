
#pragma once
#include "Vertex.h"
#include "Node.h"
#include "Edge.h"
#include <vector>

class Edge;
//class Vertex;
class Graph: public Vertex
{
private:
	//std::vector<Vertex*> vertices;
	std::vector<Edge*> edges;
	long double proba = 0.L;

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

	void setP(long double p);
	long double getP() { return this->P; }
	long double getProba() { return this->proba; }
	void setProba(long double p) { this->proba = p; }

	bool isEmpty() { return vertices.empty(); }
	bool checkEdge(Edge*e);

	std::string typeCheck() { return "Graph"; }

	void removeinneredge(Edge*);
	void nullinneredge(Edge*);
	void removeVertex(Vertex*);

	std::string toString();

	// returns the edge connecting 2 vertices if they exist
	// or NULL otherwise
	Edge* tryGetEdge(Vertex*, Vertex*);


	// Returns a vector of a cycle including nodes equivalent to a node, given 2 nodes and 2 vertices (that are part of this and form a 2-cycle).
	// N1 is part of V1 and N2 is part of V2
	// Returns an empty vector if no cycle (bigger than 2) is found
	std::vector<Vertex*> tryCycle(Vertex* V1, Node* N1, Vertex* V2, Node* N2);

	void tryCycle(std::vector<Vertex*, std::allocator<Vertex*>>* outer, std::vector<Vertex*, std::allocator<Vertex*>>* inner);

};

