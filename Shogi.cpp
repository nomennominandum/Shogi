// Shogi.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "board.h"
#include "MCTS.h"

int main()
{
	MCTS engine;
	clock_t start;
	start = clock();
	srand(static_cast<int>(std::time(NULL)));
	int sum=0;
		board board1;
		int n = 0;
		int m = 2000;
		while (board1.checkMateReturnRandomMove(board1.position))
		{
			if (n == 50)
			{
				board1.printBoard();
				engine.printRollouts(&board1,m);
			}
			n++;
		}
		//board1.printBoard();
		cout << n;
		cout << "Player " << (board1.move*(-1) + 1) / 2 << " wins" << endl;
		sum = sum + n;
	cout << "gebrauchte Zeit: " << (float)(clock() - start)/CLOCKS_PER_SEC << " durchgeführte Rollouts " << m;
	int x;
	cin >> x;
    return 0;
}

