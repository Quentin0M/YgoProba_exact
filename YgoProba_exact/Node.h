#ifndef NODE_H
#define NODE_H

#pragma once
#include "Vertex.h"
#include "Graph.h"
#include <vector>
class Node: public Vertex
{
private:

	std::vector<int> weights; //remaining weights of successes
	std::vector<int> colors; // list of all colors of success
	int N; //remaining balls in the urn
	int h = 0; //size of the hand so far
	int sumw; // number of remaining colors in the urn
	double P; // probability of the leaf(or combined leaves)
	int hash = 0;

	

public:
	Node(const Node&);
	Node(const std::vector<int>&, const std::vector<Edge*>& e); // used to create a new node with only weights
	Node(const std::vector<int>&, const int&, const double&, const std::vector<Edge*>& e); // probably unused
	Node(const std::vector<int>&, std::vector<int>&, const int&, const int&, const int&, const double&,const int&, const std::vector<Edge*>& e); //used to copy another node

	std::vector<Edge*> getEdges() ;
	void setEdges(const std::vector<Edge*>& e) { Vertex::setEdges(e); }

	double Pn() { return this->P; }
	bool isSuccess;

	void draw(int); //draws a ball (index of the success or -1)
	Vertex* convert(); //expands the node into a graph by drawing as many colors as possible.

	Node operator=(const Node&);
	Node operator*(const Node&); //combines 2 nodes with equivalent outcome

	friend bool operator==(const Node& a, const Node& b) {
		return (a.weights == b.weights) && (a.h == b.h);
	}
};


#endif // !NODE_H
