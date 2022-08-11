#include "Edge.h"

Edge::Edge(Vertex* V1, Vertex* V2, const int& h,bool simple=true) {
	this->V1 = V1;
	this->V2 = V2;
	this->hash = h;
	this->simple = simple;
}

void Edge::Vswap(Vertex* A, Vertex* B) {
	(this->V1 == A ? this->V1 : this->V2) = B;
}

Vertex* Edge::Other(Vertex* v) {
	return (this->V1 == v ? this->V2 : this->V1);
}


void Edge::getEquivalentNodes(Vertex* v1, Vertex* v2) {
	for (Vertex* v : ((Graph*)v1)->getVertices() ) {
		for (Vertex* w : ((Graph*)v2)->getVertices()) {
			if (*((Node*)v) == *((Node*)w)) {
				v1 = v;
				v2 = w;
			}
		}
	}
}