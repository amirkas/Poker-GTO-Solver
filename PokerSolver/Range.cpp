#include "Range.h"
#include "HandEvaluationConstants.h";
#include "GameStateNode.h"

/*
Private Function Definitions
*/

/*
HandHash
	Takes in 2 cards, and returns index in Range Array and Range Frequency Array
*/

int Range::HandHash(card_pair hole_cards, bool is_hand_sorted) {

	if (!is_hand_sorted) {
		hole_cards = SortCardPair(hole_cards);
	}

	const char* first_card = hole_cards.first;
	const char* second_card = hole_cards.second;

	//Card ranks start from 0 (deuce) - 12 (Ace)
	int first_card_rank = HandEvalConstants::CARD_RANKS.at(first_card[0]) - 2;
	int second_card_rank = HandEvalConstants::CARD_RANKS.at(second_card[0]) - 2;

	//Calculate number of hands before indexed hand.

	//Number of unpaired hands before pair: (first_card, first_card)
	int previous_hands = ((first_card_rank + 1) * (second_card_rank) * 8);

	//Number of paired hands before pair: (first_card, first_card)
	previous_hands += (first_card_rank * 6);

	//If card isn't paired, find:
	//		Number of unpaired cards between
	//		(first_card, second_card - 1) and pair: (first_card, first_card)
	//		As well as number of (first_card, first_card) pairs: (Always 6)
	if (first_card_rank < second_card_rank) {
		previous_hands += (( second_card_rank - first_card_rank - 1 ) * 16) + 6;
	}
	

	
	const char first_suit = first_card[1];
	const char second_suit = second_card[1];

	int first_suit_val = GetSuitRank(first_suit);
	int second_suit_val = GetSuitRank(second_suit);

	int suit_offset;
	//Calculate offset due to suit combination
	if (first_card_rank < second_card_rank) {
		//Hand isn't pair
		suit_offset = ( first_suit_val * 4 ) + second_suit_val;
	}
	else {
		//Hand is pair
		suit_offset = GetPairedSuitComboVal(first_suit, second_suit);
	}

	return previous_hands + suit_offset;
}

/*
Sorts pair of cards for easy hashing.
Cards are first sorted by rank in ascending order.
If ranks are same (card is paired) then sort cards by suit

Ex: 2s2h -> 2h2s
	KcQc -> QcKc
	KsQh -> QhKs
	KdQh -> QhKd
*/
card_pair Range::SortCardPair(card_pair unsorted_hole_cards) {

	const char* first_card = unsorted_hole_cards.first;
	const char* second_card = unsorted_hole_cards.second;

	

	int first_card_rank = HandEvalConstants::CARD_RANKS.at(first_card[0]) - 2;
	int second_card_rank = HandEvalConstants::CARD_RANKS.at(second_card[0]) - 2;

	card_pair sorted_cards;
	if (first_card_rank < second_card_rank) {
		sorted_cards.first = first_card;
		sorted_cards.second = second_card;
	}
	else if (first_card_rank > second_card_rank) {
		sorted_cards.first = second_card;
		sorted_cards.second = first_card;
	}
	else {

		const char first_suit = first_card[1];
		const char second_suit = second_card[1];

		int first_suit_val = GetSuitRank(first_suit);
		int second_suit_val = GetSuitRank(second_suit);

		if (first_suit_val < second_suit_val) {
			sorted_cards.first = first_card;
			sorted_cards.second = second_card;
		}
		else {
			sorted_cards.first = second_card;
			sorted_cards.second = first_card;
		}
	}
	return sorted_cards;
}


/*
For suit of a card, return suit value
	Suit value used in combination with suit value of other card to find relative index.
*/
int Range::GetSuitRank(const char card_suit) {

	switch (card_suit) {
		case 'd':
			return 0;
		case 'c':
			return 1;
		case 'h':
			return 2;
		default:
			return 4;
	}
}

/*
For paired hand, return relative index based on suit combination.
*/
int Range::GetPairedSuitComboVal(char suit_a, char suit_b) {

	switch (suit_a) {
		case 'd':
			if (suit_b == 'c') {
				return 0;
			}
			if (suit_b == 'h') {
				return 1;
			}
			return 2;

		case 'c':
			if (suit_b == 'h') {
				return 3;
			}
			return 4;

		case 'h':
			return 5;
	}

}




/*
Public Function Definitions
*/


/* Constructors */

Range::Range(std::vector<std::pair<card_pair, GameStateNode*>>* range_hole_cards,
			 bool are_hands_sorted) {

	for (std::pair<card_pair, GameStateNode*> hand : *(range_hole_cards)) {
		SetGameStateList(hand.first, hand.second, are_hands_sorted);
	}
}

Range::Range(std::vector<std::pair<card_pair_and_freq, GameStateNode*>>* range_hole_cards_and_freq,
			 bool are_hands_sorted) {

	for (std::pair<card_pair_and_freq, GameStateNode*> hand : *( range_hole_cards_and_freq )) {
		SetGameStateList(hand.first.first, hand.second, are_hands_sorted);
		SetHandFrequency(hand.first.first, hand.first.second, are_hands_sorted);
	}

}


/* API definitions */

/* Data retrieval */
GameStateNode* Range::GetGameStateListPtr(card_pair hole_cards, bool is_hand_sorted) {

	int hand_hash = HandHash(hole_cards, is_hand_sorted);
	return this->range_arr[hand_hash];
}

float Range::GetHandFrequency(card_pair hole_cards, bool is_hand_sorted) {

	int hand_hash = HandHash(hole_cards, is_hand_sorted);
	return this->range_freq[hand_hash];
}


/* Data settor */

void Range::SetGameStateList(card_pair hole_cards, GameStateNode* GameStateList, bool is_hand_sorted) {

	int hand_hash = HandHash(hole_cards, is_hand_sorted);
	this->range_arr[hand_hash] = GameStateList;
}

void Range::SetHandFrequency(card_pair hole_cards, float freq, bool is_hand_sorted) {

	int hand_hash = HandHash(hole_cards, is_hand_sorted);
	this->range_freq[hand_hash] = freq;
}