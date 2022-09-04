#include "Solver.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string.h>

Solver::Solver(int u, int ss, std::vector<int> w, std::vector<int> obj) {
	this->G = (Graph*)(new Node(u, w, obj, ss))->convert();
}

long double Solver::buildnsolve() {
	int N, h, tmp;
	std::vector<int> obj, weights;
	std::string input;
	std::istringstream iss;
	std::cout << "How many cards are there in the deck?" << std::endl;
	/*std::getline(std::cin, input);
	std::cin.ignore();
	iss.str(input);
	while (iss >> tmp) {
		std::cout << "tmp=" << tmp << std::endl;
		N = tmp;
	}*/
	std::cin >> N;
	std::cout << "N=" << N << std::endl;
	std::cout << "How many cards are drawn? (size of the starting hand)" << std::endl;
	/*std::getline(std::cin, input);
	std::cin.ignore();
	std::cout << input << std::endl;
	iss.str(input);
	while (iss >> tmp) {
		std::cout << "tmp=" << tmp << std::endl;
		h = tmp;
	}*/
	std::cin >> h;
	std::cout << "h=" << h << std::endl;

	std::cout << "For each card you want in your starting hand, enter how many there are in the deck" << std::endl;
	std::cout << "E.g. if you have 2 copies of a card and 3 copies of another card, enter 2 3" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, input);
	iss.str(input);
	while (iss >> tmp) {
		std::cout << "tmp=" << tmp << std::endl;
		weights.push_back(tmp);
	}
	std::cout << weights.size() << std::endl;


	std::cout << "Enter the how many copy of each card you want in your starting hand respectively" << std::endl;
	std::cout << "Following the previous example, if you want 1 copy of each card, enter 1 1" << std::endl;
	for (;;) {
		std::getline(std::cin, input);
		std::istringstream iss2(input);
		while (iss2 >> tmp) {
			std::cout << "tmp=" << tmp << std::endl;
			obj.push_back(tmp);
		}
		std::cout << obj.size() << std::endl;
		if (weights.size() == obj.size())
			break;
		obj.clear();
		std::cout << "You need to enter as many numbers as previously" << std::endl;
	}
	Node* startingN = new Node(N, weights, obj, h);
	std::stringstream ss;
	bool first = true;
	for (auto i = startingN->obj.begin(); i != startingN->obj.end(); i++) {
		if (!first) ss << ", ";
		ss << *i;
		first = false;
	}
	std::cout << "h=" << startingN->samplesize << std::endl;
	std::cout << "obj=[" << ss.str() << "]" << std::endl;
	this->G = (Graph*)startingN->convert();

	std::cout << this->G->getVertices().size() << std::endl;

	return this->solve();
}

long double Solver::solve() {
	while (!G->isEmpty()) {
		//--std::cout << "hello" << std::endl;
		//--std::cout << "============================================\n";
		G->expand();
	}
	return G->getP();
}