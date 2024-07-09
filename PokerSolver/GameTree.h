#pragma once

#include <vector>
#include <utility>

class GameStateNode;
class Range;
class ActionNode;

class GameTreeConfig {

private:

	/*
	Nested vector stores bet sizes used for each street by each player.
	Nested vector is indexed by depth of tree for current street.
		For example: 
			0th index is reserved for being first player to have aggressive action (bet)
			2nd index is used for 4-bet at current street with following action:
				4-bet for IP player on flop:
					1st Action: IP player bets						(IP_flop_bets[0])
					2nd Action: OOP player raises (3-bets)			(OOP_flop_bets[1])
					3rd Action: IP player raises again (4-bets)		(IP_flop_bets[2])
	*/
	std::vector< ActionNode* > *OOP_flop_bets;
	std::vector< ActionNode* > *OOP_turn_bets;
	std::vector< ActionNode* > *OOP_river_bets;

	std::vector< ActionNode* > *IP_flop_bets;
	std::vector< ActionNode* > *IP_turn_bets;
	std::vector< ActionNode* > *IP_river_bets;

	float effective_stack_size;
	
	std::vector<const char*> flop;

public:
	/*
	Constructors
	*/

	//Creates empty GameTreeConfig object
	GameTreeConfig();

	//Creates GameTreeConfig and sets bet sizes for each player for each street.
	GameTreeConfig(
		std::vector< ActionNode* > OOP_flop_bets,
		std::vector< ActionNode* > OOP_turn_bets,
		std::vector< ActionNode* > OOP_river_bets,
		std::vector< ActionNode* > IP_flop_bets,
		std::vector< ActionNode* > IP_turn_bets,
		std::vector< ActionNode* > IP_river_bets,
		float effective_stack,
		std::vector<const char *> flop_cards
	);

	~GameTreeConfig();

	
	/*
	Game Tree config API
	*/

	/*
	Game Tree Settor API
	*/
	void SetOopFlopBets(std::vector< ActionNode* >* OOP_flop_bets);

	void SetOopTurnBets(std::vector< ActionNode* >* OOP_turn_bets);

	void SetOopRiverBets(std::vector< ActionNode* >* OOP_river_bets);

	void SetIpFlopBets(std::vector< ActionNode* >* IP_flop_bets);

	void SetIpTurnBets(std::vector<ActionNode* >* IP_turn_bets);

	void SetIpRiverBets(std::vector< ActionNode* >* IP_river_bets);

	
	/*
	Game Tree Retrieval API
	*/

	std::vector< ActionNode* >* GetOopFlopBets();

	std::vector< ActionNode* >* GetOopTurnBets();

	std::vector< ActionNode* >* GetOopRiverBets();

	std::vector< ActionNode* >* GetIpFlopBets();

	std::vector< ActionNode* >* GetIpTurnBets();

	std::vector< ActionNode* >* GetIpRiverBets();

};

enum street {
	flop = 0,
	turn = 1,
	river = 2,
};

enum bet_depth {

	check = 0,
	first_bet = 1,
	second_bet = 2,
	third_bet = 3,
	fourth_bet = 4,
	fifth_bet = 5,
	sixth_bet = 6,
	seventh_bet = 7,

};

enum player {
	in_position = 1,
	out_of_position = -1
};

typedef std::pair<const char*, const char*> card_pair;

class GameTree {

private:


	//Constructs all Game State nodes for given hand and player (OOP or IP player)
	void GameStateListConstructor(GameTreeConfig* tree_config, card_pair curr_hand, player player_pos);

	//Returns pointer to newly constructed GameState node for given number of actions.
	GameStateNode* GameStateNodeConstructor(int num_actions);

	//Returns number of strategic actions for a given GameTree configuration, player, street, and bet depth.
	int NumActions(GameTreeConfig* config, player curr_player, street curr_street, bet_depth bet_num);

	//Returns index for GameState node for given player, hand, street, and bet depth.
	int GameStateIndex(player curr_player, card_pair curr_hand, street curr_street, bet_depth curr_bet_depth);

	//Tracks max bet depth for each player for each street for tree navigation.
	short max_IP_flop_depth;
	short max_IP_turn_depth;
	short max_IP_river_depth;

	short max_OOP_flop_depth;
	short max_OOP_turn_depth;
	short max_OOP_river_depth;

public:

	float effective_stack;
	Range* IP_range;
	Range* OOP_range;

	//Constructs static game tree with GameTreeConfiguration and each player's ranges
	GameTree(GameTreeConfig* tree_configuration, Range* IP_range_ptr, Range* OOP_range_ptr, int num_threads);

	GameStateNode* GetGameState(card_pair hole_cards, street curr_street, bet_depth curr_bet_depth);
	
	



};

