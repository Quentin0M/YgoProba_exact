#include "Graph.h"
#include <algorithm>
#include <iostream>

#include "util.cpp"



/*
Graph::Graph(const std::vector<Vertex*> v, const std::vector<Edge*> e, const std::vector<Edge*> ae):Vertex(ae) {
	this->vertices = v;
	this->edges = e;
}
*/
Graph::Graph(const std::vector<Vertex*, std::allocator<Vertex*>> v, const std::vector<Edge*, std::allocator<Edge*>> e, const std::vector<Edge*, std::allocator<Edge*>> ae) :Vertex(ae) {
	this->vertices = std::vector<Vertex*>(v);
	this->edges = std::vector<Edge*>(e);
}

Vertex* Graph::simplify() {
	std::cout << "  Entered simplify" << std::endl;
	if (this->vertices.size() != 1) {
		std::cout << "not an atom (size=" << this->vertices.size() <<")" << std::endl;
		return NULL;
	}
	if (this->vertices[0] == this) {
		std::cout << "Already a node" << std::endl;
	}
	return this->vertices[0];
	
}

void Graph::simplifyAll() {
	std::cout << "Entering simplifyAll" << std::endl;
	if (this->vertices.size() == 1) {
		Graph* G = (Graph*)(this->vertices.back());
		std::cout << "only 1 subgraph with " << G->getVertices().size() << " vertices and " << G->getinneredges().size() << " edges" << std::endl;
		Graph* tmp = (Graph*)(this->vertices[0]);
		this->vertices = tmp->getVertices();
		this->edges = tmp->getinneredges();
		return;
	}

}

void Graph::simplifyAll(std::vector<Vertex*> old) {

	while (!this->flag) {}
	std::cout << "Entering simplifyAll" << std::endl;

	this->flag = false;
	
	if (this->vertices.size() == 1) {
		Graph* G = (Graph*)(this->vertices.back());
		std::cout << "only 1 subgraph with " << G->getVertices().size() << " vertices and " << G->getinneredges().size() << " edges" << std::endl;
		Graph* tmp = (Graph*)(this->vertices[0]);
		this->vertices = tmp->getVertices();
		this->edges = tmp->getinneredges();
	}

	for (Vertex* v : old) {
		try {
			Vertex* tmp = ((Graph*)v)->simplify();
			for (Edge* e : v->getEdges()) {
				e->Vswap(v, tmp);
			}
			this->removeVertex(v);
			this->vertices.push_back(tmp);
		}
		catch (...) {
			std::cout << "  Error" << std::endl;
			continue;
		}
	}
	
}

std::vector<Edge*> Graph::merge(Edge* E) {
	Vertex* V1=NULL;
	Vertex* V2=NULL;
	Vertex* n;
	
	std::cout << "Entering merge"<<std::endl;

	E->getEquivalentNodes(&V1, &V2);

	if (!V1) {
		E->getV1()->removeEdge(E);
		E->getV2()->removeEdge(E);
		//this->removeinneredge(E);
		//E->selfdestruct();
		
		if (n = ((Graph*)E->getV1())->simplify()) {
			this->removeVertex(E->getV1());
			this->vertices.push_back(n);
			for (Edge* e : E->getV1()->getEdges())
				e->Vswap(E->getV1(), n);
		}
		if (E->getV1()->getVertices().empty()) {
			for (Edge* e : E->getV1()->getEdges()) {
				//this->nullinneredge(e);
				e->selfdestruct();
			}
			this->removeVertex(E->getV1());
		}

		((Graph*)E->getV2())->removeVertex(V2);
		if (n = ((Graph*)E->getV2())->simplify()) {
			this->removeVertex(E->getV2());
			this->vertices.push_back(n);
			for (Edge* e : E->getV2()->getEdges())
				e->Vswap(E->getV2(), n);
		}
		if (E->getV2()->getVertices().empty()) {
			for (Edge* e : E->getV2()->getEdges()) {
				//this->nullinneredge(e);
				e->selfdestruct();
			}
			this->removeVertex(E->getV2());
		}

		E->selfdestruct();

		return std::vector<Edge*>();
	}

	if (n = ((Graph*)E->getV1())->simplify()) {
		this->removeVertex(E->getV1());
		this->vertices.push_back(n);
		for (Edge* e : E->getV1()->getEdges())
			e->Vswap(E->getV1(), n);
		E->Vswap(E->getV1(), n);
		V1 = n;
	}

	if (n = ((Graph*)E->getV2())->simplify()) {
		this->removeVertex(E->getV2());
		this->vertices.push_back(n);
		for (Edge* e : E->getV2()->getEdges())
			e->Vswap(E->getV2(), n);
		E->Vswap(E->getV2(), n);
		V2 = n;
	}

	std::cout << "found nodes " << (V1 == V2) << std::endl;

	std::cout << "V1: colors = " << vtos(((Node*)V1)->getColors()) << " P=" << ((Node*)V1)->Pn() << std::endl;
	std::cout << "V2: colors = " << vtos(((Node*)V2)->getColors()) << " P=" << ((Node*)V2)->Pn() << std::endl;

	Node tmp = (*((Node*)V1)) * (*((Node*)V2));
	Vertex* Vm =(Vertex*) new Node(tmp);
	E->getV1()->removeEdge(E);
	E->getV2()->removeEdge(E);
	//this->removeinneredge(E);
	//E->selfdestruct();
	
	/*std::cout << "V1's edges:\n";
	for (Edge* e : V1->getEdges()) {
		std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	}*/
	for (Edge* e : V1->getEdges())
		e->Vswap(V1, Vm);

	/*std::cout << "V2's edges:\n";
	for (Edge* e : V2->getEdges()) {
		std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	}*/
	for (Edge* e : V2->getEdges())
		e->Vswap(V2, Vm);


	std::cout << "Vm: colors = " << vtos(((Node*)Vm)->getColors()) << " P=" << ((Node*)Vm)->Pn() << " " << ((Node*)Vm)->getEdges().size()<< " outgoing edges " << Vm->getEdges().size() << std::endl;
		
	((Graph*)E->getV1())->removeVertex(V1);
	if (n = ((Graph*)E->getV1())->simplify()) {
		this->removeVertex(E->getV1());
		this->vertices.push_back(n);
		for (Edge* e : E->getV1()->getEdges())
			e->Vswap(E->getV1(), n);
	}
	if (E->getV1()->getVertices().empty()) {
		for (Edge* e : E->getV1()->getEdges()) {
			std::cout << "AAAAAAAAAAA" << std::endl;
			//this->nullinneredge(e);
			e->selfdestruct();
		}
		this->removeVertex(E->getV1());
	}

	((Graph*)E->getV2())->removeVertex(V2);
	if (n = ((Graph*)E->getV2())->simplify()) {
		this->removeVertex(E->getV2());
		this->vertices.push_back(n);
		for (Edge* e : E->getV2()->getEdges())
			e->Vswap(E->getV2(), n);
	}
	if (E->getV2()->getVertices().empty()) {
		for (Edge* e : E->getV2()->getEdges()) {
			std::cout << "BBBBBBBBBBBBBBBBB" << std::endl;
			//this->nullinneredge(e);
			e->selfdestruct();
		}
		this->removeVertex(E->getV2());
	}

	E->selfdestruct();

	this->vertices.push_back(Vm);
	delete(V1);
	delete(V2);

	return Vm->getEdges();
}

