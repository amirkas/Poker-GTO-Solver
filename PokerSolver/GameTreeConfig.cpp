#include "GameTreeConfig.h"
#include "GameStateNode.h"

/*
Game Tree Config Class Definition
*/


/*
Constructors / Deconstructor definitions
*/


GameTreeConfig::GameTreeConfig() {

	this->OOP_flop_bets = new std::vector<ActionNode*>;
	this->OOP_turn_bets = new std::vector<ActionNode*>;
	this->OOP_river_bets = new std::vector<ActionNode*>;

	this->IP_flop_bets = new std::vector<ActionNode*>;
	this->IP_turn_bets = new std::vector<ActionNode*>;
	this->IP_river_bets = new std::vector<ActionNode*>;

	effective_stack_size = 0.0;
}

GameTreeConfig::GameTreeConfig(
	std::vector< ActionNode* > oop_flop_bets, std::vector< ActionNode* > oop_turn_bets,
	std::vector< ActionNode* > oop_river_bets, std::vector< ActionNode* > ip_flop_bets,
	std::vector< ActionNode* > ip_turn_bets, std::vector< ActionNode* > ip_river_bets,
	float effective_stack,
	std::vector<const char*> flop_cards) {


	this->OOP_flop_bets = new std::vector<ActionNode*>;
	this->OOP_turn_bets = new std::vector<ActionNode*>;
	this->OOP_river_bets = new std::vector<ActionNode*>;

	this->IP_flop_bets = new std::vector<ActionNode*>;
	this->IP_turn_bets = new std::vector<ActionNode*>;
	this->IP_river_bets = new std::vector<ActionNode*>;

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

	delete( this->OOP_flop_bets );
	delete( this->OOP_turn_bets );
	delete( this->OOP_river_bets );
	delete( this->IP_flop_bets );
	delete( this->IP_turn_bets );
	delete( this->IP_river_bets );

}


/*
Settor API definitions
*/

void GameTreeConfig::SetOopFlopBets(std::vector< ActionNode* >* oop_flop_bets) {


	for (size_t i = 0; i < oop_flop_bets->size(); i++) {

		this->OOP_flop_bets->at(i) = std::move(oop_flop_bets->at(i));
	}
}

void GameTreeConfig::SetOopTurnBets(std::vector< ActionNode* >* oop_turn_bets) {

	for (size_t i = 0; i < oop_turn_bets->size(); i++) {

		this->OOP_turn_bets->at(i) = std::move(oop_turn_bets->at(i));
	}

}

void GameTreeConfig::SetOopRiverBets(std::vector< ActionNode* >* oop_river_bets) {

	for (size_t i = 0; i < oop_river_bets->size(); i++) {

		this->OOP_river_bets->at(i) = std::move(oop_river_bets->at(i));
	}
}

void GameTreeConfig::SetIpFlopBets(std::vector< ActionNode* >* ip_flop_bets) {

	for (size_t i = 0; i < ip_flop_bets->size(); i++) {

		this->IP_flop_bets->at(i) = std::move(ip_flop_bets->at(i));
	}

}

void GameTreeConfig::SetIpTurnBets(std::vector< ActionNode* >* ip_turn_bets) {

	for (size_t i = 0; i < ip_turn_bets->size(); i++) {

		this->IP_turn_bets->at(i) = std::move(ip_turn_bets->at(i));
	}
}

void GameTreeConfig::SetIpRiverBets(std::vector< ActionNode* >* ip_river_bets) {

	for (size_t i = 0; i < ip_river_bets->size(); i++) {

		this->IP_river_bets->at(i) = std::move(ip_river_bets->at(i));
	}
}

/*
Retrieval API definitions
*/

std::vector< ActionNode* >* GameTreeConfig::GetOopFlopBets() {

	return this->OOP_flop_bets;
}

std::vector< ActionNode* >* GameTreeConfig::GetOopTurnBets() {

	return this->OOP_turn_bets;
}

std::vector< ActionNode* >* GameTreeConfig::GetOopRiverBets() {

	return this->OOP_river_bets;
}

std::vector< ActionNode* >* GameTreeConfig::GetIpFlopBets() {

	return this->IP_flop_bets;
}

std::vector< ActionNode* >* GameTreeConfig::GetIpTurnBets() {

	return this->IP_turn_bets;
}

std::vector< ActionNode* >* GameTreeConfig::GetIpRiverBets() {

	return this->IP_river_bets;
}