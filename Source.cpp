#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

// Variables Globales
char** grid;
int** gridRevealed;
int** gridCheck;
bool getBombed = false;


void InitializeGrid(int pGridSize) {

	// grid creation
	grid = new char*[pGridSize];
	gridRevealed = new int*[pGridSize];

	for (int i = 0; i < pGridSize; i++)
	{
		grid[i] = new char[pGridSize];
		for (int j = 0; j < pGridSize; j++)
		{
			grid[i][j] = ' ';
		}
	}

	for (int i = 0; i < pGridSize; i++)
	{
		gridRevealed[i] = new int[pGridSize];
		for (int j = 0; j < pGridSize; j++)
		{
			gridRevealed[i][j] = 0;
		}
	}
	cout << endl;
}

void PrintGrid(int pGridSize) {

	// print grid

	/* Bug a partir d'une grille de taille 11
	cout << "   ";

	for (int i = 0; i < pGridSize; i++)
	{
		cout << " " << i;
	}
	cout << endl;
	*/
	for (int i = 0; i < pGridSize; i++)
	{
		cout << i << " |";
		for (int j = 0; j < pGridSize; j++)
		{
			if (gridRevealed[i][j] == 1)
			{
				cout << " " << grid[i][j];
			}
			else
			{
				cout << " " << 0;
			}
		}
		cout << " |" << endl;
	}
	cout << endl;
}

void CreateBombs(int pGridSize) {

	// placement des bombes

	int bombPlaced = 0;

	while (bombPlaced < pGridSize - 1)
	{
		// cree un number aleatoire uniforme
		mt19937 rngLine;
		rngLine.seed(random_device()());
		mt19937 rngColumn;
		rngColumn.seed(random_device()());
		uniform_int_distribution<mt19937::result_type> random(0, pGridSize - 1);

		int line = random(rngLine);
		int column = random(rngColumn);

		/*cout << endl;
		cout << " line : " << line << endl;
		cout << " row : " << column << endl;
		cout << endl;*/

		// place la bombe

		grid[line][column] = 'b';

		bombPlaced++;
	}
}

void CellsNumbering(int pGridSize) {
	/*
	cases a check autour de chaque cases de la grille (0) :

		{0}{0}{b}
		{0}{x}{0}
		{0}{b}{0}

	(x) est la case dont ont veut afficher le nombre total de bombes (b) autour.
	dans l'exemple au dessus la valeur de (x) doit etre 2. (on trouve 2 (b) autour de (x).

	*/
	int cptBombAround = 0; // nombre de bombes autour de la case.

	for (int i = 0; i < pGridSize; i++)
	{
		for (int j = 0; j < pGridSize; j++)
		{
			if (grid[i][j] != 'b')
			{
				if (i > 0)
				{
					if (j > 0)
					{
						if (grid[i - 1][j - 1] == 'b')
						{
							cptBombAround++;
						}
					}
					if (grid[i - 1][j] == 'b')
					{
						cptBombAround++;
					}
					if (j < pGridSize - 1)
					{
						if (grid[i - 1][j + 1] == 'b')
						{
							cptBombAround++;
						}
					}
					
				}
				
				if (j > 0)
				{
					if (grid[i][j - 1] == 'b') 
					{
						cptBombAround++;
					}
				}
				if (j < pGridSize - 1)
				{
					if (grid[i][j + 1] == 'b')
					{
						cptBombAround++;
					}
				}
				
				if (i < pGridSize - 1)
				{
					if (j > 0)
					{
						if (grid[i + 1][j - 1] == 'b')
						{
							cptBombAround++;
						}
					}
					if (grid[i + 1][j] == 'b')
					{
						cptBombAround++;
					}
					if (j < pGridSize - 1)
					{
						if (grid[i + 1][j + 1] == 'b')
						{
							cptBombAround++;
						}
					}

				}

				// on indique le nombre correspondant au bombe autour de la case
				// bug affichage donc obliger de verifier manuellement chaque cas ( a revoir)

				if (cptBombAround == 0)
				{
					grid[i][j] = ' ';
				}
				if (cptBombAround == 1)
				{
					grid[i][j] = '1';
				}
				if (cptBombAround == 2)
				{
					grid[i][j] = '2';
				}
				if (cptBombAround == 3)
				{
					grid[i][j] = '3';
				}
				if (cptBombAround == 4)
				{
					grid[i][j] = '4';
				}
				if (cptBombAround == 5)
				{
					grid[i][j] = '5';
				}
				if (cptBombAround == 6)
				{
					grid[i][j] = '6';
				}
				if (cptBombAround == 7)
				{
					grid[i][j] = '7';
				}
				if (cptBombAround == 8)
				{
					grid[i][j] = '8';
				}
			}
			cptBombAround = 0;
		}
	}

}

void GridCheckInit(int pGridSize) {

	gridCheck = new int*[pGridSize];
	for (int i = 0; i < pGridSize; i++)
	{
		gridCheck[i] = new int[pGridSize];
		for (int j = 0; j < pGridSize; j++)
		{
			gridCheck[i][j] = 0;
		}
	}
}

