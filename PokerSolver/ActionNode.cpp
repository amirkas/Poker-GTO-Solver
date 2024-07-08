#include "ActionNode.h"

ActionNode::ActionNode(std::vector<float> input_actions) {
	std::move(this->actions.begin(), this->actions.end(), input_actions.begin());
}

float ActionNode::PotSizeAfterAction(int action_index, float initial_pot_size,
									 float effective_stack, street current_street) {

	float action = actions.at(action_index);
	
	//If float less than zero, using geometric sizing based on current street.
	int next_pot_size;
	if (action < 0) {
		//TODO:
		next_pot_size = initial_pot_size;
	}
	else {
		
		next_pot_size = (1.0 + action) * initial_pot_size;
	}
	return next_pot_size;
}