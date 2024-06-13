#pragma once

#include <string>
#include <utility>
#include <vector>

class Card {

private:
	char rank; //A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2

public:

	Card(char c) { rank = c; };

	char GetRank() { return rank; };

	std::string toString();

};

class SuitedCard : Card {

private:

	char suit; //s, c, d, h

public: 

	char GetRank();

	char GetSuit();

	std::string GetCardString();

};


class HoleCards {

private:
	Card first;
	Card second;

public:

	Card GetFirstCard();

	Card GetSecondCard();

	std::pair<std::string, std::string> ToStringPair();

};





class UnsuitedHoleCards {

private:
	UnsuitedCard first;
	UnsuitedCard second;

public:

	UnsuitedCard GetFirstUnsuitedCard();

	UnsuitedCard GetSecondUnsuitedCard();

	std::pair<std::string, std::string> ToStringPair();

};



class CardCombinations {

private:

	std::vector<Card> SeenCards;





};

