#include "GameTree.h"
#include "GameStateNode.h"

/*

GameTree Class Definition

*/

GameTree::GameTree(GameTreeConfig* tree_configuration, Range* IP_range_ptr, Range* OOP_range_ptr, int num_threads) {

	//Assign threads to equally distribute workload.
	//Edge case for 1 thread -> Create Tree for OOP range then IP range.




}

/*
GameTree Constructor Helpers
*/





GameStateNode* GameTree::GameStateNodeConstructor(int num_actions) {

	size_t GameStateSize = 2 * sizeof(float) * num_actions;
	GameStateNode* game_state = new GameStateNode(num_actions);


}



