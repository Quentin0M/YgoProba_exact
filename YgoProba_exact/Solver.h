#pragma once
#include "Graph.h"
#include "Node.h"
#include <vector>
class Solver
{
private:
	Graph* G = NULL;
	double P = 0.;

public:
	Solver(int urnSize, int samplesize,std::vector<int> weights, std::vector<int> obj);
	Solver() {}
	double buildnsolve();
	double solve();
};

