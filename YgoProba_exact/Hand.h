#pragma once

#include "Color.h"
#include <vector>

class Hand
{
private:
	Color* clist = nullptr;
	int s = 0;

public:
	/////////////////////////////////
	/// CONSTRUCTORS / DESTRUCTOR ///
	/////////////////////////////////

	Hand();
	Hand(const Hand&);
	Hand(const std::vector<Color>& cl);
	Hand(const Hand&, const int values);

	~Hand();


	/////////////////////////
	/// GETTERS / SETTERS ///
	/////////////////////////

	const int size() const;
	Color& front();

	/////////////////////
	/// OTHER METHODS ///
	/////////////////////
	
	// Verifies if 2 hands have the same kind of cards
	bool isCompatible(const Hand&);
	// verifies if a hand satisfies an objective hand
	bool satisfies(const Hand&);

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

