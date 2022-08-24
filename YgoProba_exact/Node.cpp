#include "Node.h"
#include <iostream>
#include "util.cpp"

int Node::samplesize = 0;
std::vector<int> Node::obj = std::vector<int>();

Node::Node(int n, const std::vector<int>& w, std::vector<int> obj, int ss) :Vertex(std::vector<Edge*>()) {
	this->weights = std::vector<int>(w);
	for (int e : this->weights) this->sumw += e;
	this->colors = std::vector<int>(this->weights.size(), 0);
	this->obj = obj;
	this->samplesize = ss;
	this->N = n;
	this->vertices = std::vector<Vertex*>();
	this->vertices.push_back((Vertex*)this);
}

Node::Node(const std::vector<int>& w, const std::vector<Edge*>& e, std::vector<int> obj,int ss):Vertex(e) {
	this->weights = std::vector<int>(w);
	for (int e : this->weights) this->sumw += e;
	this->colors = std::vector<int>(this->weights.size(), 0);
	this->obj = obj;
	this->samplesize = ss;
	this->vertices = std::vector<Vertex*>();
	this->vertices.push_back((Vertex*)this);
}

Node::Node(const std::vector<int>& w, const int& N, const long double& P, const std::vector<Edge*>& e) :Vertex(e) {

	this->weights = std::vector<int>(w);
	this->N = N;
	this->P = P;
	this->sumw = 0;
	for (int e : this->weights) this->sumw += e;
	this->vertices = std::vector<Vertex*>();
	this->vertices.push_back((Vertex*)this);
}


Node::Node(const std::vector<int>& w, std::vector<int>& c, const int& N, const int& h, const int& sumw, const long double& P,const int& hash, const std::vector<Edge*>& e) :Vertex(e) {
	this->weights = std::vector<int>(w);
	this->N = N;
	this->h = h;
	this->sumw = sumw;
	this->P = P;
	this->colors = std::vector<int>(c);
	this->hash = hash;
	this->obj = obj;
	this->vertices = std::vector<Vertex*>();
	this->vertices.push_back((Vertex*)this);

}

Node::Node(const Node& n):Vertex(n) {
	this->weights = std::vector<int>(n.weights);
	this->N = n.N;
	this->h = n.h;
	this->sumw = n.sumw;
	this->P = n.P;
	this->colors = std::vector<int>(n.colors);
	this->hash = n.hash;
	this->obj = n.obj;
	this->vertices = std::vector<Vertex*>();
	this->vertices.push_back((Vertex*)this);
}

std::vector<Edge*> Node::getEdges() {

	return Vertex::getEdges(); 
}

void Node::draw(int color) {
	if (color == -1) {
		std::cout << this->P << " * (" << this->N << " - " << this->sumw << ") / " << this->N << " = ";
		this->P *= ((long double)(this->N - this->sumw)) / ((long double)this->N);
		std::cout << this->P << std::endl;
	}
	else {
		this->P *= ((long double)this->weights[color]) / ((long double)this->N);
		this->weights[color]--;
		this->sumw--;
		this->colors[color]++;
	}
	this->N--;
	this->h++;
}

Node Node::operator=(const Node& n) {
	return Node(n);
}

Node Node::operator*(const Node& n) {
	return Node(this->weights,this->colors, this->N, this->h, this->sumw, this->P + n.P,this->hash,std::vector<Edge*>());
}



Vertex* Node::convert() {
	std::cout << "###################################################################" << std::endl;
	std::cout << "Entering convert() with " << this->colors.size() + 1 << " colors to draw" << std::endl;
	std::cout << "Node " << this->toString() << std::endl;
	std::cout << "Total P of the node = " << this->P << std::endl;
	std::cout << "This node has " << this->getEdges().size() << " outgoing edges" << std::endl;
	std::vector<Vertex*> vlist;
	std::vector<Edge*> elist;
	//Node* tmp;
	long double successP = 0.L;
	std::cout << "check" << std::endl;

	for (int i = -1; i < (int)this->colors.size(); i++) {
		std::cout << "Drawing " << i << std::endl;
		//tmp = new Node(*this);
		vlist.push_back(new Node(*this));
		vlist[vlist.size() - 1]->wipeEdges();
		((Node*)vlist.back())->draw(i);
		//Removing all nodes whose P=0 or nodes that can't be a success
		if (((Node*)vlist.back())->isdeadend()) {
			std::cout << "Dead end" << std::endl;
			vlist.pop_back();
		}
		else if (!((Node*)vlist.back())->Pn()) {
			std::cout << "Node with P = 0" << std::endl;
			vlist.pop_back();
		}
		//Removing nodes which are already successes and getting their probabilities
		else if (((Node*)vlist.back())->isSuccess()) {
			std::cout << "Success with P = " << ((Node*)vlist.back())->Pn() << std::endl;
			successP += ((Node*)vlist.back())->Pn();
			vlist.pop_back();
		}
	}
	std::cout << "Finished drawing" << endl;
	for (int i = 0; i < ((int)vlist.size())-1; i++) {
		for (int j = i + 1; j < vlist.size(); j++) {
			elist.push_back(new Edge(vlist[i], vlist[j], this->hash));
			vlist[i]->addEdge(elist.back());
			vlist[j]->addEdge(elist.back());
		}
	}
	std::cout << "edges created: " << std::endl;
	for (Edge* e : elist) {
		std::cout << "[" << vtos(((Node*)e->getV1())->getColors()) << " , " << vtos(((Node*)e->getV2())->getColors()) << "]" << std::endl;
	}
	Graph* G = new Graph(vlist, elist, std::vector<Edge*>());
	for (Edge* e : this->getEdges()) {
		e->Vswap(this, (Vertex*)G);
		//e->Vswap((Vertex*)G, (Vertex*)G);
		std::cout << "The edge " << (G->checkEdge(e) ? "has" : "hasn't") << " been added to G" << std::endl;
	}
	//std::cout << vtos(((Node*)G)->getColors()) << std::endl;
	((Graph*)G)->setP(successP);
	/*
	for (Edge* e : G->getEdges()) {
		std::cout << "{{{}}}" << e->toString() << std::endl;
	}
	*/
	//std::cout << vtos(((Node*)G)->getColors()) << std::endl;
	//std::cout << ( * ((Node*)G->getVertices()[0]) == *((Node*)G->getVertices()[0]) )<< std::endl;
	
	//std::cout <<"@ = " << (long)G << std::endl;
	return (Vertex*) (G);
}

bool Node::isSuccess() {
	for (int i = 0; i < colors.size(); i++)
		if (colors[i] < obj[i]) return false;
	return true;
}

bool Node::isdeadend() {
	std::vector<int> tmp;
	for (int i = 0; i < this->obj.size(); i++) {
		tmp.push_back(this->obj[i] - this->colors[i]);
	}
	// std::transform(this->obj.begin(), this->obj.end(), this->colors.begin(), tmp, std::minus<int>());
	int sum = 0;
	// if an element is there more time than needed, it shouldn't make me want less of the others
	for (int e : tmp) sum += (e < 0 ? 0 : e); 
	return (this->samplesize - this->h) < sum;
}

void Node::setEdges(const std::vector<Edge*>& e) { Vertex::setEdges(e); }



std::vector<Vertex*> Node::getVertices() {
	std::vector<Vertex*> res;
	res.push_back(this);
	return res;
}

std::string Node::toString() {
	return vtos(this->colors);
}

void Node::setP(long double p) {
	Vertex::setP(p);
}