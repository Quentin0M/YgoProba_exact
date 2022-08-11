#include "Node.h"


Node::Node(const std::vector<int>& w, const std::vector<Edge*>& e):Vertex(e) {
	this->weights = std::vector<int>(w.begin(), w.end());
	for (int e : this->weights) this->sumw += e;
	this->colors = std::vector<int>(this->weights.size(), 0);
}

Node::Node(const std::vector<int>& w, const int& N, const double& P, const std::vector<Edge*>& e) :Vertex(e) {

	this->weights = std::vector<int>(w.begin(), w.end());
	this->N = N;
	this->P = P;
	this->sumw = 0;
	for (int e : this->weights) this->sumw += e;
}


Node::Node(const std::vector<int>& w, std::vector<int>& c, const int& N, const int& h, const int& sumw, const double& P,const int& hash, const std::vector<Edge*>& e) :Vertex(e) {
	this->weights = std::vector<int>(w.begin(), w.end());
	this->N = N;
	this->h = h;
	this->sumw = sumw;
	this->P = P;
	this->colors = std::vector<int>(c.begin(), c.end());
	this->hash = hash;

}

Node::Node(const Node& n):Vertex(n) {
	this->weights = std::vector<int>(n.weights.begin(), n.weights.end());
	this->N = n.N;
	this->h = n.h;
	this->sumw = n.sumw;
	this->P = n.P;
	this->colors = std::vector<int>(n.colors.begin(), n.colors.end());
	this->hash = n.hash;
}

std::vector<Edge*> Node::getEdges() {

	return Vertex::getEdges(); 
}

void Node::draw(int color) {
	if (color == -1) {
		this->P *= (this->N - this->sumw) / this->N;
	}
	else {
		this->P *= this->weights[color] / this->N;
		this->weights[color]--;
		this->sumw--;
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
	std::vector<Vertex*> vlist;
	std::vector<Edge*> elist;

	for (int i = -1; i < this->colors.size(); i++) {
		vlist.push_back(new Node(*this));
		vlist[vlist.size() - 1]->wipeEdges();
		((Node*)vlist[vlist.size() - 1])->draw(i);
		if (!((Node*)vlist[vlist.size() - 1])->Pn()) vlist.pop_back();
	}
	for (int i = 0; i < vlist.size(); i++) {
		for (int j = i + 1; j < vlist.size(); j++) {
			elist.push_back(new Edge(vlist[i], vlist[j], this->hash));
		}
	}
	return new Graph(vlist, elist, this->getEdges());
}