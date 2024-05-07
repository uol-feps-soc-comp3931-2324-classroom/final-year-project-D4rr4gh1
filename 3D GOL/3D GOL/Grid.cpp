#include "Cell.h"
#include "Grid.h"
#include <iostream>
#include "Global.h"


// Define the main function for updating and evolving the Grid/Population
template<>
void Grid<Cell>::updateGrid() {
	// Create a new grid to store the updated cells
	std::vector<std::vector<std::vector<Cell>>> newGrid(this->sizeX, std::vector<std::vector<Cell>>(this->sizeY, std::vector<Cell>(this->sizeZ, this->cell)));;

	// Iterate through each cell in the grid
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				
				// Get the number of alive neighbors for the current cell and update the cell based on the ruleset
				int aliveNeighbors = getAliveNeighbors(i, j, k);

				newGrid[i][j][k] = rules.newCell(cells[i][j][k], aliveNeighbors);
			}
		}
	}

	// Set the grid to the new, updated grid
	cells = newGrid;
}


// Define the function to initialize the grid with random cells
template<>
void Grid<Cell>::initializeGrid() {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			for (int z = 0; z < sizeZ; z++) {
				if ((rand() % 100) < initialCellChance) {
					cells[x][y][z].setState(ALIVE);
					cells[x][y][z].setLifespan(defaultLifeSpan);
				}
			}
		}
	}
}


// Define the function to get the number of alive neighbors for a cell
template<>
int Grid<Cell>::getAliveNeighbors(int x, int y, int z) {
	int aliveNeighbors = 0;

	// Iterate through each neighbor of the cell within one step in each direction
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (i == 0 && j == 0 && k == 0) {
					continue;
				}
				
				// Get the column, row, and depth of the neighbor cell, accounting for wrapping around the grid
				int col = (x + i + sizeX) % sizeX;
				int row = (y + j + sizeY) % sizeY;
				int dep = (z + k + sizeZ) % sizeZ;

				// Ensure the neighbor cell is within the grid
				if (col < 0 || row < 0 || dep < 0 || col >= sizeX || row >= sizeY || dep >= sizeZ) {
					continue;
				}

				// If the neighbor cell is alive and not dying, increment the number of alive neighbors
				if (cells[col][row][dep].getState() == ALIVE && !cells[col][row][dep].getIsDying()) {
					aliveNeighbors++;
				}
			}
		}
	}
	return aliveNeighbors;
}

// Initialise the RPS grid with random cells
template<>
void Grid<RPSCell>::initializeGrid() {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			for (int z = 0; z < sizeZ; z++) {
				auto randState = rand() % 3;

				cells[x][y][z].setState(static_cast<RPSState>(randState));
			}
		}
	}
}

// Define the Rock Paper Scissors function
RPSState Grid<RPSCell>::playRPS(RPSState currentState, int x, int y, int z) {
	int losses{};

	// Iterate through each neighbor of the cell within one step in each direction
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			for (int k = -1; k <= 1; ++k) {
				if (i == 0 && j == 0 && k == 0) continue;
				
				// Get the column, row, and depth of the neighbor cell, accounting for wrapping around the grid
				int col = (x + i + sizeX) % sizeX;
				int row = (y + j + sizeY) % sizeY;
				int dep = (z + k + sizeZ) % sizeZ;

				// If the neighbour cell is the dominating state, increment the number of losses
				if (currentState == ROCK && cells[col][row][dep].getState() == PAPER) losses++;
				else if (currentState == PAPER && cells[col][row][dep].getState() == SCISSORS) losses++;
				else if (currentState == SCISSORS && cells[col][row][dep].getState() == ROCK) losses++;

				
			}
		}
	}

	// If the number of losses is greater than the threshold, return the state of the winning cell
	if(losses > (RPSWinThreshold + (rand() % RPSRandomness))) return static_cast<RPSState>((currentState + 1) % 3);
	return currentState;
}

// Update the RPS grid
template<>
void Grid<RPSCell>::updateGrid() {

	// Create a new grid to store the updated cells
	std::vector<std::vector<std::vector<RPSCell>>> newGrid(this->sizeX, std::vector<std::vector<RPSCell>>(this->sizeY, std::vector<RPSCell>(this->sizeZ, this->cell)));;

	// Iterate through each cell in the grid, setting the new state based on the RPS game
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				RPSState winningState = playRPS(cells[i][j][k].getState(), i, j, k);
				newGrid[i][j][k].setState(winningState);
			}
		}
	}
	// Set the grid to the new, updated grid
	cells = newGrid;
}