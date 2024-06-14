#pragma once

#include <string>
#include <utility>
#include <map>

const char CARD_RANKS[14] = "23456789TJQKA";
const char CARD_SUITS[5] = "scdh";

const std::map<char, int> CARD_VALUES = {
	{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10},
	{'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}
	, {'4', 4}, {'3', 3}, {'2', 2} 
};

const std::map<char, int> SUIT_VALUES = {
	{'s', 4}, {'c', 3}, {'d', 2}, {'h', 1}
};

//Representation of single card out of 52 card deck
class Card {
private:

	char rank;
	char suit;

public:

	//Constructors
	Card(char card_rank, char card_suit);
	Card(std::string card);

	//Object Accessors
	char GetRankAsChar();
	char GetSuitAsChar();
	short int GetRankAsInt();
	short int GetSuitAsInt();
	std::string toString();

	//Operator Overloads
	friend bool operator==(const Card&, const Card&);

	friend bool operator<(const Card&, const Card&);

	friend bool operator>(const Card&, const Card&);

	//Comparator
	bool CardComparator(const Card*, const Card*);
};

