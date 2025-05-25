#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>

#define GRIDXSIZE 50
#define GRIDYSIZE 30
#define THRESHOLD 3
#define RANDOM_THRESHOLD_MODIFIER 1
#define SET_SEED -1

int gridGetAtCoords(int x, int y, int grid[GRIDXSIZE][GRIDYSIZE]) {
	if (x < 0 || x >= GRIDXSIZE || y < 0 || y >= GRIDYSIZE) {
		return -1;
	}
	else {
		return grid[x][y];
	}
}

void printHeader() {
	printf("Rock, Paper, Scissors Cellular Automata\n");
	printf("  - Each cell can be in one of 3 states\n");
	printf("  - Each state is strong against another, but weak against the other\n");
	printf("  - Cells that are surrounded by too many cells that they are weak against are 'conquered'\n");
	printf("  - Press Enter to advance the simulation\n");
	printf("\n");
}

void initializeGrid(int grid[GRIDXSIZE][GRIDYSIZE]) {
	for (int i = 0; i < GRIDXSIZE; i++) {
		for (int j = 0; j < GRIDYSIZE; j++) {
			grid[i][j] = rand() % 3;
		}
	}
}


void renderGrid(int grid[GRIDXSIZE][GRIDYSIZE]) {

	for (int j = 0; j < GRIDYSIZE; j++) {
		for (int i = 0; i < GRIDXSIZE; i++) {
			if (grid[i][j] == 0)
			{
				wprintf(L"██");
			}
			else if (grid[i][j] == 1) {
				wprintf(L"░░");
			}
			else {
				wprintf(L"  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void applyRules(int grid[GRIDXSIZE][GRIDYSIZE]) {
	int newGrid[GRIDXSIZE][GRIDYSIZE];
	for (int i = 0; i < GRIDXSIZE; i++) {
		for (int j = 0; j < GRIDYSIZE; j++) {
			newGrid[i][j] = 0;
		}
	}

	for (int i = 0; i < GRIDXSIZE; i++) {
		for (int j = 0; j < GRIDYSIZE; j++) {

			int weakness;
			if (grid[i][j] == 0) {
				weakness = 1;
			}
			else if (grid[i][j] == 1) {
				weakness = 2;
			}
			else {
				weakness = 0;
			}

			//get the number of neighbours that are weaknesses
			int nCount = 0;

			if (gridGetAtCoords(i, j + 1, grid) == weakness)
				nCount++;
			if (gridGetAtCoords(i, j - 1, grid) == weakness)
				nCount++;

			if (gridGetAtCoords(i + 1, j, grid) == weakness)
				nCount++;
			if (gridGetAtCoords(i - 1, j, grid) == weakness)
				nCount++;

			if (gridGetAtCoords(i + 1, j + 1, grid) == weakness)
				nCount++;
			if (gridGetAtCoords(i + 1, j - 1, grid) == weakness)
				nCount++;

			if (gridGetAtCoords(i - 1, j + 1, grid) == weakness)
				nCount++;
			if (gridGetAtCoords(i - 1, j - 1, grid) == weakness)
				nCount++;

			//if the cell has enough surrounding weaknesses
			//compare it to threshold + a random amount
			int r = 0;
			if (RANDOM_THRESHOLD_MODIFIER != 0)
				r = rand() % RANDOM_THRESHOLD_MODIFIER;

			if (nCount >= THRESHOLD + r)
			{
				newGrid[i][j] = weakness;
			}
			else {
				newGrid[i][j] = grid[i][j];
			}

		}
	}

	//copy the new values to the main array
	for (int i = 0; i < GRIDXSIZE; i++) {
		for (int j = 0; j < GRIDYSIZE; j++) {
			grid[i][j] = newGrid[i][j];
		}
	}
}

int main(int argc, char* argv[]) {

	setlocale(LC_CTYPE, "en_US.UTF-8");
	int seed = SET_SEED == -1? time(0) : SET_SEED;
	srand(seed);

	int count = 0;
	int isPlaying = 1;
	int grid[GRIDXSIZE][GRIDYSIZE];

	//user inputs
	int n = 0;
	char inp[50];

	//populate grid
	initializeGrid(grid);


	while (isPlaying == 1) {
		printHeader();

		printf("GENERATION: %d\n", count);
		printf("DIMENSIONS: %d x %d\n", GRIDXSIZE,GRIDYSIZE);
		printf("THRESHOLD: %d\n", THRESHOLD);
		printf("RANDOM_THRESHOLD_MODIFIER: %d\n", RANDOM_THRESHOLD_MODIFIER);
		printf("SEED: %d\n\n", seed);

		renderGrid(grid);
		
		while (1) {
			printf("Press enter to continue. N to exit.  ");
			fgets(inp, 50, stdin);
			inp[strcspn(inp, "\n")] = 0;

			if (strcmp(inp, "n") == 0 || strcmp(inp, "N") == 0) {
				printf("Goodbye!\n");
				isPlaying = 0;
				break;
			}
			else{
				count++;
				system("cls");
				break;
			}
		}

		//apply rps rules
		applyRules(grid);
	}
	return 0;
}
