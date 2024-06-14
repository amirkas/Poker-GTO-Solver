#pragma once

#include "resource.h"

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <cassert>
#include <algorithm>
#include <set>

//Struct stores information of cards of similar rank 
struct PairAnalysisData {

	int four_of_kind[1];
	int four_of_kind_count;

	int three_of_kind[2];
	int three_of_kind_count;

	int pair[3];
	int pair_count;

	int high_cards[7];
	int high_card_count;
};

typedef struct HandStrength {

	int hand_class;

	//Representation of board using card ranks. 
	int hand[5];
	PairAnalysisData *pair_data;

};

//Class allows for evaluation of hand strength and Comparison of two opponents hands.
class HandEvaluator {

public:

	HandEvaluator();	//Constructor

	~HandEvaluator();	//Deconstructor

	HandStrength* EvaluateHandStrength(std::pair < std::string, std::string>*, std::vector<std::string>*);

	void EvaluateHandStrength(std::vector<std::string>*, HandStrength*);

	int StrongerHand(std::pair < std::string, std::string>*, std::pair < std::string, std::string>*, std::vector<std::string>*);

private:

	std::string ordered_cards;

	std::map<char, int>* card_rank_map;

	std::map<char, int>* card_suit_map;

	//Hand Evaluator Helper methods.
	bool CardRankComparator(std::string, std::string);

	void SortHandByRank(std::pair < std::string, std::string>*, std::vector<std::string>*, std::vector<std::string>*);

	int GetCardRank(std::string);

	char GetCardSuit(std::string);

	bool CheckWheelStraight(std::set<int>*);

	int FindHighestStraight(std::vector<std::string>*);

	int FindHighestStraightFlush(std::vector<std::string>*, int, char);

	void PairAnalysis(std::vector <std::string>*, PairAnalysisData*);

	bool IsStraightPossible(std::vector <std::string>*);

	char IsFlushPossible(std::vector <std::string>*);

}