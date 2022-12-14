#include "Graph.h"
#include <algorithm>
#include <iostream>
#include"exceptions.h"

#include "util.cpp"




Graph::Graph(const std::vector<Vertex*, std::allocator<Vertex*>> v, const std::vector<Edge*, std::allocator<Edge*>> e, const std::vector<Edge*, std::allocator<Edge*>> ae) :Vertex(ae) {
	this->vertices = std::vector<Vertex*>(v);
	this->edges = std::vector<Edge*>(e);
	for (Edge* e : this->edges)
		e->getContainers().push_back(this);
}

Vertex* Graph::simplify() {
	//--std::cout << "  Entered simplify" << std::endl;
	if (this->vertices.size() != 1) {
		//--std::cout << "not an atom (size=" << this->vertices.size() <<")" << std::endl;
		return NULL;
	}

	return this->vertices[0];
	
}

void Graph::simplifyAll() {
	//--std::cout << "Entering simplifyAll" << std::endl;
	if (this->vertices.size() == 1) {
		Graph* G = (Graph*)(this->vertices.back());
		//--std::cout << "only 1 subgraph with " << G->getVertices().size() << " vertices and " << G->getinneredges().size() << " edges" << std::endl;
		Graph* tmp = (Graph*)(this->vertices[0]);
		this->vertices = tmp->getVertices();
		this->edges = tmp->getinneredges();
		return;
	}

}


/***************************************************
* Try and merge 2 or more nodes
*/
std::vector<Edge*> Graph::merge(Edge* E) {
	Vertex* V1=NULL;
	Vertex* V2=NULL;
	Vertex* n;

	Vertex* W1 = E->getV1();
	Vertex* W2 = E->getV2();
	
	//--std::cout << "Entering merge "<<E->toString() << std::endl;

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
	//--std::cout << "GEN ended" << std::endl;
	this->removeinneredge(E);

	E->selfdestruct();

	if (!V1 || (V1 == V2)) {

		
		if (n = ((Graph*)W1)->simplify()) {
			if (!(n->getVertices().empty())) {
				this->removeVertex(W1);
				this->vertices.push_back(n);
				for (Edge* e : W1->getEdges())
					e->Vswap(W1, n);
			}
		}


		if (n = ((Graph*)W2)->simplify()) {
			if (!(n->getVertices().empty())) {
				this->removeVertex(W2);
				this->vertices.push_back(n);
				for (Edge* e : W2->getEdges())
					e->Vswap(W2, n);
			}
		}


		return std::vector<Edge*>();
	}

	//--std::cout << "looking for a clique" << std::endl;

	std::vector<Vertex*> outer, inner;
	outer.push_back(W1);
	outer.push_back(W2);

	inner.push_back(V1);
	inner.push_back(V2);

	this->tryClique(&outer, &inner);

	//--std::cout << "Size of the clique: " << outer.size() << std::endl;

	//--std::cout << "Finishing merge (before preliminary simplify)" << std::endl;
	
	//--//std::cout << (long)W1 << "---" << (long) W2 << std::endl;
	

	for (int i = 0; i < outer.size();i++) {
		if (n = ((Graph*)outer[i])->simplify()) {
			if (!(n->getVertices().empty())) {
				//--//std::cout << (long)W1 << std::endl;
				this->removeVertex(outer[i]);
				//--//this->removeVertex(W1);
				this->vertices.push_back(n);
				for (Edge* e : outer[i]->getEdges())
					e->Vswap(outer[i], n);
				outer[i] = n;
				//--std::cout << ((Node*)outer[i])->toString() << std::endl;
			}
		}
	}

	Node* tmp = NULL;

	for (Vertex* v : inner) {
		if (!tmp)
			tmp = new Node(*((Node*)v));
		else
			tmp = new Node((*tmp) * (*((Node*)v)));
	}

	//tmp can't equal NULL so it's ok
	Vertex* Vm = new Node(*tmp);





	std::vector<Edge*> fresh;

	for (Vertex* v : inner) {
		for (Edge* e : v->getEdges()) {
			e->Vswap(v, Vm);
			if (!this->checkInnerEdge(e)) {
				if (e->isMinimal())
					fresh.push_back(e);
				
				else {
					this->edges.push_back(e);
					e->getContainers().push_back(this);
					//--std::cout << "Added " << e->toString() << std::endl;
				}
				
			}
		}

	}


	//--std::cout << "Vm: colors = " << vtos(((Node*)Vm)->getColors()) << " P=" << ((Node*)Vm)->Pn() << " " << ((Node*)Vm)->getEdges().size()<< " outgoing edges " << Vm->getEdges().size() << std::endl;
		

	for (int i = 0; i < outer.size();i++) {
		Vertex* v = outer[i];
		if (!v->isNode()) {
			//--std::cout << "Before simplify: ";
			//--std::cout << ((((Node*)v)->toString() != "[]") ? ((Node*)v)->toString() : ((Graph*)v)->toString()) << " " << v->getVertices().empty() << std::endl;
			((Graph*)v)->removeVertex(inner[i]);
			if (n = ((Graph*)v)->simplify()) {
				if (!(n->getVertices().empty())) {
					this->removeVertex(v);
					this->vertices.push_back(n);
					for (Edge* e : v->getEdges()) {
						if (*((Node*)(e->Other(v))) == *((Node*)Vm)) {
							//--std::cout << "NO" << std::endl;
							e->Vswap(v, Vm);
						}
						else e->Vswap(v, n);
					}
				}
			}
			if (v->getVertices().empty()) {
				vector<Edge*> buf(v->getEdges());
				for (Edge* e : buf) {
					//--std::cout << "AAAAAAAAAAA" << std::endl;

					e->selfdestruct();
				}
				this->removeVertex(v);
			}
			//--std::cout << "After simplify: ";
			//--std::cout << ((((Node*)this->vertices.back())->toString() != "[]") ? ((Node*)this->vertices.back())->toString() : ((Graph*)this->vertices.back())->toString()) << " " << this->vertices.back()->getVertices().empty() << std::endl;
		}
		else {
			this->removeVertex(v);
		}
	}


	this->vertices.push_back(Vm);

	for (Vertex* v : inner) {
		delete v;
	}


	return fresh;
}

