#include "stdafx.h"
#include "MCTS.h"
#include "board.h"

MCTS::MCTS()
{

}

MCTS::~MCTS()
{
}

void MCTS::calculateMove(board * tempBoard, int m, vector<vector<int>> *moveVector)
{
	srand(static_cast<int>(std::time(NULL)));
	board Board = board((*tempBoard));
	//vector<vector<int>> moveVector;
	Board.returnMoves(&(*moveVector));
	int n = (*moveVector).size();
	for (int i = 0; i < n; i++)
	{
		(*moveVector)[i].push_back(0);
		(*moveVector)[i].push_back(0);
	}

#pragma omp parallel for
		for (int i = 0; i < m; i++)
		{
			int l = rand() % n;
			makeRollout(&Board, &(*moveVector)[l]);
		}
	

}
void MCTS::makeRollout(board *tempBoard, vector<int> *moveVector)
{
	board Board = board(*tempBoard);
	int tempMove = Board.move;
	int org[2], dest[2];
	org[0] = (*moveVector)[0];
	org[1] = (*moveVector)[1];
	dest[0] = (*moveVector)[2];
	dest[1] = (*moveVector)[3];
	Board.makeMove(org, dest);
	int n = 0;
	while (Board.checkMateReturnRandomMove(Board.position))
	{
		n++;
	}
	(*moveVector)[5] = (*moveVector)[5] + 1;
	(*moveVector)[4] = (*moveVector)[4] - Board.move*tempMove;
	
	
}
void MCTS::printRollouts(board *tempBoard, int m)
{
	int sum = 0;
	vector<vector<int>> moveVector;
	calculateMove(&(*tempBoard), m, &moveVector);
	int n = moveVector.size();
	for (int i =0 ;i<n;i++)
	{
		cout << "org " << moveVector[i][0] << " " << moveVector[i][1] << " dest " << moveVector[i][2] << " " << moveVector[i][3];
		cout <<" rolls " << moveVector[i][5] << " points " <<moveVector[i][4] << " efficiency " << ((float)moveVector[i][4]) / ((float)moveVector[i][5]) << endl;
		sum = sum + moveVector[i][4];
	}
	cout << "sum " << sum << endl;
}
int MCTS::findSuitableMove(vector<vector<int>> *moveVector)
{
	int temp = 0;
	int n = (*moveVector).size();
	for (int i = 0; i < n; i++)
	{
		if ((*moveVector)[i][4] > (*moveVector)[temp][4])
			temp = i;
	}
	return temp;
}


