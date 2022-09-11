#pragma once

#include "Color.h"
#include <vector>

class Hand
{
private:
	Color* clist = nullptr;
	int s = 0;

public:

	/// CONSTRUCTORS / DESTRUCTOR

	Hand();
	Hand(const Hand&);
	Hand(const std::vector<Color>& cl);
	Hand(const Hand&, const int values);

	~Hand();



	/// GETTERS / SETTERS

	int size();
	Color& front();

	/// OPERATOR OVERRIDES

	friend bool operator==(const Hand&, const Hand&);
	friend bool operator!=(const Hand&, const Hand&);
	// the following operators test for inclusion rather than size (which wouldn't make sense)
	// They follow the exact / card / garnet rules
	// I might change some op to check for success
	friend bool operator<=(const Hand&, const Hand&);
	friend bool operator>=(const Hand&, const Hand&);
	friend bool operator<(const Hand&, const Hand&);
	friend bool operator>(const Hand&, const Hand&);

	Color& operator[](int);
	Color& operator[](int) const;
	Hand operator=(const Hand&);



};

