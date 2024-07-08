#pragma once

#include <vector>
class GameTreeConfig;

class GameStateNode {

private:

	std::vector<float> *curr_behavioral_strategy;
	std::vector<float> *total_cumulative_regret;

public:

	GameStateNode(GameTreeConfig* tree_config, player player_type, street curr_street, bet_depth curr_bet_depth);


};

