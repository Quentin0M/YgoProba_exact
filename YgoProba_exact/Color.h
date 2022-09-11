#pragma once


/*
* Defines what kind of color we're dealing with
* -Balls are the math proba concept, exactly their obj must be drawn for the test to be a success
* -Cards are used for children's card games. At least the obj must be drawn for a successful hand
* -Garnet is a yugioh term for cards you don't want to draw. At least the obj must remain in the deck for a success
*  for simplicity's sake, the obj will be converted beforehand to the max number to be drawn
*/
typedef enum { ball, card, garnet } Kind;

class Color
{
private:
	int cardinal;
	Kind k;

public:

	/// CONSTRUCTORS / DESTRUCTOR

	Color(int, Kind);
	Color(const Color&);

	~Color() {}

	/// GETTERS / SETTERS

	Kind kind();

	/// OPERATOR OVERRIDES

	Color& operator++();
	Color& operator--();
	Color operator++(int);
	Color operator--(int);

	Color operator+(int);
	Color operator+(const Color&);

	Color operator-(int);
	Color operator-(const Color&);

	friend bool operator==(const Color&, const Color&);
	friend bool operator!=(const Color&, const Color&);
	friend bool operator<(const Color&, const Color&);
	friend bool operator>(const Color&, const Color&);
	friend bool operator<=(const Color&, const Color&);
	friend bool operator>=(const Color&, const  Color&);
};

