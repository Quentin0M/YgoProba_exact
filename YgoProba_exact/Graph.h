#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include "Vertex.h"
#include "Node.h"
#include "Edge.h"
#include <vector>

class Graph: public Vertex
{
private:
	std::vector<Vertex*> vertices;
	std::vector<Edge*> edges;
public:
	Graph(const std::vector<Vertex*>& v,const std::vector<Edge*> e, const std::vector<Edge*> ae);

	std::vector<Edge*> getEdges() { Vertex::getEdges(); }
	std::vector<Vertex*> getVertices() { return this->vertices; }

	//function that is used to convert a hypernode of size 1 into a regular node
	Vertex* simplify();
	void simplifyAll();

	//functions that merge nodes and simplify the graph
	std::vector<Edge*> merge(Edge*);
	void mergeAll();

	//functions that expand the graph to the next draw
	void expand();

};


#endif // !GRAPH_H
