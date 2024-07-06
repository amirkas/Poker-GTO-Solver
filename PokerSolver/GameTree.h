#pragma once

#include <vector>

class GameStateNode;

class GameTreeConfig {

private:

	std::vector<float> *OOP_flop_bets;
	std::vector<float> *OOP_turn_bets;
	std::vector<float> *OOP_river_bets;

	std::vector<float> *IP_flop_bets;
	std::vector<float> *IP_turn_bets;
	std::vector<float> *IP_river_bets;
	

public:
	/*
	Constructors
	*/

	//Creates empty GameTreeConfig object
	GameTreeConfig();

	//Creates GameTreeConfig and sets bet sizes for each player for each street.
	GameTreeConfig(
		std::vector<float> OOP_flop_bets,
		std::vector<float> OOP_turn_bets,
		std::vector<float> OOP_river_bets,
		std::vector<float> IP_flop_bets,
		std::vector<float> IP_turn_bets,
		std::vector<float> IP_river_bets
	);

	~GameTreeConfig();

	
	/*
	Game Tree config API
	*/

	/*
	Game Tree Settor API
	*/
	void SetOopFlopBets(std::vector<float> OOP_flop_bets);

	void SetOopTurnBets(std::vector<float> OOP_turn_bets);

	void SetOopRiverBets(std::vector<float> OOP_river_bets);

	void SetIpFlopBets(std::vector<float> IP_flop_bets);

	void SetIpTurnBets(std::vector<float> IP_turn_bets);

	void SetIpRiverBets(std::vector<float> IP_river_bets);

	
	/*
	Game Tree Retrieval API
	*/

	std::vector<float>* GetOopFlopBets();

	std::vector<float>* GetOopTurnBets();

	std::vector<float>* GetOopRiverBets();

	std::vector<float>* GetIpFlopBets();

	std::vector<float>* GetIpTurnBets();

	std::vector<float>* GetIpRiverBets();

};

class GameTree {

public:

	GameStateNode* root;

	GameTree();

	GameStateNode* GetRootGameState;
	
private:


};

