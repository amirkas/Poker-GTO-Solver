#include "GameStateNode.h"
#include "GameTree.h"
#include "ActionNode.h"

GameStateNode::GameStateNode(GameTreeConfig* tree_config, player player_type, street curr_street, bet_depth curr_bet_depth) {


	std::vector<ActionNode*>* action_list;


	//TODO: implement helper function that returns number of bets for player, street, and bet depth
	switch (player_type) {

		case in_position:

			switch (curr_street) {

				case flop:
					action_list = tree_config->GetIpFlopBets();
					break;

				case turn:
					action_list = tree_config->GetIpTurnBets();
					break;

				case river:
					action_list = tree_config->GetIpRiverBets();
					break;
			}
			break;

		case out_of_position:

			switch (curr_street) {

				case flop:
					action_list = tree_config->GetOopFlopBets();
					break;

				case turn:
					action_list = tree_config->GetOopTurnBets();
					break;

				case river:
					action_list = tree_config->GetOopRiverBets();
					break;
			}
			break;
	}



	

}