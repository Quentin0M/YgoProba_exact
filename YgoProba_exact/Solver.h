#pragma once
#include "Graph.h"
#include "Node.h"
#include <vector>
class Solver
{
private:
	Graph* G = NULL;
	long double P = 0.L;

public:
	Solver(int urnSize, int samplesize,std::vector<int> weights, std::vector<int> obj);
	Solver() {}
	long double buildnsolve();
	long double solve();
};

