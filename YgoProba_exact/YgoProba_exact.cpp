
#include <iostream>
#include "Solver.h"

int main()
{
    for (;;) {
        std::cout << "P=" << Solver().buildnsolve();
        std::cin.ignore();
    }
    return 0;
}

