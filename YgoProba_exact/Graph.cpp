#include "Graph.h"
#include <algorithm>
#include <iostream>
#include"exceptions.h"

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

	Vertex* W1 = E->getV1();
	Vertex* W2 = E->getV2();
	
	std::cout << "Entering merge"<<std::endl;

	try { E->getEquivalentNodes(&V1, &V2); }


	catch (SnT_null_exception* e) {
		this->removeinneredge(E);
		E->selfdestruct();

		return std::vector<Edge*>();
	}
	catch (S_null_exception* e) {
		this->removeinneredge(E);
		E->selfdestruct();
		return std::vector<Edge*>();
	}
	catch (T_null_exception* e) {
		this->removeinneredge(E);
		E->selfdestruct();
		return std::vector<Edge*>();
	}
	std::cout << "GEN ended" << std::endl;
	this->removeinneredge(E);
	E->selfdestruct();
	if (!V1) {

		//W1->removeEdge(E);
		//W2->removeEdge(E);
		//this->removeinneredge(E);
		//E->selfdestruct();
		
		if (n = ((Graph*)W1)->simplify()) {
			if (!(n->getVertices().empty())) {
				this->removeVertex(W1);
				this->vertices.push_back(n);
				for (Edge* e : W1->getEdges())
					e->Vswap(W1, n);
			}
		}

		//((Graph*)W2)->removeVertex(V2);
		if (n = ((Graph*)W2)->simplify()) {
			if (!(n->getVertices().empty())) {
				this->removeVertex(W2);
				this->vertices.push_back(n);
				for (Edge* e : W2->getEdges())
					e->Vswap(W2, n);
			}
		}

		//E->selfdestruct();

		/*
		std::cout << "Finishing merge (no merge)" << std::endl;
		for (Edge* e : this->edges) {
			if (e != E) {
				std::cout << (long)e << ": ";
				std::cout << vtos(((Node*)W1)->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
			}
		}
		*/

		return std::vector<Edge*>();
	}

	
	std::cout << "Finishing merge (before preliminary simplify)" << std::endl;
	
	//std::cout << (long)W1 << "---" << (long) W2 << std::endl;
	


	
	if (n = ((Graph*)W1)->simplify()) {
		if (!(n->getVertices().empty())) {
			//std::cout << (long)W1 << std::endl;
			this->removeVertex(W1);
			//this->removeVertex(W1);
			this->vertices.push_back(n);
			for (Edge* e : W1->getEdges())
				e->Vswap(W1, n);
			W1 = n;
		}
	}

	if (n = ((Graph*)W2)->simplify()) {
		if (!(n->getVertices().empty())) {
			this->removeVertex(W2);
			this->vertices.push_back(n);
			for (Edge* e : W2->getEdges())
				e->Vswap(W2, n);
			W2 = n;
		}
	}


	/*
	std::cout << "merge (after preliminary simplify)" << std::endl;
	for (Edge* e : this->edges) {
		if (e != E) {
			std::cout << (long)e << ": ";
			std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
		}
	}
	*/

	std::cout << "found nodes " << (V1 == V2) << std::endl;

	std::cout << "V1: colors = " << vtos(((Node*)V1)->getColors()) << " P=" << ((Node*)V1)->Pn() << std::endl;
	std::cout << "V2: colors = " << vtos(((Node*)V2)->getColors()) << " P=" << ((Node*)V2)->Pn() << std::endl;

	Node tmp = (*((Node*)V1)) * (*((Node*)V2));
	Vertex* Vm =(Vertex*) new Node(tmp);
	W1->removeEdge(E);
	W2->removeEdge(E);
	//this->removeinneredge(E);
	//E->selfdestruct();
	
	/*std::cout << "V1's edges:\n";
	for (Edge* e : V1->getEdges()) {
		std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	}

	std::cout << "V2's edges:\n";
	for (Edge* e : V2->getEdges()) {
		try { std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl; }
		catch (...) {
			std::cout<< ((Node*)e->getV1())->getColors().size()<<"==="<< ((Node*)e->getV2())->getColors().size()<<std::endl;
		}
	}*/


	std::vector<Edge*> fresh;
	for (Edge* e : V1->getEdges()) {
		e->Vswap(V1, Vm);
		if (e->isMinimal())
			fresh.push_back(e);
	}
	for (Edge* e : V2->getEdges()) {
		e->Vswap(V2, Vm);
		if (e->isMinimal())
			fresh.push_back(e);
	}


	std::cout << "Vm: colors = " << vtos(((Node*)Vm)->getColors()) << " P=" << ((Node*)Vm)->Pn() << " " << ((Node*)Vm)->getEdges().size()<< " outgoing edges " << Vm->getEdges().size() << std::endl;
		

	if (!W1->isNode()) {
		((Graph*)W1)->removeVertex(V1);
		if (n = ((Graph*)W1)->simplify()) {
			if (!(n->getVertices().empty())) {
				this->removeVertex(W1);
				this->vertices.push_back(n);
				for (Edge* e : W1->getEdges())
					e->Vswap(W1, n);
			}
		}
		if (W1->getVertices().empty()) {
			vector<Edge*> buf(W1->getEdges());
			for (Edge* e : buf) {
				std::cout << "AAAAAAAAAAA" << std::endl;
				//this->nullinneredge(e);
				e->selfdestruct();
			}
			this->removeVertex(W1);
		}
	}
	else this->removeVertex(W1);

	if (!W2->isNode()) {
		((Graph*)W2)->removeVertex(V2);
		if (n = ((Graph*)W2)->simplify()) {
			if (!(n->getVertices().empty())) {
				this->removeVertex(W2);
				this->vertices.push_back(n);
				for (Edge* e : W2->getEdges())
					e->Vswap(W2, n);
			}
		}
		if (W2->getVertices().empty()) {
			vector<Edge*> buf(W2->getEdges());
			for (Edge* e : buf) {
				std::cout << "BBBBBBBBBBBBBBBBB" << std::endl;
				//this->nullinneredge(e);
				e->selfdestruct();
			}
			this->removeVertex(W2);
		}
	}
	else this->removeVertex(W2);

	//E->selfdestruct();
	//this->removeinneredge(E);

	/*
	std::cout << "Finishing merge (after merge)" << std::endl;
	for (Edge* e : this->edges) {
		if (e != E)
			std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	}
	*/

	this->vertices.push_back(Vm);
	delete(V1);
	delete(V2);


	return fresh;
}

