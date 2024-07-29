#pragma once
#include "utility"
class Range;
class ActionNode;
class GameTreeConfig;

enum Street {
	flop = 0,
	turn = 1,
	river = 2,
};

enum BetDepth {

	check = 0,
	first_bet = 1,
	second_bet = 2,
	third_bet = 3,
	fourth_bet = 4,
	fifth_bet = 5,
	sixth_bet = 6,
	seventh_bet = 7,

};

enum Player {
	in_position = 1,
	out_of_position = -1
};

typedef std::pair<const char*, const char*> CardPair;\

typedef struct SubtreeMaxDepth {
	short max_oop_depth_flop;
	short max_ip_depth_flop;

	short max_oop_depth_turn;
	short max_ip_depth_turn;

	short max_oop_depth_river;
	short max_ip_depth_river;
};

typedef struct SubtreeMaxActionsAtDepth {
	short* max_actions_flop_donk;
	short* max_actions_flop_check;

	short* max_actions_turn_donk;
	short* max_actions_turn_check;

	short* max_actions_river_donk;
	short* max_actions_river_check;
};

typedef struct MaxDepthPair {
	short oop_max_depth;
	short ip_max_depth;
};

class GameTree {

private:
	
	/*
	Six components of tree:
		- 3 Streets and 2 subtrees per street.
		- Each subtree contains action tree from either:
			- Out of Position player donks -> Odd bet depth, d, corresponds to IP player
			- Out of Position player checks -> Odd bet depth, d, corresponds to OOP player
	*/
	float* flop_tree_donk;
	float* flop_tree_check;

	float* turn_tree_donk;
	float* turn_tree_check;

	float* river_tree_donk;
	float* river_tree_check;

	/*
	Records max bet depth for each player for each street.
	Used for GameTree Construction
	*/
	SubtreeMaxDepth max_depths;

	/*
	Records max number of actions at depth d for subtree T that don't result in terminal node. 
	*/
	SubtreeMaxActionsAtDepth max_actions_at_d;

	static MaxDepthPair MaxDepthCurrStreet(GameTreeConfig*, Street curr_street);

	void CalculateMaxDepths(GameTreeConfig* tree_configuration);

	void CalculateMaxActions(GameTreeConfig* tree_configuration);
	

	
	/**
	////Returns pointer to newly constructed GameState node for given number of actions.
	//GameStateNode* GameStateNodeConstructor(int num_actions);

	////Returns number of strategic actions for a given GameTree configuration, player, street, and bet depth.
	//int NumActions(GameTreeConfig* config, player curr_player, street curr_street, bet_depth bet_num);

	////Returns index for GameState node for given player, hand, street, and bet depth.
	//int GameStateIndex(player curr_player, card_pair curr_hand, street curr_street, bet_depth curr_bet_depth);

	////Tracks max bet depth for each player for each street for tree navigation.
	//short max_IP_flop_depth;
	//short max_IP_turn_depth;
	//short max_IP_river_depth;

	//short max_OOP_flop_depth;
	//short max_OOP_turn_depth;
	//short max_OOP_river_depth;
	*/

public:
	
	float starting_pot;
	float effective_stack;
	Range* IP_range;
	Range* OOP_range;

	//Constructs static game tree with GameTreeConfiguration and each player's ranges
	GameTree(GameTreeConfig* tree_configuration, Range* IP_range_ptr, Range* OOP_range_ptr, int num_threads);

	


};