#pragma once

#include <vector>
enum Street {
	flop = 0,
	turn = 1,
	river = 2,
};
class ActionNode {

private:

	std::vector<float> actions;

public:

	ActionNode(std::vector<float> input_actions);

	float PotSizeAfterAction(int action_index, float initial_potsize, float effective_stack, Street current_street);

};

