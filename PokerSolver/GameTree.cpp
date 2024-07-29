#include "GameTree.h"
#include "GameTreeConfig.h"

/**

Private Function Definitions

*/

/**
* MaxDepthCurrStreet
* 
* Helper Function for CalculateMaxDepths
*/


MaxDepthPair GameTree::MaxDepthCurrStreet(GameTreeConfig* tree_configuration, Street curr_street) {

	MaxDepthPair max_depth_pair;
	short oop_depth;
	short ip_depth;

	switch (curr_street) {
		case flop:
			oop_depth = tree_configuration->GetOopFlopBets()->size();
			ip_depth = tree_configuration->GetIpFlopBets()->size();
			break;

		case turn:
			oop_depth = tree_configuration->GetOopTurnBets()->size();
			ip_depth = tree_configuration->GetIpTurnBets()->size();
			break;

		case river:
			oop_depth = tree_configuration->GetOopRiverBets()->size();
			ip_depth = tree_configuration->GetIpRiverBets()->size();
			break;
	}

	if (oop_depth - ip_depth > 1) {
		oop_depth = ip_depth + 1;
	}
	if (ip_depth - oop_depth > 1) {
		ip_depth = oop_depth + 1;
	}
	max_depth_pair.oop_max_depth = oop_depth;
	max_depth_pair.ip_max_depth = ip_depth;
	return max_depth_pair;
	
}

/*
CalculateMaxDepth
*/
void GameTree::CalculateMaxDepths(GameTreeConfig* tree_configuration) {

	//NOTE: For each Street, each player's max depth has a maximum difference of 1.
	
	
	//Calculate Max depth for flop for OOP and IP players.
	MaxDepthPair flop_depth_pair = MaxDepthCurrStreet(tree_configuration, flop);
	this->max_depths.max_oop_depth_flop = flop_depth_pair.oop_max_depth;
	this->max_depths.max_ip_depth_flop = flop_depth_pair.ip_max_depth;

	//Calculate Max depth for Turn for OOP and IP players.
	MaxDepthPair turn_depth_pair = MaxDepthCurrStreet(tree_configuration, turn);
	this->max_depths.max_oop_depth_turn = turn_depth_pair.oop_max_depth;
	this->max_depths.max_ip_depth_turn = turn_depth_pair.ip_max_depth;

	//Calculate Max depth for River for OOP and IP players.
	MaxDepthPair river_depth_pair = MaxDepthCurrStreet(tree_configuration, river);
	this->max_depths.max_oop_depth_river = river_depth_pair.oop_max_depth;
	this->max_depths.max_ip_depth_river = river_depth_pair.ip_max_depth;
}


/*
CalculateMaxActions
*/
void GameTree::CalculateMaxActions(GameTreeConfig* tree_configuration) {

	/**
	Subtree A for Street S(S, A) has:
		- A = donk : Even Depth = OOP player, Odd Depth = IP player
		- B = check: Odd Depth = OOP Player, Even Depth = IP player
	*/

	//Flop - SubTree A:




}
