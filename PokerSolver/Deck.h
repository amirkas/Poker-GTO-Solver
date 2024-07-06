#pragma once

//Forward Declaration of Required Classes
class Card;

const short int DECK_SIZE = 52;

//Class Definition for standard 52 card Deck
class Deck{
private: 

	Card* deck[DECK_SIZE];
	short int drawn_count;

	Card* CardAt(int) const;

	void SetCardAt(Card*, int);

	int RandomCardIndex(int, int) const;

	void SwapCards(int, int);

	int GetUndrawnEnd() const;

public:
	
	Deck();

	Card* DrawRandomCard();

	Card* DrawSpecificCard(Card);

	void ShuffleDeck();

	void ResetDeck();

	int NumRemainingCards() const;

	int NumDrawnCards() const;
};

