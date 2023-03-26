#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_
#include "ParticipantsOfTheCompetition.hpp"

struct binaryTree
{
	ParticipantsOfTheCompetition data;
	binaryTree* left;
	binaryTree* right;
};

#endif