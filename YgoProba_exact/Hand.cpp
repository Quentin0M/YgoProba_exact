#include "Hand.h"
#include "exceptions.h"


Hand::Hand(){}

Hand::Hand(const Hand& h) {
	this->s = h.s;
	this->clist = (Color*)malloc(this->s * sizeof(Color);
	for (int i = 0; i < this->s; ++i) {
		this->clist[i] = h[i];
	}
}

Hand::Hand(const std::vector<Color>& cl) {
	this->s = cl.size();
	this->clist = (Color*)malloc(this->s * sizeof(Color));
	for (int i = 0; i < this->s; ++i) {
		this->clist[i] = cl[i];
	}
}

Hand::Hand(const Hand& h, const int values) {
	this->s = h.s;
	this->clist = (Color*)malloc(this->s * sizeof(Color));
	for (int i = 0; i < this->s; ++i) {
		this->clist[i] = Color(values,h[i].kind());
	}
}


Hand::~Hand() {
	free(this->clist);
}




int Hand::size() {
	return this->s;
}
Color& Hand::front() {
	if (this->s)
		return this->clist[0];
	throw(empty_array_exception());
}




Color& Hand::operator[](int i) {
	if (this->s > i)
		return this->clist[i];
	throw(index_out_of_bounds_exception());
}


Color& Hand::operator[](int i) const{
	if (this->s > i)
		return this->clist[i];
	throw(index_out_of_bounds_exception());
}

