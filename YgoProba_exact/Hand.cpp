#include "Hand.h"
#include "exceptions.h"


/// CONSTRUCTORS / DESTRUCTORS

Hand::Hand(){}

Hand::Hand(const Hand& h) {
	this->s = h.s;
	this->clist = (Color*)malloc(this->s * sizeof(Color));
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


/// GETTERS / SETTERS

const int Hand::size() const {
	return this->s;
}
Color& Hand::front() {
	if (this->s)
		return this->clist[0];
	throw(empty_array_exception());
}

/// OTHER METHODS

bool Hand::isCompatible(const Hand& h) {
	if (this->s == h.s) {
		for (int i = 0; i < this->s; ++i) {
			if ((*this)[i].kind() != h[i].kind()) return false;
		}
		return true;
	}
	return false;
}

bool Hand::satisfies(const Hand& obj) {
	if (!this->isCompatible(obj)) return false; // maybe should throw an exception
	for (int i = 0; i < this->s; ++i) {
		switch ((*this)[i].kind()) {
		case ball:
			if ((*this)[i] != obj[i]) return false;
		case card:
			if ((*this)[i] < obj[i]) return false;
		case garnet:
			if ((*this)[i] > obj[i]) return false;
		}
	}
	return true;
}



/// OPERATOR OVERRIDES

bool operator==(const Hand& h1, const Hand& h2) {
	if (h1.size() != h2.size()) return false;
	for (int i = 0; i < h1.size(); ++i) {
		if (h1[i] != h2[i]) return false;
	}
	return true;
}

bool operator!=(const Hand& h1, const Hand& h2) {
	return !(h1 == h2);
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

Hand Hand::operator=(const Hand& h) {
	(*this) = Hand(h);
	return *this;
}