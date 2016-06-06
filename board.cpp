#include "stdafx.h"
#include "board.h"


	board::board()
	{
		move = 1;
		// initialization position 
		for (int n = 0; n < 9; n++) {
			if( n == 0)
			{position[n][0] = 3;
			position[n][1] = 2;
			position[n][2] = 4;
			position[n][3] = 5;
			position[n][4] = 8;
			position[n][5] = 5;
			position[n][6] = 4;
			position[n][7] = 2;
			position[n][8] = 3;
			}
			else if (n == 1)
			{
				position[n][1] = 6;
				position[n][7] = 7;
			}
			else if (n == 2)
				for (int m = 0; m < 9; m++)
					position[n][m] = 1;
			else if (n == 6)
				for (int m = 0; m < 9; m++)
					position[n][m] = -1;
			else if (n == 7)
			{
				position[n][1] = -7;
				position[n][7] = -6;
			}
			if (n == 8)
			{
				position[n][0] = -3;
				position[n][1] = -2;
				position[n][2] = -4;
				position[n][3] = -5;
				position[n][4] = -8;
				position[n][5] = -5;
				position[n][6] = -4;
				position[n][7] = -2;
				position[n][8] = -3;
			}
			}
			
	}
	board::board(int position2[9][9], int peacesCaptured2[2][7], int move2)
	{
		move = move2;
		for (int i = 0; i<9; i++)
			for (int j = 0; j<9; j++)
				this->position[i][j] = position2[i][j];
		for (int i = 0; i<2; i++)
			for (int j = 0; j<7; j++)
				this->peacesCaptured[i][j] = peacesCaptured2[i][j];

	}

	board::~board()
{
	//delete this->position;
	//delete this->move;
	//delete this->peacesCaptured;
}

	int board::printBoard()
	{
		cout << "Position: " << this->move <<endl;
		for (int n = -1; n < 9; n++)
			cout << setw(3) << n;
		cout << endl;
		for (int n = -1; n < 9; n++)
			cout << setw(3) << "--";
		cout << endl;
		for (int n = 0; n < 9; n++)
		{
			cout << setw(2) << n << "|";
			for (int m = 0; m < 9; m++)
			{
				cout << setw(3)<<position[n][m];
			}
			cout << endl;
		}
		cout << "captured peaces white" << endl;
		for (int m = 0; m < 7; m++)
		{
			cout << setw(2) << m+1;
		}
		cout << endl;
		for (int m = 0; m < 7; m++)
		{
			cout << setw(2) << peacesCaptured[1][m];
		}
		cout << endl<<"captured peaces black" << endl;
		for (int m = 0; m < 7; m++)
		{
			cout << setw(2) << m + 1;
		}
		cout << endl;
		for (int m = 0; m < 7; m++)
		{
			cout << setw(2) << peacesCaptured[0][m];
		}
		cout << endl;
		return 0;
	}

	bool board::makeMove(int org[2], int dest[2])
	{
		int peace = this->move*this->position[org[0]][org[1]];
		if (org[0] == 9) //Figur einsetzen
		{
			if (this->peacesCaptured[(this->move+1)/2][org[1] - 1] != 0) // Check ob Figur eingesetzt werden kann
			{
				if (this->position[dest[0]][dest[1]] != 0) // Zielfeld frei?
					cout << "idiot"<<endl;
				this->peacesCaptured[(this->move+1)/2][org[1] - 1] --;
					this->position[dest[0]][dest[1]] = this->move*org[1];
			}
			else
			{
				cout << "moron";
				return false;
			}
			
		}
		else
		{
			if (this->move*this->position[org[0]][org[1]] > 0) //Ursprungsfeld enthält eine eigene Figur
			{
				if (this->move*this->position[dest[0]][dest[1]] <= 0) //Zielfeld enthält keine Eigene Figur
				{
					if (this->position[dest[0]][dest[1]] != 0) //Zielfeld enthält eine gegnerische Figur
					{
						if (abs(this->position[dest[0]][dest[1]]) >= 100)
							this->position[dest[0]][dest[1]] = this->position[dest[0]][dest[1]] / 100; //Wenn beförderte Figur geschlagen wird
						if (abs(this->position[dest[0]][dest[1]]) > 10)
							this->position[dest[0]][dest[1]] = this->position[dest[0]][dest[1]] / 10; // Wenn Turm+, Läufer+ geschlagen wird
						this->peacesCaptured[(this->move + 1) / 2][abs(this->position[dest[0]][dest[1]]) - 1] ++; //Geschlagene Figur zu den Geschlagenen Figuren hinzufügen
					}
					this->position[org[0]][org[1]] = 0; // Zug ausführen
					this->position[dest[0]][dest[1]] = this->move*peace;
				}
				else
				{
					cout << "wanker" << endl;
					return false;
				}
			}
			else
			{
				cout << "dumbass" << endl;
				return false;
			}
				
		}
		this->promotePeace(peace, org, dest); // Kann eine Figur befördert werden?
		this->move = this->move*(-1); // Zugmarker ändern
		return true;
	}

	bool board::playerMove(void)
	{
		int org[2];
		int dest[2];
		int peace;
		cout << "Bitte Zug eingeben:" << endl;
		cout << "erste Komponente Ursprungsfeld, Enter zweite Komponente" << endl;
		cout << "fuer das Einsetzen einer neuen Figur als erste Komponente 9 eingeben" << endl;
		cout << "als zweite Komponente die Figur die eingesetzt werden soll" << endl;
		cin >> org[0];
		if (org[0] > 9)
		{
			cout << "out of bounds error";
			return false;
		}
			
		cin >> org[1];
		if (org[1] > 9)
		{
			cout << "out of bounds error";
			return false;
		}
		cout << "erste Komponente Zielfeld, Enter zweite Komponente" << endl;
		cin >> dest[0];
		if (dest[0] > 9)
		{
			cout << "out of bounds error";
			return false;
		}
		cin >> dest[1];
		if (dest[1] > 9 )
		{
			cout << "out of bounds error";
			return false;
		}
		if (org[0] == 9)
			peace = org[1];
		else
			peace = abs(position[org[0]][org[1]]);
		if (checkPeaceMove(peace, org, dest))
			if (checkIfPeaceInbetween(peace,org,dest))
				makeMove(org, dest);
			else
			{
				cout << "prick" << endl;
				return false;
			}

		return true;
	}

	bool board::validateMove(int peace, int org[2], int dest[2])
	{
		//if (checkCheck(position))
			//return true;
		//else
			return false;
	}

	bool board::checkCheck(int position[9][9], vector<vector<int>> *moveVector)
	{
		vector<int> king;
		if (!return_position_king(&king))
			cout << "König nicht gefunden!"<< endl;
		this->move = this->move *(-1);
		returnPossibleMoves(position, &(*moveVector),0);
		int m = (*moveVector).size();
		//cout << m << endl;
		for (int p = 0; p < m; p++)
		{
			//cout << "p "<< p << " size "<<(*moveVector)[p].size()<< " size +1 " << (*moveVector)[p+1].size();
			//cout << " p2 "<<(*moveVector)[p][2] << " p3 "<<(*moveVector)[p][3] << endl;
			if (((*moveVector)[p][2] == king[0]) && ((*moveVector)[p][3] == king[1]))
			{
				this->move = this->move*(-1);
				return true;
			}
		}
		this->move = this->move*(-1);
		return false;
	}
	bool board::checkMate(int position[9][9])
	{
		vector<vector<int>> tempVector;
		vector<vector<int>> tempVector2;
		tempVector.reserve(100);
		tempVector.reserve(100);
		if (checkCheck(position, &tempVector2))
		{
			returnPossibleMoves(position, &tempVector,0);
			for (int i = 0; i < tempVector.size(); i++)
				if (!moveResultsInCheck(tempVector[i]))
				{
					//cout << "check but not mate" << endl;
					return false;
				}
			//cout << "mate" << endl;
			//if (move == -1)
				//cout << "white wins" << endl;
			//else
				//cout << "black wins"<<endl;
			return true;
		}
		//cout << "not check" << endl;
		return false;
	}
	bool board::checkMateReturnRandomMove(int position[9][9])
	{
		vector<vector<int>> moveVector;
		moveVector.reserve(100);
		returnPossibleMoves(position, &moveVector, 0);
		moveVector.shrink_to_fit();
		int n = moveVector.size();
		vector<int> randVector;
		randVector.reserve(n);
		for (int i = 0; i<n; i++)
		{
			randVector.push_back(i);
		}
		random_shuffle(randVector.begin(), randVector.end());
		int check = 0;
		for (int i= 0;i<n;i++)
		{
			check = moveResultsInCheck(moveVector[randVector[i]]);
			if (check == 0)
			{
				int org[2];
				int dest[2];
				org[0] = moveVector[randVector[i]][0];
				org[1] = moveVector[randVector[i]][1];
				dest[0] = moveVector[randVector[i]][2];
				dest[1] = moveVector[randVector[i]][3];
				makeMove(org,dest);
				return true;
			}
			

		}
		return false;
	}
	bool board::moveResultsInCheck(const vector<int>& moveVector)
		{
			vector<vector<int>> tempVector;
			tempVector.reserve(100);
			board tempBoard(*this);
			int org[2];
			int dest[2];
			org[0] = (moveVector)[0];
			org[1] = (moveVector)[1];
			dest[0] = (moveVector)[2];
			dest[1] = (moveVector)[3];
			tempBoard.makeMove(org, dest);
			tempBoard.move = tempBoard.move*(-1);
			bool temp = tempBoard.checkCheck(tempBoard.position, &tempVector);
			return temp;
		}

		
	bool board::checkPeaceMove(int peace, int org[2], int dest[2])
	{
		if (org[0] == 9)
			return true;
		int n = peace;
		if (n>=100) //Beförderte Figuren ziehen wie ein Goldgeneral
			n = 5;
		switch (n)
		{
		case 1: //Bauer
			cout << "Bauer"<<endl;
			if (dest[0] - org[0] == move)
			{
				if (org[1] == dest[1])
				{
					return true;
				}
			}
			break;
		case 2: //Springer
			cout << "Springer";
			if (abs(org[1] - dest[1]) == 1)
				if (dest[0] - org[0] == 2*move)
					return true;
			break;
		case 3: //Lanze
			cout << "Lanze";
			if (org[1] == dest[1])
				if (dest[0]*move > org[0]*move)
					return true;
			break;
		case 4: //Silbergeneral
			cout << "Silbergeneral";
			if (dest[0] - org[0] == move)
				if (abs(dest[1] - org[1]) <= 1)
					return true;
			if (dest[0] - org[0] == (-1)*move)
				if (abs(dest[1] - org[1]) == 1)
					return true;
			break;
		case 5: //Goldgeneral
			cout << "Goldgeneral";
			if (dest[0] - org[0] == move)
				if (abs(dest[1] - org[1]) <= 1)
					return true;
			if (dest[0] - org[0] == (-1)*move)
				if (dest[1] == org[1])
					return true;
			if (dest[0] == org[0])
				if (abs(dest[1] - org[1]) == 1)
					return true;
			break;
		case 6: //Turm
			cout << "Turm";
			if (org[1] == dest[1])
				return true;
			if (org[0] == dest[0])
				return true;
			break;
		case 7: //Läufer
			cout << "Läufer";
			if (abs(dest[0] - org[0]) == abs(dest[1] - org[1]) )
				return true;
			break;
		case 8: //König
			cout << "König";
			if (abs(dest[0] - org[0]) <= 1)
				if (abs(dest[1] - org[1]) <= 1)
					return true;
            break;
        case 60: //Turm+
			cout << "Turm+";
			if (abs(dest[0] - org[0]) <= 1)
				if (abs(dest[1] - org[1]) <= 1)
					return true;
			if (org[1] == dest[1])
				return true;
			if (org[0] == dest[0])
				return true;
			break;
		case 70: //Läufer+
			cout << "Läufer+";
			if (abs(dest[0] - org[0]) <= 1)
				if (abs(dest[1] - org[1]) <= 1)
					return true;
			if (abs(dest[0] - org[0]) == abs(dest[1] - org[1]))
				return true;
			break;
		}
		cout<<"false";

		return false;
	}

	void board::promotePeace(int peace, int org[2], int dest[2])
	{

		int temp;
		if (peace < 8)
				if (org[0] != 9)
					if (org[0] * move >= (4 + 2 * move)*move) //Befördern beim Rausziehen
					{
						//cout << "promote1";
						//cout << "Do you want to promote your peace?" << endl;
						//cout << "Enter 1 for yes and 0 for no" << endl;
						//cin >> temp;
						temp = 1;
						if (temp == 1)
							if (peace <6)
								position[dest[0]][dest[1]] = position[dest[0]][dest[1]] * 100; //Beförderung zum Goldgeneral
							else
								position[dest[0]][dest[1]] = position[dest[0]][dest[1]] * 10; //Beförderung zur Dame

					}
					else
					{
						if (dest[0] * move >= (4 + 2 * move)*move) // Befördern beim Reinziehen
						{
							//cout << "promote"<<dest[0]<< " " << (dest[0] * move >= (4 + 2 * move)*move)<<endl;
							//cout << "Do you want to promote your peace?" << endl;
							//cout << "Enter 1 for yes and 0 for no" << endl;
							//cin >> temp;
							temp = 1;
							if (temp == 1)
								if (peace < 6)
								{
									position[dest[0]][dest[1]] = position[dest[0]][dest[1]] * 100;
								}
								else
								{
									position[dest[0]][dest[1]] = position[dest[0]][dest[1]] * 10;
								}
									
						}
					}

	}

	bool board::checkIfPeaceInbetween(int peace, int org[2], int dest[2])
	{// Überprüfe ob die Felder die zwischen Ursprungsfeld und Zielfeld liegen leer sind

		if (org[0] == 9)
			return true; //Figur wird eingesetzt
		int n = peace;
		if (n>=100) //Beförderte Figuren ziehen wie ein Goldgeneral
			n = 5;
		switch (n)
		{
		case 1: //Bauer
			return true; //für Bauer kein Fehler möglich, da dieser nur 1 Feld zieht
			break;
		case 2: //Springer
			return true;//Springer hüpft
			break;
		case 3: //Lanze
			cout << "Lanze";
			for (n = 1; n< abs(dest[0]- org[0]); n++)
				if (position[org[0]+n*move][org[1]]!=0)
					return false;
			break;
		case 4:  // Silbergeneral
			return true; // zieht auch nur 1 Feld
			break;
		case 5: //Goldgeneral
			return true; // zieht auch nur 1 Feld
			break;
		case 6: //Turm
			cout << "Turm";
			if (org[1] == dest[1])
				for (n = 1; n< abs(dest[0] - org[0]); n++)
					if (position[org[0] + (dest[0] - org[0]) / abs(dest[0] - org[0])*n][org[1]] != 0)
						return false;
			if (org[0] == dest[0])
				for (n = 1; n< abs(dest[1] - org[1]); n++)
					if (position[org[0]][org[1] + (dest[1] - org[1]) / abs(dest[1] - org[1])*n] != 0)
						return false;
			break;
		case 7: //Läufer
			cout << "Läufer";
			for (n = 1; n< abs(dest[0]-org[0]); n++)
				if (position[org[0] + (dest[0] - org[0]) / abs(dest[0] - org[0])*n][org[1] + (dest[1] - org[1]) / abs(dest[1] - org[1])*n] != 0)
					return false;
			break;
		case 8: //König
			return true;
			break;
		case 60: //Turm+
			cout << "Turm+";
			if (org[1] == dest[1])
				for (n = 1; n< abs(dest[0] - org[0]); n++)
					if (position[org[0] + (dest[0] - org[0]) / abs(dest[0] - org[0])*n][org[1]] != 0)
						return false;
			if (org[0] == dest[0])
				for (n = 1; n< abs(dest[1] - org[1]); n++)
					if (position[org[0]][org[1] + (dest[1] - org[1]) / abs(dest[1] - org[1])*n] != 0)
						return false;
			break;
		case 70: //Läufer+
			cout << "Läufer+";
			for (n = 1; n< abs(dest[0] - org[0]); n++)
				if (position[org[0] + (dest[0] - org[0]) / abs(dest[0] - org[0])*n][org[1] + (dest[1] - org[1]) / abs(dest[1] - org[1])*n] != 0)
					return false;
			break;
		}
		cout << "true";

		return true;
	}

	void board::returnPossibleMoves(int position[9][9], vector<vector<int>> *moveVector, int flag)
	{
		//vector<vector<int>> moveVector;
		(*moveVector).reserve(100);

			for (int x = 0; x < 9; x++)
//#pragma omp parallel for
				for (int y = 0; y < 9; y++)
				{
					int field[2];
					field[0] = x;
					field[1] = y;
					returnPossibleMovesPeace(field, position, &(*moveVector), flag);

				}
#pragma omp barrier			
		
		//(*moveVector).shrink_to_fit;
	}

	void board::returnPossibleMovesPeace(int field[2], int tempPosition[9][9], vector<vector<int>> *moveVector, int flag)
	{
		int m = 0;
		int peace = this->move*position[field[0]][field[1]];
		int n = peace;
		if (n >= 100) //Beförderte Figuren ziehen wie ein Goldgeneral
		{
			n = 5;
		}
		switch (n)
		{
		case 0: //Figur einsetzen
			for (int k = 1; k < 8; k++)
			{
				if (k == 1)
				{
					if (this->check_pawn(field[1]))
						if (this->peacesCaptured[(this->move + 1) / 2][k-1] != 0)
						{
							vector<int> temp; //malloc?
							temp.push_back(9);
							temp.push_back(k);
							temp.push_back(field[0]);
							temp.push_back(field[1]);
#pragma omp critical
							(*moveVector).push_back(temp);
							if ((flag == 1))
								if (moveResultsInCheck(temp))
								{
									cout << "check";
									(*moveVector).pop_back();
								}
									
						}
				}
				else
					if (this->peacesCaptured[(this->move + 1) / 2][k-1] != 0)
					{
						vector<int> temp; //malloc?
						temp.push_back(9);
						temp.push_back(k);
						temp.push_back(field[0]);
						temp.push_back(field[1]);
#pragma omp critical
						(*moveVector).push_back(temp);
						if ((flag == 1))
							if (moveResultsInCheck(temp))
							{
								cout << "check";
								(*moveVector).pop_back();
							}
					}
			}
			break;

		case 1: //Bauer zieht 1 Feld
			this->moveVorward(1,field[0],field[1],&(*moveVector),flag);
			break;

		case 2: // Springer zieht
			if (!out_of_bounds_error(field[0] + 2 * this->move, field[1] - 1))
				if (this->move*position[field[0] + 2 * this->move][field[1] - 1] <= 0)
				{
					vector<int> temp; //malloc?
					temp.push_back(field[0]);
					temp.push_back(field[1]);
					temp.push_back(field[0] + 2 * this->move);
					temp.push_back(field[1] - 1);
					if (flag == 1)
						if (moveResultsInCheck(temp))
							break;
#pragma omp critical
					(*moveVector).push_back(temp);
				}
			if (!out_of_bounds_error(field[0] + 2 * this->move, field[1] + 1))
				if (this->move*position[field[0] + 2 * this->move][field[1] + 1] <= 0)
				{
					vector<int> temp; //malloc?
					temp.push_back(field[0]);
					temp.push_back(field[1]);
					temp.push_back(field[0] + 2 * this->move);
					temp.push_back(field[1] + 1);
					if (flag == 1)
						if (moveResultsInCheck(temp))
							break;
#pragma omp critical
					(*moveVector).push_back(temp);
				}
			break;
		case 3: //Lanze
			m = 0;
			while ((this->move*position[field[0] + (m + 1)*this->move][field[1]]< 1) &&(!out_of_bounds_error(field[0] + (m+1) * this->move, field[1])))
			{
				if (this->move*position[field[0] + (m + 1)*this->move][field[1]] < 0)
				{
					this->moveVorward(m+1,field[0], field[1], &(*moveVector),flag);
					break;
				}
				this->moveVorward(m+1,field[0], field[1], &(*moveVector),flag);
				m = m + 1;
			}
			break;
		case 4: //Silbergeneral
			this->moveVorward(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackwardLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackwardRight(1,field[0], field[1], &(*moveVector), flag);
			break;
		case 5: //Goldgeneral
			this->moveVorward(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackward(1,field[0], field[1], &(*moveVector), flag);
			break;

		case 6: //Turm
			m = 0; //vorwärts
			if (!out_of_bounds_error(field[0] + (m + 1) * this->move, field[1]))
			while (this->move*position[field[0] + (m + 1)*this->move][field[1]] < 1)
			{
				if (this->move*position[field[0] + (m + 1)*this->move][field[1]] < 0)
				{
					this->moveVorward(m+1,field[0], field[1], &(*moveVector), flag);
					break;
				}
				this->moveVorward(m+1,field[0], field[1], &(*moveVector), flag);
				m = m + 1;
				if (out_of_bounds_error(field[0] + m * this->move, field[1]))
					break;
			}
			m = 0; //rückwerts
			if (!out_of_bounds_error(field[0] - (m + 1) * this->move, field[1]))
			while (this->move*position[field[0] - (m + 1)*this->move][field[1]] < 1)
			{
				if (this->move*position[field[0] - (m + 1)*this->move][field[1]] < 0)
				{
					this->moveBackward(m+1,field[0], field[1], &(*moveVector), flag);
					break;
				}
				this->moveBackward(m+1,field[0], field[1], &(*moveVector), flag);
				m = m + 1;
				if (out_of_bounds_error(field[0] - m * this->move, field[1]))
					break;
			}
			m = 0; //rechts
			if (!out_of_bounds_error(field[0] , field[1] + (m + 1)))
			while (this->move*position[field[0] ][field[1] + (m + 1)] < 1)
			{
				if (this->move*position[field[0]][field[1] + (m + 1)] < 0)
				{
					this->moveRight(m+1,field[0], field[1], &(*moveVector), flag);
					break;
				}
				this->moveRight(m+1,field[0], field[1], &(*moveVector), flag);
				m = m + 1;
				if (out_of_bounds_error(field[0], field[1] + (m + 1)))
					break;
			}
			m = 0; //links
			if (!out_of_bounds_error(field[0], field[1] - (m + 1)))
			while (this->move*position[field[0]][field[1] - (m + 1)] < 1)
			{
				if (this->move*position[field[0]][field[1] - (m + 1)] < 0)
				{
					this->moveLeft(m+1,field[0], field[1], &(*moveVector), flag);
					break;
				}
				this->moveLeft(m+1,field[0], field[1], &(*moveVector), flag);
				m = m + 1;
				if (out_of_bounds_error(field[0], field[1] - (m + 1)))
					break;
			}
	
			break;

		case 7: //Läufer
			m = 0; //vorwärts rechts
			if (!out_of_bounds_error(field[0]+(m+1)*this->move, field[1] + (m + 1)))
			while (this->move*position[field[0] + (m + 1)*this->move][field[1]+m+1] < 1)
			{
				if (this->move*position[field[0] + (m + 1)*this->move][field[1]+m+1] < 0)
				{
					this->moveVorwardRight(m+1,field[0], field[1], &(*moveVector), flag);
					break;
				}
				this->moveVorwardRight(m+1,field[0], field[1], &(*moveVector), flag);
				m = m + 1;
				if (out_of_bounds_error(field[0]+(m+1)*this->move, field[1] + m+1))
					break;
			}
			m = 0; //vorwärts links
			if (!out_of_bounds_error(field[0] + (m + 1)*this->move, field[1] - (m + 1)))
				while (this->move*position[field[0] + (m + 1)*this->move][field[1] - m + 1] < 1)
				{
					if (this->move*position[field[0] + (m + 1)*this->move][field[1] - m + 1] < 0)
					{
						this->moveVorwardLeft(m+1,field[0], field[1], &(*moveVector), flag);
						break;
					}
					this->moveVorwardLeft(m+1,field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] + (m + 1)*this->move, field[1] - m + 1))
						break;
				}
			m = 0; //rückwerts links
			if (!out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] - (m + 1)))
				while (this->move*position[field[0] - (m + 1)*this->move][field[1] - m + 1] < 1)
				{
					if (this->move*position[field[0] - (m + 1)*this->move][field[1] - m + 1] < 0)
					{
						this->moveBackwardLeft(m+1,field[0], field[1], &(*moveVector), flag);
						break;
					}
					this->moveBackwardLeft(m+1,field[0], field[1] , &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] - m + 1))
						break;
				}
			m = 0; //rückwerts rechts
			if (!out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] + (m + 1)))
				while (this->move*position[field[0] - (m + 1)*this->move][field[1] + m + 1] < 1)
				{
					if (this->move*position[field[0] - (m + 1)*this->move][field[1] + m + 1] < 0)
					{
						this->moveBackwardRight(m+1,field[0], field[1], &(*moveVector), flag);
						break;
					}
					this->moveBackwardRight(m+1,field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] + m + 1))
						break;
				}
			
			break;

		case 8: //König
			this->moveVorward(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackward(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackwardRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackwardLeft(1,field[0], field[1], &(*moveVector), flag);
			break;

		case 60: //Turm +
			this->moveVorwardRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveVorwardLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackwardRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackwardLeft(1,field[0], field[1], &(*moveVector), flag);
			m = 0; //vorwärts
			if (!out_of_bounds_error(field[0] + (m + 1) * this->move, field[1]))
				while (this->move*position[field[0] + (m + 1)*this->move][field[1]] < 1)
				{
					if (this->move*position[field[0] + (m + 1)*this->move][field[1]] < 0)
					{
						moveVorward(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveVorward(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] + m * this->move, field[1]))
						break;
				}
			m = 0; //rückwerts
			if (!out_of_bounds_error(field[0] - (m + 1) * this->move, field[1]))
				while (this->move*position[field[0] - (m + 1)*this->move][field[1]] < 1)
				{
					if (this->move*position[field[0] - (m + 1)*this->move][field[1]] < 0)
					{
						moveBackward(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveBackward(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] - m * this->move, field[1]))
						break;
				}
			m = 0; //rechts
			if (!out_of_bounds_error(field[0], field[1] + (m + 1)))
				while (this->move*position[field[0]][field[1] + (m + 1)] < 1)
				{
					if (this->move*position[field[0]][field[1] + (m + 1)] < 0)
					{
						moveRight(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveRight(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0], field[1] + (m + 1)))
						break;
				}
			m = 0; //links
			if (!out_of_bounds_error(field[0], field[1] - (m + 1)))
				while (this->move*position[field[0]][field[1] - (m + 1)] < 1)
				{
					if (this->move*position[field[0]][field[1] - (m + 1)] < 0)
					{
						moveLeft(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveLeft(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0], field[1] - (m + 1)))
						break;
				}
			break;

		case 70: //Läufer+
			this->moveVorward(1,field[0], field[1],&(*moveVector), flag);
			this->moveRight(1,field[0], field[1], &(*moveVector), flag);
			this->moveLeft(1,field[0], field[1], &(*moveVector), flag);
			this->moveBackward(1,field[0], field[1], &(*moveVector), flag);
			m = 0; //vorwärts rechts
			if (!out_of_bounds_error(field[0] + (m + 1)*this->move, field[1] + (m + 1)))
				while (this->move*position[field[0] + (m + 1)*this->move][field[1] + m + 1] < 1)
				{
					if (this->move*position[field[0] + (m + 1)*this->move][field[1] + m + 1] < 0)
					{
						moveVorwardRight(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveVorwardRight(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] + (m + 1)*this->move, field[1] + m + 1))
						break;
				}
			m = 0; //vorwärts links
			if (!out_of_bounds_error(field[0] + (m + 1)*this->move, field[1] - (m + 1)))
				while (this->move*position[field[0] + (m + 1)*this->move][field[1] - m + 1] < 1)
				{
					if (this->move*position[field[0] + (m + 1)*this->move][field[1] - m + 1] < 0)
					{
						moveVorwardLeft(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveVorwardLeft(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] + (m + 1)*this->move, field[1] - m + 1))
						break;
				}
			m = 0; //rückwerts links
			if (!out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] - (m + 1)))
				while (this->move*position[field[0] - (m + 1)*this->move][field[1] - m + 1] < 1)
				{
					if (this->move*position[field[0] - (m + 1)*this->move][field[1] - m + 1] < 0)
					{
						moveBackwardLeft(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveBackwardLeft(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] - m + 1))
						break;
				}
			m = 0; //rückwerts rechts
			if (!out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] + (m + 1)))
				while (this->move*position[field[0] - (m + 1)*this->move][field[1] + m + 1] < 1)
				{
					if (this->move*position[field[0] - (m + 1)*this->move][field[1] + m + 1] < 0)
					{
						moveBackwardRight(m + 1, field[0], field[1], &(*moveVector), flag);
						break;
					}
					moveBackwardRight(m + 1, field[0], field[1], &(*moveVector), flag);
					m = m + 1;
					if (out_of_bounds_error(field[0] - (m + 1)*this->move, field[1] + m + 1))
						break;
				}
			break;
		default:
			break;

		}

		
	}

	void board::returnMoves(vector<vector<int>> *moveVector)
	{
		(*moveVector).reserve(100);
		returnPossibleMoves(position, &(*moveVector), 1);
		(*moveVector).shrink_to_fit();
		int n = (*moveVector).size();
				
	}

	void board::returnRandomMove()
	{
		vector<vector<int>> moveVector;
		moveVector.reserve(100);
		returnPossibleMoves(position, &moveVector,0);
		moveVector.shrink_to_fit();
		int n = moveVector.size();
		vector<int> randVector;
		randVector.reserve(n);
		for (int i=0;i<n;i++)
		{
			randVector.push_back(i);
		}
		random_shuffle(randVector.begin(), randVector.end());
		bool check = 1;
		int j = n - 1;
		while (check)
		{
			check = moveResultsInCheck(moveVector[randVector[j]]);
			if (check == 1)
			{
				randVector.pop_back();
				j--;
			}

		}
		int l = randVector[j];
			int org[2];
			int dest[2];
			org[0] = moveVector[l][0];
			org[1] = moveVector[l][1];
			dest[0] = moveVector[l][2];
			dest[1] = moveVector[l][3];
		this->makeMove(org, dest);
	}
    bool board::out_of_bounds_error(int field0,int field1)
    {
        if(field0<0)
            return true;
        if(field1<0)
            return true;
        if(field0>8)
            return true;
        if(field1>8)
            return true;
        return false;
    }

	bool board::check_pawn(int row)
	{
		for (int i = 0; i<9; i ++)
			if (position[i][row] == move)
				return false;
		
		return true;
	}

	void board::moveRight(int m, int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if(!out_of_bounds_error(field0,field1+m))
		if (this->move*position[field0][field1 + m] <= 0)
		{
			vector<int> temp; //malloc?
			temp.push_back(field0);
			temp.push_back(field1);
			temp.push_back(field0 );
			temp.push_back(field1 + m);
#pragma omp critical
			(*moveVector).push_back(temp);
			if ((flag == 1))
				if (moveResultsInCheck(temp))
				{
					(*moveVector).pop_back();
				}
		}
	}
	void board::moveLeft(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0, field1 - m))
			if (this->move*position[field0][field1 - m] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0);
				temp.push_back(field1 - m);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
					{
						(*moveVector).pop_back();
					}
			}
	}
	void board::moveVorward(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0+m*this->move, field1))
			if (this->move*position[field0+m*this->move][field1] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0+m*this->move);
				temp.push_back(field1);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
						(*moveVector).pop_back();
			}
	}
	void board::moveBackward(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0 - m*this->move, field1))
			if (this->move*position[field0 - m*this->move][field1] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0 - m*this->move);
				temp.push_back(field1);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
						(*moveVector).pop_back();
			}
	}
	void board::moveVorwardRight(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0 + m*this->move, field1+m))
			if (this->move*position[field0 + m*this->move][field1+m] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0 +m* this->move);
				temp.push_back(field1+m);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
						(*moveVector).pop_back();
			}
	}
	void board::moveVorwardLeft(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0 +m* this->move, field1 - m))
			if (this->move*position[field0 + m*this->move][field1 - m] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0 + m*this->move);
				temp.push_back(field1 - m);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
						(*moveVector).pop_back();
			}
	}
	void board::moveBackwardLeft(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0 - m*this->move, field1 - m))
			if (this->move*position[field0 - m*this->move][field1 - m] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0 - m*this->move);
				temp.push_back(field1 - m);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
						(*moveVector).pop_back();
			}
	}
	void board::moveBackwardRight(int m,int field0, int field1, vector<vector<int>> *moveVector, int flag)
	{
		if (!out_of_bounds_error(field0 - m*this->move, field1 + m))
			if (this->move*position[field0 - m*this->move][field1 + m] <= 0)
			{
				vector<int> temp; //malloc?
				temp.push_back(field0);
				temp.push_back(field1);
				temp.push_back(field0 - m*this->move);
				temp.push_back(field1 + m);
#pragma omp critical
				(*moveVector).push_back(temp);
				if ((flag == 1))
					if (moveResultsInCheck(temp))
						(*moveVector).pop_back();
			}
	}
	bool board::return_position_king(vector<int> *king)
	{
		for (int i =0;i<9;i++)
			for(int j=0;j<9;j++)
				if (this->position[i][j] == this->move * 8)
				{
					(*king).push_back(i);
					(*king).push_back(j);
					return true;
				}
		return false;
	}
	void board::setPosition(int position2[9][9], int peacesCaptured2[2][7])
	{
		for(int i = 0;i<9;i++)
			for(int j =0;j<9;j++)
				this->position[i][j] = position2[i][j];
		for (int i = 0; i<2; i++)
			for (int j = 0; j<7; j++)
				this->peacesCaptured[i][j] = peacesCaptured2[i][j];

	}





