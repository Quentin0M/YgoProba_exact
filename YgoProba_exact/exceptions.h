#pragma once
#include <iostream>

class SnT_null_exception : public std::exception {

};

class S_null_exception : public std::exception {

};

class T_null_exception : public std::exception {

};

class empty_array_exception : public std::exception {
	const char* what() {
		return "Array is empty";
	}
};

class index_out_of_bounds_exception : public std::exception {
	const char* what() {
		return "Index out of bounds";
	}
};

class incompatible_hands_exception :public std::exception {
	const char* what() {
		return "Hands are incompatible (not the same size or do not contain the same types";
	}
};