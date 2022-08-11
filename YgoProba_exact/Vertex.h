#pragma once
#ifndef VERTEX_H
#define	VERTEX_H

#include <vector>
#include "Edge.h"
class Vertex
{
private:
	std::vector<Edge*> attached_edges;
public:
	Vertex() {}
	Vertex(const Vertex& v) {
		this->attached_edges = v.attached_edges;
	}
	Vertex(const std::vector<Edge*>& e) { this->attached_edges = e; }
	void convert(){}
	std::vector<Edge*> getEdges() { return this->attached_edges; }
	void setEdges(const std::vector<Edge*>& e) { this->attached_edges = std::vector<Edge*>(e); }
	Vertex* simplify() { return NULL; }
	void wipeEdges() { this->attached_edges.clear(); }
};

#endif // !VERTEX_H


