#include "Cell.h"
#include "Grid.h"
#include <iostream>
#include "Global.h"

template<>
void Grid<Cell>::updateGrid() {
	std::vector<std::vector<std::vector<Cell>>> newGrid(this->sizeX, std::vector<std::vector<Cell>>(this->sizeY, std::vector<Cell>(this->sizeZ, this->cell)));;

	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			for (int k = 0; k < sizeZ; k++) {
				
				int aliveNeighbors = getAliveNeighbors(i, j, k);

				newGrid[i][j][k] = newCell(cells[i][j][k], aliveNeighbors);
			}
		}
	}

	cells = newGrid;
}

template<>
Cell Grid<Cell>::newCell(Cell currentCell, int neighbours) {
	Cell newCell;

	State currentState = currentCell.getState();
	bool isDying = currentCell.getIsDying();
	int lifespan = currentCell.getLifespan();
	
	newCell.setState(currentState);
	newCell.setLifespan(lifespan);
	newCell.setIsDying(isDying);
	newCell.setCellColor(currentCell.getColor());


	if (currentState == ALIVE && lifespan == 0) {
		newCell.setState(DEAD);
		newCell.setIsDying(true);
		newCell.setCellColor(glm::vec3(0.0, 0.0, 0.0));
	}
	else if (currentState == ALIVE && lifespan == defaultLifeSpan) {
		if (neighbours < 13 || neighbours > 26) {
			newCell.setIsDying(true);
			newCell.setLifespan(lifespan - 1);
		}
	}
	else if (currentState == DEAD) {
		if (neighbours == 13 || neighbours == 14 || neighbours == 17 || neighbours == 18 || neighbours == 19)
		{
			newCell.setState(ALIVE);
			newCell.setIsDying(false);
			newCell.setCellColor(glm::vec3(1.0, 0.0, 0.0));
			newCell.setLifespan(defaultLifeSpan);
		}
	}
	
	if (newCell.getState() == ALIVE && newCell.getIsDying()) {
		newCell.setLifespan(lifespan - 1);
		newCell.setCellColor(glm::vec3(1.0, 1.0 - ((float)newCell.getLifespan() / defaultLifeSpan), 0.0));
	}

	return newCell;
}

template<>
void Grid<Cell>::initializeGrid() {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			for (int z = 0; z < sizeZ; z++) {
				if ((rand() % 100) < 5) {
					cells[x][y][z].setState(ALIVE);
					cells[x][y][z].setLifespan(defaultLifeSpan);
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

				int col = (x + i + sizeX) % sizeX;
				int row = (y + j + sizeY) % sizeY;
				int dep = (z + k + sizeZ) % sizeZ;


				if (col < 0 || row < 0 || dep < 0 || col >= sizeX || row >= sizeY || dep >= sizeZ) {
					continue;
				}

				if (cells[col][row][dep].getState() == ALIVE && !cells[col][row][dep].getIsDying()) {
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
				
				int col = (x + i + sizeX) % sizeX;
				int row = (y + j + sizeY) % sizeY;
				int dep = (z + k + sizeZ) % sizeZ;

				if (currentState == ROCK && cells[col][row][dep].getState() == PAPER) losses++;
				else if (currentState == PAPER && cells[col][row][dep].getState() == SCISSORS) losses++;
				else if (currentState == SCISSORS && cells[col][row][dep].getState() == ROCK) losses++;

				
			}
		}
	}

	if(losses > (RPSWinThreshold + (rand() % RPSRandomness))) return static_cast<RPSState>((currentState + 1) % 3);
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