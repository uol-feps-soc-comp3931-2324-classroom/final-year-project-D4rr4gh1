#include "Cell.h"
#include "Grid.h"
#include <iostream>

template<>
void Grid<Cell>::updateGrid() {
	std::vector<std::vector<std::vector<Cell>>> newGrid(this->sizeX, std::vector<std::vector<Cell>>(this->sizeY, std::vector<Cell>(this->sizeZ, this->cell)));;

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				
				int aliveNeighbors = getAliveNeighbors(i, j, k);

				cells[i][j][k].updateCell(aliveNeighbors);

				newGrid[i][j][k].copy(cells[i][j][k]);
			}
		}
	}

	cells = newGrid;
}	

template<>
void Grid<Cell>::initializeGrid() {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			for (int z = 0; z < sizeZ; z++) {
				if ((rand() % 100) < 10) {
					cells[x][y][z].setState(ALIVE);
					cells[x][y][z].setLifespan(2);
				}
			}
		}
	}
}

template<>
int Grid<Cell>::getAliveNeighbors(int x, int y, int z) {
	int aliveNeighbors = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (i == 0 && j == 0 && k == 0) {
					continue;
				}
				if (x + i < 0 || x + i >= sizeX || y + j < 0 || y + j >= sizeY || z + k < 0 || z + k >= sizeZ) {
					continue;
				}
				if (cells[x + i][y + j][z + k].getState() == ALIVE) {
					aliveNeighbors++;
				}
			}
		}
	}
	return aliveNeighbors;
}

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


RPSState Grid<RPSCell>::playRPS(RPSState currentState, int x, int y, int z) {
	int losses{};
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			for (int k = -1; k <= 1; ++k) {
				if (i == 0 && j == 0 && k == 0) continue;
				int nx = x + i, ny = y + j, nz = z + k;
				if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY && nz >= 0 && nz < sizeZ) {

					if (currentState == ROCK && cells[nx][ny][nz].getState() == PAPER) losses++;
					else if (currentState == PAPER && cells[nx][ny][nz].getState() == SCISSORS) losses++;
					else if (currentState == SCISSORS && cells[nx][ny][nz].getState() == ROCK) losses++;

				}
			}
		}
	}

	if(losses > (threshold + (rand() % 3))) return static_cast<RPSState>((currentState + 1) % 3);
	return currentState;
}

template<>
void Grid<RPSCell>::updateGrid() {
	std::vector<std::vector<std::vector<RPSCell>>> newGrid(this->sizeX, std::vector<std::vector<RPSCell>>(this->sizeY, std::vector<RPSCell>(this->sizeZ, this->cell)));;

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				RPSState winningState = playRPS(cells[i][j][k].getState(), i, j, k);
				newGrid[i][j][k].setState(winningState);
			}
		}
	}

	cells = newGrid;
}