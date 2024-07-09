#include "GameStateNode.h"
#include "GameTree.h"
#include "ActionNode.h"

GameStateNode::GameStateNode(int num_actions) :  {

	curr_behavioral_strategy(num_actions);

}

constexpr size_t sizeOfT = sizeof(GameStateNode);