#include "GameTree.h"
#include "GameStateNode.h"


/*

Game Tree Config Class Definition

*/


/*
Constructors / Deconstructor definitions
*/


GameTreeConfig::GameTreeConfig() {

	this->OOP_flop_bets = new std::vector<float>;
	this->OOP_turn_bets = new std::vector<float>;
	this->OOP_river_bets = new std::vector<float>;

	this->IP_flop_bets = new std::vector<float>;
	this->IP_turn_bets = new std::vector<float>;
	this->IP_river_bets = new std::vector<float>;

}

GameTreeConfig::GameTreeConfig(
	std::vector<float> oop_flop_bets, std::vector<float> oop_turn_bets,
	std::vector<float> oop_river_bets, std::vector<float> ip_flop_bets,
	std::vector<float> ip_turn_bets, std::vector<float> ip_river_bets) {

	GameTreeConfig();
	SetOopFlopBets(OOP_flop_bets);
	SetOopTurnBets(OOP_turn_bets);
	SetOopRiverBets(OOP_river_bets);

	SetIpFlopBets(IP_flop_bets);
	SetIpTurnBets(IP_turn_bets);
	SetIpRiverBets(IP_turn_bets);

}

GameTreeConfig::~GameTreeConfig() {

	delete(this->OOP_flop_bets);
	delete(this->OOP_turn_bets);
	delete(this->OOP_river_bets);
	delete(this->IP_flop_bets);
	delete(this->IP_turn_bets);
	delete(this->IP_river_bets);

}


/*
Settor API definitions
*/

void GameTreeConfig::SetOopFlopBets(std::vector<float> oop_flop_bets) {

	std::move(oop_flop_bets.begin(), oop_flop_bets.end(), this->OOP_flop_bets->begin());
}

void GameTreeConfig::SetOopTurnBets(std::vector<float> oop_turn_bets) {

	std::move(oop_turn_bets.begin(), oop_turn_bets.end(), this->OOP_turn_bets->begin());
}

void GameTreeConfig::SetOopRiverBets(std::vector<float> oop_river_bets) {

	std::move(oop_river_bets.begin(), oop_river_bets.end(), this->OOP_river_bets->begin());
}

void GameTreeConfig::SetIpFlopBets(std::vector<float> ip_flop_bets) {

	std::move(ip_flop_bets.begin(), ip_flop_bets.end(), this->IP_flop_bets->begin());
}

void GameTreeConfig::SetIpTurnBets(std::vector<float> ip_turn_bets) {

	std::move(ip_turn_bets.begin(), ip_turn_bets.end(), this->IP_turn_bets->begin());
}

void GameTreeConfig::SetIpRiverBets(std::vector<float> ip_river_bets) {

	std::move(ip_river_bets.begin(), ip_river_bets.end(), this->IP_river_bets->begin());
}

/*
Retrieval API definitions
*/

std::vector<float>* GameTreeConfig::GetOopFlopBets() {

	return this->OOP_flop_bets;
}

std::vector<float>* GameTreeConfig::GetOopTurnBets() {

	return this->OOP_turn_bets;
}

std::vector<float>* GameTreeConfig::GetOopRiverBets() {

	return this->OOP_river_bets;
}

std::vector<float>* GameTreeConfig::GetIpFlopBets() {

	return this->IP_flop_bets;
}

std::vector<float>* GameTreeConfig::GetIpTurnBets() {

	return this->IP_turn_bets;
}

std::vector<float>* GameTreeConfig::GetIpRiverBets() {

	return this->IP_river_bets;
}




/*

GameTree Class Definition

*/