#include "GameTree.h"
#include "GameStateNode.h"


/*

Game Tree Config Class Definition

*/


/*
Constructors / Deconstructor definitions
*/


GameTreeConfig::GameTreeConfig() {

	this->OOP_flop_bets = new std::vector<std::vector<float>*>;
	this->OOP_turn_bets = new std::vector<std::vector<float>*>;
	this->OOP_river_bets = new std::vector<std::vector<float>*>;

	this->IP_flop_bets = new std::vector<std::vector<float>*>;
	this->IP_turn_bets = new std::vector<std::vector<float>*>;
	this->IP_river_bets = new std::vector<std::vector<float>*>;

	effective_stack_size = 0.0;
}

GameTreeConfig::GameTreeConfig(
	std::vector< std::vector<float>* > oop_flop_bets, std::vector< std::vector<float>* > oop_turn_bets,
	std::vector< std::vector<float>* > oop_river_bets, std::vector< std::vector<float>* > ip_flop_bets,
	std::vector< std::vector<float>* > ip_turn_bets, std::vector< std::vector<float>* > ip_river_bets,
	float effective_stack,
	std::vector<const char*> flop_cards) {

	GameTreeConfig();
	SetOopFlopBets(&oop_flop_bets);
	SetOopTurnBets(&oop_turn_bets);
	SetOopRiverBets(&oop_river_bets);

	SetIpFlopBets(&ip_flop_bets);
	SetIpTurnBets(&ip_turn_bets);
	SetIpRiverBets(&ip_river_bets);

	this->effective_stack_size = effective_stack;
	std::move(this->flop.begin(), this->flop.end(), flop_cards.begin());


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

void GameTreeConfig::SetOopFlopBets(std::vector< std::vector<float>* >* oop_flop_bets) {


	for (size_t i = 0; i < oop_flop_bets->size(); i++) {

		oop_flop_bets->at(i) = new std::vector<float>;
		std::move(oop_flop_bets->at(i)->begin(), oop_flop_bets->at(i)->end(), this->OOP_flop_bets->at(i)->begin());

	}
}

void GameTreeConfig::SetOopTurnBets(std::vector< std::vector<float>* >* oop_turn_bets) {

	for (size_t i = 0; i < oop_turn_bets->size(); i++) {

		oop_turn_bets->at(i) = new std::vector<float>;
		std::move(oop_turn_bets->at(i)->begin(), oop_turn_bets->at(i)->end(), this->OOP_turn_bets->at(i)->begin());
	}
	
}

void GameTreeConfig::SetOopRiverBets(std::vector< std::vector<float>* >* oop_river_bets) {

	for (size_t i = 0; i < oop_river_bets->size(); i++) {

		oop_river_bets->at(i) = new std::vector<float>;
		std::move(oop_river_bets->at(i)->begin(), oop_river_bets->at(i)->end(), this->OOP_river_bets->at(i)->begin());
	}
}

void GameTreeConfig::SetIpFlopBets(std::vector< std::vector<float>* >* ip_flop_bets) {

	for (size_t i = 0; i < ip_flop_bets->size(); i++) {

		ip_flop_bets->at(i) = new std::vector<float>;
		std::move(ip_flop_bets->at(i)->begin(), ip_flop_bets->at(i)->end(), this->IP_flop_bets->at(i)->begin());
	}
	
}

void GameTreeConfig::SetIpTurnBets(std::vector< std::vector<float>* >* ip_turn_bets) {

	for (size_t i = 0; i < ip_turn_bets->size(); i++) {

		ip_turn_bets->at(i) = new std::vector<float>;
		std::move(ip_turn_bets->at(i)->begin(), ip_turn_bets->at(i)->end(), this->IP_turn_bets->at(i)->begin());
	}
}

void GameTreeConfig::SetIpRiverBets(std::vector< std::vector<float>* >* ip_river_bets) {

	for (size_t i = 0; i < ip_river_bets->size(); i++) {

		ip_river_bets->at(i) = new std::vector<float>;
		std::move(ip_river_bets->at(i)->begin(), ip_river_bets->at(i)->end(), this->IP_river_bets->at(i)->begin());
	}
}

/*
Retrieval API definitions
*/

std::vector< std::vector<float>* >* GameTreeConfig::GetOopFlopBets() {

	return this->OOP_flop_bets;
}

std::vector< std::vector<float>* >* GameTreeConfig::GetOopTurnBets() {

	return this->OOP_turn_bets;
}

std::vector< std::vector<float>* >* GameTreeConfig::GetOopRiverBets() {

	return this->OOP_river_bets;
}

std::vector< std::vector<float>* >* GameTreeConfig::GetIpFlopBets() {

	return this->IP_flop_bets;
}

std::vector< std::vector<float>* >* GameTreeConfig::GetIpTurnBets() {

	return this->IP_turn_bets;
}

std::vector< std::vector<float>* >* GameTreeConfig::GetIpRiverBets() {

	return this->IP_river_bets;
}




/*

GameTree Class Definition

*/

GameStateNode* GameTree::GetRootGameState() {
	return root;
}