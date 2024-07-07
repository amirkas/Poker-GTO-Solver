#pragma once
#include <utility>
#include <vector>

//There are 1326 total possible starting hands in Texas Holdem
const int NUM_CARD_COMBOS = 1326;


//Represents pair of cards (Hole cards)
typedef std::pair<const char*, const char*> card_pair;

//Represents pair of cards alongside associated frequency
typedef std::pair<std::pair<const char*, const char*>, float> card_pair_and_freq;

class GameStateNode;

class Range {

private:

	static GameStateNode* range_arr[NUM_CARD_COMBOS];
	static float range_freq[NUM_CARD_COMBOS];

	int HandHash(card_pair hole_cards, bool is_hand_sorted);


	int GetSuitRank(const char card);

	int GetPairedSuitComboVal(char suit_a, char suit_b);

public:

	Range(std::vector<std::pair<card_pair, GameStateNode*>>* range_hole_cards, bool are_hands_sorted);

	Range(std::vector<std::pair<card_pair_and_freq, GameStateNode*>>* range_hole_cards_and_freq, bool are_hands_sorted);


	

	GameStateNode* GetGameStateListPtr(card_pair hole_cards, bool is_hand_sorted);

	float GetHandFrequency(card_pair hole_cards, bool is_hand_sorted);

	void SetGameStateList(card_pair hole_cards, GameStateNode* GameStateList, bool is_hand_sorted);

	void SetHandFrequency(card_pair hole_cards, float freq, bool is_hand_sorted);

	card_pair SortCardPair(card_pair unsorted_hole_cards);


	

};

