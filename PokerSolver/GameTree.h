#pragma once

#include <vector>

class GameStateNode;
class Range;

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
	std::vector< std::vector<float>* > *OOP_flop_bets;
	std::vector< std::vector<float>* > *OOP_turn_bets;
	std::vector< std::vector<float>* > *OOP_river_bets;

	std::vector< std::vector<float>* > *IP_flop_bets;
	std::vector< std::vector<float>* > *IP_turn_bets;
	std::vector< std::vector<float> *> *IP_river_bets;

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
		std::vector< std::vector<float>* > OOP_flop_bets,
		std::vector< std::vector<float>* > OOP_turn_bets,
		std::vector< std::vector<float>* > OOP_river_bets,
		std::vector< std::vector<float>* > IP_flop_bets,
		std::vector< std::vector<float>* > IP_turn_bets,
		std::vector< std::vector<float>* > IP_river_bets,
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
	void SetOopFlopBets(std::vector< std::vector<float>* >* OOP_flop_bets);

	void SetOopTurnBets(std::vector< std::vector<float>* >* OOP_turn_bets);

	void SetOopRiverBets(std::vector< std::vector<float>* >* OOP_river_bets);

	void SetIpFlopBets(std::vector< std::vector<float>* >* IP_flop_bets);

	void SetIpTurnBets(std::vector< std::vector<float>* >* IP_turn_bets);

	void SetIpRiverBets(std::vector< std::vector<float>* >* IP_river_bets);

	
	/*
	Game Tree Retrieval API
	*/

	std::vector< std::vector<float>* >* GetOopFlopBets();

	std::vector< std::vector<float>* >* GetOopTurnBets();

	std::vector< std::vector<float>* >* GetOopRiverBets();

	std::vector< std::vector<float>* >* GetIpFlopBets();

	std::vector< std::vector<float>* >* GetIpTurnBets();

	std::vector< std::vector<float>* >* GetIpRiverBets();

};

class GameTree {

private:



public:

	GameStateNode* root;

	//Constructs static game tree with GameTreeConfiguration and each player's ranges
	GameTree(GameTreeConfig* tree_configuration, Range* IP_range, Range* OOP_range);

	GameStateNode* GetRootGameState();
	



};