void Graph::mergeAll() {
	std::cout << "Entering mergeAll with " << this->vertices.size() << " vertices and " << this->edges.size() << " edges" << std::endl;
	std::vector<Edge*> fresh;
	int i = 0;
	for(Edge* e:this->edges){
		std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << ++i << "/" << this->edges.size() << std::endl;
		std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
		if (!e) continue;
		std::vector<Edge*> tmp = this->merge(e);
		std::cout << tmp.size() << " edges" << std::endl;
		if (tmp.empty()) {
			std::cout<<"No edges to insert"<<std::endl;
			continue;
		}
		for (Edge* f : fresh) {
			for (int j = 0; j < tmp.size();j++) {
				if (tmp[j] == f) {
					tmp.erase(tmp.begin() + j);
					break;
				}
			}
		}
		/*
		for (Edge* e : tmp) {
			std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
		}
		*/
		fresh.insert(fresh.end(), tmp.begin(), tmp.end());
	}
	this->edges = fresh;
	std::cout<<"Finishing mergeAll with " << this->vertices.size() << " vertices and " << this->edges.size() << " edges" << std::endl;
	/****
	for (Edge* e : this->edges) {
		std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	}
	****/
	this->flag = true;
}


void Graph::expand() {
	std::cout << this->vertices.size() << " vertices to expand" << std::endl;
	std::vector<Vertex*> new_vertices;
	for (Vertex* v : this->vertices) {
		new_vertices.push_back(((Node*)v)->convert());
		this->P += ((Graph*)new_vertices.back())->getP();
		if (((Graph*)new_vertices.back())->isEmpty()) {
			std::cout << "empty graph" << std::endl;
			//delete new_vertices.back();
			
			for (Edge* e : new_vertices.back()->getEdges()) {
				this->removeinneredge(e);
			}
			new_vertices.pop_back();
		}
		//delete v;
	}
	this->vertices = new_vertices;
	std::cout << "End of expansion" << std::endl;
	
	std::vector<Vertex*> old(this->vertices);
	this->mergeAll();
	this->simplifyAll();
}

std::vector<Edge*> Graph::getEdges() { return Vertex::getEdges(); }
std::vector<Vertex*> Graph::getVertices() { return this->vertices; }

bool Graph::checkEdge(Edge* e) {
	return Vertex::checkEdge(e);
}

void Graph::removeinneredge(Edge* edge) {
	for (int i = 0; i < this->edges.size(); i++) {
		if (this->edges[i] == edge) {
			this->edges.erase(this->edges.begin() + i);
			return;
		}
	}
}

void Graph::nullinneredge(Edge* edge) {
	for (int i = 0; i < this->edges.size(); i++) {
		if (this->edges[i] == edge) {
			this->edges[i] = NULL;
			return;
		}
	}
}


void Graph::removeVertex(Vertex* v) {
	for (int i = 0; i < this->vertices.size(); i++) {
		if (this->vertices[i] == v) {
			this->vertices.erase(this->vertices.begin() + i);
			return;
		}
	}
}