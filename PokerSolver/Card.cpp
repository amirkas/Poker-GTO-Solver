#include "Card.h"

/*
Implementation of Card Class.
Texas HoldEm uses a 52 card deck which includes cards ranked:
		Ace, King, Queen, Jack, Numbers 10-2.
Every card also has one of 4 suits: Spade, Club, Diamond, Heart

This program converts ranks into numbers 2 (Deuce) - 14 (Ace).
*/


//Constructor Definitions
Card::Card(char card_rank, char card_suit) {

	this->rank = card_rank;
	this->suit = card_suit;
}

Card::Card(std::string card) {

	this->rank = card[0];
	this->suit = card[1];
}


//Object Accessor Implementation
char Card::GetRankAsChar() {
	return this->rank;
}

char Card::GetSuitAsChar() {
	return this->suit;
}

short int Card::GetRankAsInt() {
	return CARD_VALUES.at(this->rank);
}

short int Card::GetSuitAsInt() {
	return SUIT_VALUES.at(this->suit);
}

std::string Card::toString() {

	return std::string{this->rank, this->suit};

}


//Operator Overload Implementation
bool operator==(Card& first, Card& second) {
	return (first.GetRankAsChar() == second.GetRankAsChar()) && (first.GetSuitAsChar() == second.GetSuitAsChar());
}

bool operator<(Card& first, Card& second) {
	if (first.GetRankAsInt() < second.GetRankAsInt()) {
		return true;
	}
	else if (first.GetRankAsInt() > second.GetRankAsInt()) {
		return false;
	}
	else if (first.GetSuitAsChar() == second.GetSuitAsChar()) {
		return false;
	}
	else {
		return first.GetSuitAsInt() < second.GetSuitAsInt();
	}
}

bool operator>(Card& first, Card& second) {
	if (first.GetRankAsInt() < second.GetRankAsInt()) {
		return false;
	}
	else if (first.GetRankAsInt() > second.GetRankAsInt()) {
		return true;
	}
	else if (first.GetSuitAsChar() == second.GetSuitAsChar()) {
		return false;
	}
	else {
		return first.GetSuitAsInt() > second.GetSuitAsInt();
	}
}


//Comparator Implementation
bool Card::CardComparator(const Card* a, const Card* b) {
	return a < b;
}

