#pragma once
#include <utility>
#include <string>
//Forward declaration of Required Classes;
class Card;


class HoleCards {

private:
	Card* high;
	Card* low;

public:

	//Constructor
	HoleCards(Card*, Card*);

	//Object Accessors
	std::pair < Card*, Card*> ToCardPair();
	std::pair <std::string, std::string> ToStringPair();
};

