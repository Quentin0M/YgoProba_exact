#pragma once
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include <vector>
#include <algorithm>
#include <functional>
#include<iostream>

class Edge;
class Vertex;
class Node: public Vertex
{
private:

	std::vector<int> weights; //remaining weights of successes
	std::vector<int> colors; // list of all colors of success
	int N; //remaining balls in the urn
	int h = 0; //size of the hand so far
	int sumw; // number of remaining colors in the urn
	double P=1; // probability of the leaf(or combined leaves)
	int hash = 0;

	

public:

	static std::vector<int> obj; //objective vector
	static int samplesize;

	Node(const Node&);
	~Node() {};
	Node(int n, const std::vector<int>& w, std::vector<int> obj, int ss); // used to create the first node
	Node(const std::vector<int>& w, const std::vector<Edge*>& e, std::vector<int> obj,int ss); // used to create the first node
	Node(const std::vector<int>&, const int&, const double&, const std::vector<Edge*>& e); // probably unused
	Node(const std::vector<int>&, std::vector<int>&, const int&, const int&, const int&, const double&,const int&, const std::vector<Edge*>& e); //used to copy another node

	std::vector<Edge*> getEdges() ;
	void setEdges(const std::vector<Edge*>& e);
	std::vector<int> getColors() { return this->colors; }
	double Pn() { return this->P; }
	bool isSuccess();
	bool isdeadend();

	//void test() { //std::cout << "test\n"; }

	void draw(int); //draws a ball (index of the success or -1)
	Vertex* convert(); //expands the node into a graph by drawing as many colors as possible.

	std::vector<Vertex*> getVertices();

	Node operator=(const Node&);
	Node operator*(const Node&); //combines 2 nodes with equivalent outcome

	friend bool operator==(const Node& a, const Node& b) {
		return (a.colors == b.colors) && (a.h == b.h);
	}
};