void Graph::mergeAll() {
	//--std::cout << "Entering mergeAll with " << this->vertices.size() << " vertices and " << this->edges.size() << " edges" << std::endl;
	//--for (Vertex* v : this->vertices) {
	//--	std::cout << ((Graph*)v)->toString() << std::endl;
	//--}
	std::vector<Edge*> fresh;
	int i = 0;
	std::vector<Edge*> old(this->edges);
	//for(Edge* e:old){
	while(!this->edges.empty()){
		Edge* e = this->edges.back();
		//--std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
		//--std::cout << ++i << "/" << this->edges.size() << std::endl;
		//--std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
		

		if (!e) continue;
		std::vector<Edge*> tmp = this->merge(e);
		//--std::cout << tmp.size() << " edges" << std::endl;
		if (tmp.empty()) {
			//--	std::cout<<"No edges to insert"<<std::endl;
			//--for (Edge* f : this->edges) {
			//--	std::cout << f->toString() << " @ = " << f << std::endl;
			//--}
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

		fresh.insert(fresh.end(), tmp.begin(), tmp.end());
	//--	std::cout << "After merge" << std::endl;
	//--	for (Edge* f : fresh) {
	//--		std::cout << f->toString() << std::endl;
	//--	}
	//--	std::cout << std::endl;
	//--	for (Edge* f : this->edges) {
	//--		std::cout << f->toString() << " @ = " << f << std::endl;
	//--	}
	//--	std::cout << std::endl;
	//--	for (Vertex* v : this->vertices) {
	//--		std::cout << ((((Node*)v)->toString() != "[]") ? ((Node*)v)->toString() : ((Graph*)v)->toString()) << std::endl;
	//--	}

	}
	this->edges = fresh;
	for (Edge* e : this->edges)
		e->getContainers().push_back(this);

	

	//--std::cout<<"Finishing mergeAll with " << this->vertices.size() << " vertices and " << this->edges.size() << " edges" << std::endl;
	//--for (Edge* e : this->edges) {
	//--	std::cout << e->toString() << std::endl;
	//--}
	//--this->flag = true;
}


void Graph::expand() {
	//--std::cout << this->vertices.size() << " vertices to expand:" << std::endl;
	//--for (Vertex* v : this->vertices) {
	//--	std::cout << ((((Node*)v)->toString() != "[]") ? ((Node*)v)->toString() : ((Graph*)v)->toString()) << " " << v->getP() << " " << v << std::endl;
	//--}
	//--std::wcout << std::endl;
	std::vector<Vertex*> new_vertices;
	for (Vertex* v : this->vertices) {
		new_vertices.push_back(((Node*)v)->convert());
		this->P += ((Graph*)new_vertices.back())->getP();
		if (((Graph*)new_vertices.back())->isEmpty()) {
			//--std::cout << "empty graph" << std::endl;
			//--delete new_vertices.back();
			
			for (Edge* e : new_vertices.back()->getEdges()) {
				this->removeinneredge(e);
				e->selfdestruct();
				//--delete e;
			}
			delete new_vertices.back();
			new_vertices.pop_back();
		}
		//--delete v;
		//--std::cout << "After expand" << std::endl;
		//--for (Edge* e : this->edges) {
		//--	std::cout << e->toString() << std::endl;
		//--}
	}
	this->vertices = new_vertices;
	//--std::cout << "End of expansion" << std::endl;

	//--std::cout << "Before mergeAll" << std::endl;
	//--for (Edge* e : this->edges) {
		//--std::cout << vtos(((Node*)e->getV1())->getColors()) << "---" << vtos(((Node*)e->getV2())->getColors()) << std::endl;
	//--	std::cout << e->toString() << std::endl;
	//--}
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
			//--std::cout << "found" << std::endl;
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


/**************
* Tries to find an edge linking g to n
*/
Edge* Graph::tryGetEdge(Vertex* g, Vertex* n) {
	for (Edge* e : g->getEdges()) {
		if (e->Other(g) == n) {
			return e;
		}
	}
	return NULL;
}




/**********************************
* Tries and find a clique of nodes with the same result so that they can be merged together
**************************************/
void Graph::tryClique(std::vector<Vertex*, std::allocator<Vertex*>>* outer, std::vector<Vertex*, std::allocator<Vertex*>>* inner) {
	Vertex* v1 = NULL;
	Vertex* v2 = NULL;
	std::vector<Edge*> elist(outer->back()->getEdges());
	std::vector<Vertex*> outerbuf, innerbuf;
	for (Edge* e : elist) {
		e->getEquivalentNodes(&v1, &v2);
		if (v1) {
			if ((v1 == inner->back()) && (v2!=inner->front())){
				innerbuf.push_back(v2);
				outerbuf.push_back(e->Other(outer->back()));
				this->removeinneredge(e);
				e->selfdestruct();
				v1 = NULL;
				v2 = NULL;
			}
			else if ((v2 == inner->back()) && (v1 != inner->front())) {
				innerbuf.push_back(v1);
				outerbuf.push_back(e->Other(outer->back()));
				this->removeinneredge(e);
				e->selfdestruct();
				v1 = NULL;
				v2 = NULL;
			}
			else {
				v1 = NULL;
				v2 = NULL;
				continue;
			}
		}
		/*
		else {
			this->removeinneredge(e);
			e->selfdestruct();
		}
		*/
	}
	outer->insert(outer->end(), outerbuf.begin(), outerbuf.end());
	inner->insert(inner->end(), innerbuf.begin(), innerbuf.end());
	this->cleanClique(outer->front(), outerbuf);
}


/*************************************************
* Removes all Edges from a clique
*/
void Graph::cleanClique(Vertex* V, std::vector<Vertex*, std::allocator<Vertex*>> vlist) {
	for(Vertex* v: vlist){
		if (Edge* e = V->eSearch(v)) {
			this->removeinneredge(e);
			e->selfdestruct();
		}
	}
	if (vlist.size() > 1) {
		Vertex* next = vlist.back();
		vlist.pop_back();
		this->cleanClique(next, vlist);
	}
}



/****************************************************************
* Checks if an inner edge exists, given an address
*/
bool Graph::checkInnerEdge(Edge* e) {
	if (e)
		for (Edge* edge : this->edges)
			if (edge && (edge == e))
				return true;
	return false;
}