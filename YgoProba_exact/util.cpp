#include "util.h"

using namespace std;


template<typename T>
string vtos(vector<T> v) {
	std::stringstream ss;
	bool first = true;
	ss << "[";
	for (auto i = v.begin(); i != v.end(); i++) {
		if (!first) ss << ", ";
		ss << *i;
		first = false;
	}
	ss << "]";
	return ss.str();
}