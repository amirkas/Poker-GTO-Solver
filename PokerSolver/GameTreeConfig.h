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


