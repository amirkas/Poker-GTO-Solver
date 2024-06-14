#include "HoleCards.h"
#include "Card.h"

/*
Constructor implementation.
*/
HoleCards::HoleCards(Card* card_a, Card* card_b) {

	if (card_a >= card_b) {
		high = card_a;
		low = card_b;
	}
	else {
		high = card_b;
		low = card_b;
	}
}


//Object Accessor Implementation
/*
Returns pair of Card pointers
Pair.first is high card, Pair.second is low card.
*/
std::pair<Card*, Card*> HoleCards::ToCardPair() {
	std::pair<Card*, Card*> card_pair;
	card_pair.first = this->high;
	card_pair.second = this->low;
	return card_pair;
}

/*
Returns pair of Strings
Pair.first is high card, Pair.second is low card.
*/
std::pair<std::string, std::string> HoleCards::ToStringPair() {

	std::pair<std::string, std::string> string_pair;
	string_pair.first = high->toString();
	string_pair.second = low->toString();
	return string_pair;
}
