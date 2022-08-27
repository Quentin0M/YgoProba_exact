
#pragma once
#include "Vertex.h"
#include <iostream>

class Vertex;
class Edge
{
private:
	Vertex* V1=NULL;
	Vertex* V2=NULL;
	std::vector<Vertex*> containers;
	int hash=0;

public:
	Edge() {}
	Edge(Vertex* V1, Vertex* V2, const int& h);
	void Vswap(Vertex* oldV, Vertex* newV);
	Vertex* Other(Vertex*);
	void getEquivalentNodes(Vertex** v1, Vertex** v2);
	void selfdestruct();
	Vertex* getV1() { return this->V1; }
	Vertex* getV2() { return this->V2; }
	bool isMinimal();
	std::string toString();

	std::vector<Vertex*> getContainers();
};