void Graph::mergeAll() {
	std::cout << "Entering mergeAll with " << this->vertices.size() << " vertices and " << this->edges.size() << " edges" << std::endl;
	std::vector<Edge*> fresh;
	int i = 0;
	std::vector<Edge*> old(this->edges);
	for(Edge* e:old){
		std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << ++i << "/" << this->edges.size() << std::endl;
		std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
		
		/*
		std::cout << "Before merge" << std::endl;
		for (Edge* f : this->edges) {
			if (f) {
				std::cout << (long)f << ": ";
				std::cout << vtos(((Node*)f->getV1())->getColors()) << "---" << vtos(((Node*)f->getV2())->getColors()) << std::endl;
			}
		}
		*/

		if (!e) continue;
		std::vector<Edge*> tmp = this->merge(e);
		std::cout << tmp.size() << " edges" << std::endl;
		if (tmp.empty()) {
			std::cout<<"No edges to insert"<<std::endl;
			continue;
		}
		/*
		for (Edge* e : tmp) {
			std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
		}*/

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
		std::cout << "After merge" << std::endl;
		for (Edge* f : fresh) {
			std::cout << f->toString() << std::endl;
		}
	}
	this->edges = fresh;

	

	std::cout<<"Finishing mergeAll with " << this->vertices.size() << " vertices and " << this->edges.size() << " edges" << std::endl;
	for (Edge* e : this->edges) {
		std::cout << e->toString() << std::endl;
	}
	this->flag = true;
}


void Graph::expand() {
	std::cout << this->vertices.size() << " vertices to expand:" << std::endl;
	for (Vertex* v : this->vertices) {
		std::cout << ((((Node*)v)->toString() != "[]") ? ((Node*)v)->toString() : ((Graph*)v)->toString()) << " " << v->getP() << std::endl;
	}
	std::wcout << std::endl;
	std::vector<Vertex*> new_vertices;
	for (Vertex* v : this->vertices) {
		new_vertices.push_back(((Node*)v)->convert());
		this->P += ((Graph*)new_vertices.back())->getP();
		if (((Graph*)new_vertices.back())->isEmpty()) {
			std::cout << "empty graph" << std::endl;
			//delete new_vertices.back();
			
			for (Edge* e : new_vertices.back()->getEdges()) {
				this->removeinneredge(e);
				//e->selfdestruct();
				//delete e;
			}
			new_vertices.pop_back();
		}
		//delete v;
		std::cout << "After expand" << std::endl;
		for (Edge* e : this->edges) {
			std::cout << e->toString() << std::endl;
		}
	}
	this->vertices = new_vertices;
	std::cout << "End of expansion" << std::endl;

	std::cout << "Before mergeAll" << std::endl;
	for (Edge* e : this->edges) {
		std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	}
	//std::vector<Vertex*> old(this->vertices);
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

void Graph::setP(long double p) { 
	Vertex::setP(p);
}


std::string Graph::toString() {
	std::stringstream ss;
	bool first = true;
	ss << "[G";
	for (Vertex* v : this->vertices) {
		if (!first) ss << ", ";
		ss << ((Node*)v)->toString();
		first = false;
	}
	ss << "]";
	return ss.str();
}