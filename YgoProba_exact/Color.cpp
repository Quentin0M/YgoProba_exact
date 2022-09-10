#include "Color.h"


Color::Color(int n, Kind k) {
	this->cardinal = n;
	this->kind = k;
}

Color::Color(const Color& c) {
	this->cardinal = c.cardinal;
	this->kind = c.kind;
}


Color& Color::operator++() {
	this->cardinal++;
	return *this;
}

Color& Color::operator--() {
	this->cardinal--;
	return *this;
}

Color Color::operator++(int i) {
	Color res = Color(*this);
	this->cardinal++;
	return res;
}


Color Color::operator--(int i) {
	Color res = Color(*this);
	this->cardinal--;
	return res;
}



Color Color::operator+(int i) {
	Color res = Color(*this);
	res.cardinal += i;
	return res;
}
Color Color::operator+(const Color& c) {
	Color res = Color(*this);
	res.cardinal += c.cardinal;
	return res;
}

Color Color::operator-(int i) {
	Color res = Color(*this);
	res.cardinal -= i;
	return res;
}
Color Color::operator-(const Color& c) {
	Color res = Color(*this);
	res.cardinal -= c.cardinal;
	return res;
}

bool operator==(const Color& c1, const Color& c2) {
	return (c1.cardinal == c2.cardinal) && (c1.kind == c2.kind);
}

bool operator!=(const Color& c1, const Color& c2) {
	return (c1.cardinal != c2.cardinal) || (c1.kind != c2.kind);
}

bool operator<(const Color& c1, const Color& c2) {
	return (c1.cardinal < c2.cardinal);
}

bool operator>(const Color& c1, const Color& c2) {
	return (c1.cardinal > c2.cardinal);
}

bool operator<=(const Color& c1, const Color& c2) {
	return (c1.cardinal <= c2.cardinal);
}

bool operator>=(const Color& c1, const Color& c2) {
	return (c1.cardinal >= c2.cardinal);
}
