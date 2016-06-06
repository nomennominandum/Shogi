#pragma once
#include "board.h"
class MCTS
{
public:
	MCTS();
	~MCTS();
	void calculateMove(board *tempBoard, int m, vector<vector<int>> *moveVector);
	void makeRollout(board * tempBoard, vector<int>* moveVector);
	void printRollouts(board * tempBoard, int m);
	int findSuitableMove(vector<vector<int>>* moveVector);
};