void RevealCell(int x, int y, int pGridSize, int lastMove) {
	
	// lastMove : 0 par defaut, 1 haut , 2 bas , 3 gauche , 4 droite

	if (grid[x][y] != 'b' && grid[x][y] != ' ')
	{
		gridCheck[x][y] = 1;
		gridRevealed[x][y] = 1;
		return;
	}
	if (grid[x][y] == 'b')
	{
		gridRevealed[x][y] = 1;
		getBombed = true;
		return;
	}
	if (grid[x][y] == ' ' && lastMove == 0 && gridCheck[x][y] == 0) // par defaut
	{
		gridRevealed[x][y] = 1;
		gridCheck[x][y] = 1;
		if (x > 0)
		{
			RevealCell(x - 1, y, pGridSize, 1);
		}
		if (x < pGridSize - 1)
		{
			RevealCell(x + 1, y, pGridSize, 2);
		}
		if (y > 0)
		{
			RevealCell(x, y - 1, pGridSize, 3);
		}
		if (y < pGridSize - 1)
		{
			RevealCell(x, y + 1, pGridSize, 4);
		}
	}
	if (grid[x][y] == ' ' && lastMove == 1 && gridCheck[x][y] == 0) // derniere case check en bas
	{
		gridRevealed[x][y] = 1;
		gridCheck[x][y] = 1;
		if (x > 0)
		{
			RevealCell(x - 1, y, pGridSize, 1);
		}
		if (y > 0)
		{
			RevealCell(x, y - 1, pGridSize, 3);
		}
		if (y < pGridSize - 1)
		{
			RevealCell(x, y + 1, pGridSize, 4);
		}
	}
	if (grid[x][y] == ' ' && lastMove == 2 && gridCheck[x][y] == 0) // derniere case check en haut
	{
		gridRevealed[x][y] = 1;
		gridCheck[x][y] = 1;
		if (x < pGridSize - 1)
		{
			RevealCell(x + 1, y, pGridSize, 2);
		}
		if (y > 0)
		{
			RevealCell(x, y - 1, pGridSize, 3);
		}
		if (y < pGridSize - 1)
		{
			RevealCell(x, y + 1, pGridSize, 4);
		}
	}
	if (grid[x][y] == ' ' && lastMove == 3 && gridCheck[x][y] == 0) // derniere case check a droite
	{
		gridRevealed[x][y] = 1; 
		gridCheck[x][y] = 1;

		if (x > 0)
		{
			RevealCell(x - 1, y, pGridSize, 1);
		}
		if (x < pGridSize - 1)
		{
			RevealCell(x + 1, y, pGridSize, 2);
		}
		if (y > 0)
		{
			RevealCell(x, y - 1, pGridSize, 3);
		}
	}
	if (grid[x][y] == ' ' && lastMove == 4 && gridCheck[x][y] == 0) // derniere case check a gauche
	{
		gridRevealed[x][y] = 1;
		gridCheck[x][y] = 1;
		if (x > 0)
		{
			RevealCell(x - 1, y, pGridSize, 1);
		}
		if (x < pGridSize - 1)
		{
			RevealCell(x + 1, y, pGridSize, 2);
		}
		if (y < pGridSize - 1)
		{
			RevealCell(x, y + 1, pGridSize, 4);
		}
	}
}

void RevealGrid(int pGridSize) {
	for (int i = 0; i < pGridSize; i++)
	{
		for (int j = 0; j < pGridSize; j++)
		{
			gridRevealed[i][j] = 1;
		}
	}
}

bool CheckVictory(int pGridSize) {
	int cpt = 0; // compteur de case revelée : à (gridSize² - (gridSize -1)) cases revelées le joueur gagne.
	
	for (int i = 0; i < pGridSize; i++)
	{
		for (int j = 0; j < pGridSize; j++)
		{
			if (gridRevealed[i][j] == 1 && grid[i][j] != 'b')
			{
				cpt++;
			}
		}
	}
	if (cpt == ((pGridSize * pGridSize) - (pGridSize - 1)))
	{
		cout << "You won the game." << endl;
		return true;
	}
	return false;
}

int main() {

	int gridSize = 0;
	bool finProgramme = false;
	bool finJeu = false;

	while (!finProgramme)
	{
		cout << "Please enter the grid size. (eg : 3 for 3x3, 5 for 5x5, 10 for 10x10 ...)" << endl;
		cin >> gridSize;

		InitializeGrid(gridSize);
		CreateBombs(gridSize);
		CellsNumbering(gridSize);
		PrintGrid(gridSize);
		while (!finJeu)
		{
			// le joueur choisi une case a reveler.
			int x = 0;
			int y = 0;

			cout << "Please choose a line : (0 to grid size - 1)" << endl;
			cin >> x;
			cout << "Please choose a column : (0 to grid size - 1)" << endl;
			cin >> y;
			cout << endl;

			GridCheckInit(gridSize);
			RevealCell(x, y, gridSize,0);
			PrintGrid(gridSize);
			finJeu = CheckVictory(gridSize);
			if (getBombed)
			{
				cout << "You found a bomb ! Game over !" << endl;
				finJeu = true;
			}
		}
		int rejouer = 0;
		cout << "Play again ? (1 Yes, 2 No)" << endl;
		cin >> rejouer;
		if (rejouer == 2)
		{
			cout << "Goodbye !" << endl;
			finProgramme = true;
			return 0;
		}
		getBombed = false;
		finJeu = false;
		finProgramme = false;
	}

	
	return 0;
}