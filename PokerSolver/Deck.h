#pragma once

//Forward Declaration of Required Classes
class Card;

const short int DECK_SIZE = 52;

//Class Definition for standard 52 card Deck
class Deck{
private: 

	Card* deck[DECK_SIZE];
	short int drawn_count;

	Card* CardAt(int);

	void SetCardAt(Card, int);

	static int RandomCardIndex(int, int);

	void SwapCards(int, int);

	int GetUndrawnEnd();

public:
	
	Deck();

	Card* DrawRandomCard();

	Card* DrawSpecificCard(Card);

	void ShuffleDeck();

	void ResetDeck();

	int NumRemainingCards();

	int NumDrawnCards();
};

v