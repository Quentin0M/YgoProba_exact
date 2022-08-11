#ifndef EDGE_H
#define EDGE_H


#pragma once
#include "Vertex.h"
#include "Graph.h"
#include"Node.h"
class Edge
{
private:
	Vertex* V1;
	Vertex* V2;
	int hash;
	bool simple;

public:
	Edge(Vertex* V1, Vertex* V2, const int& h,bool simple = true);
	void Vswap(Vertex* oldV, Vertex* newV);
	Vertex* Other(Vertex*);
	void simplify() { this->simple = true; }
	bool isSimple() { return this->simple; }
	void getEquivalentNodes(Vertex* v1, Vertex* v2);
};


#endif // !EDGE_H
