#include "Deck.h"
#include "Card.h"
#include <random>

/*
Constructor for Deck\
Initialize 52 card Deck using pointer to Card Object
Calls ResetDeck which Inits deck to initial state:
	- Deuce to A, grouped by suits Spade to Heart.
*/
Deck::Deck() {
	int pos = 0;
	for (char suit : CARD_SUITS) {
		for (char rank : CARD_RANKS) {
			Card card(rank, suit);
			deck[pos] = &card;
			pos++;
		}
	}
	drawn_count = 0;
}


/*
Implementation of Deck API:
	DrawCard() - Draws card from deck
	ShuffleDeck() - Allows for drawing cards after deck is exhausted
	ResetDeck() - Resets all cards in Deck to initial position.
*/

/*
Draws random card from deck
Card cannot be redrawn until deck is shuffled / reset
 * Random number 'r' from 0 to number of remaining cards in deck is chosen.
 - Retrieves card 'C' at index "r"
 - Swap card 'C' with card at end of Undrawn portion of deck
		- Undrawn portion : [0, NumRemainingCards)
		- Drawn Portion : [NumRemainingCards, DECK_SIZE)
*/
Card* Deck::DrawRandomCard() {

	short int drawn_cards = NumDrawnCards();
	if (drawn_cards == DECK_SIZE) {
		ShuffleDeck;
	}
	int r = RandomCardIndex(0, GetUndrawnEnd());
	Card *drawn_card = CardAt(r);
	SwapCards(r, GetUndrawnEnd());
	return drawn_card;
}


/*
Draws specific card from deck.
Card cannot be redrawn until deck is shuffled / reset
 * Loops through drawn portion of deck to find card. 
 * If card is already drawn, returns null
	- Iterate through undrawn portion of deck.
	- If card found, swap to end of Undrawn portion and return card.
	- If card not found, return nullptr.
*/
Card* Deck::DrawSpecificCard(Card card) {
	int i = 0;
	int end = GetUndrawnEnd();
	for (i; i < end; i++) {
		Card *curr = CardAt(i);
		if (*curr == card) {
			SwapCards(i, GetUndrawnEnd());
			return curr;
		}
	}
	//If card not found
	return nullptr;
}


/*
Shuffles deck by resetting drawn card count to 0.
Cards in deck are not repositioned.
*/
void Deck::ShuffleDeck() {
	this->drawn_count = 0;
}

/*
Resets deck to initial position by sorting.
Drawn count resets to 0.
Deck state after reset: 
	- Deuce to A, grouped by suits Spade to Heart.
*/
void Deck::ResetDeck() {
	std::sort(this->deck, this->deck + DECK_SIZE, Card::CardComparator);
	this->drawn_count = 0;
}

/*
Helper functions used by API.
*/

//Retrieve Card at index 'card_index'
Card* Deck::CardAt(int card_index) {
	return this->deck[card_index];
}

//Sets the Card in deck at 'card_index' to 'card'
void Deck::SetCardAt(Card* card, int card_index) {
	this->deck[card_index] = card;
}

//Retrieves random number in range of ['low', 'high') (Low inclusive, High exclusive)
int Deck::RandomCardIndex(int low, int high) {

	return (std::rand() % (high - low)) + low;
}

//Get number of remaining cards in deck
int Deck::NumRemainingCards() {
	return DECK_SIZE - this->drawn_count;
}

//Retrieves number of undrawn cards in the deck
int Deck::NumDrawnCards() {

	return this->drawn_count;
}

//Swaps the cards at position 'index_one' and 'index_two' in the deck.
void Deck::SwapCards(int index_one, int index_two) {

	Card* card_one = CardAt(index_one);
	SetCardAt(CardAt(index_two), index_one);;
	SetCardAt(card_one, index_two);
}

//Get index of end of undrawn cards
int Deck::GetUndrawnEnd() {

	return NumRemainingCards();
}
