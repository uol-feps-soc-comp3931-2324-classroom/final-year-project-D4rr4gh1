#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"
#include "RPSCell.h"
#include "Ruleset.h"

template <class T>
class Grid {

public:

	std::vector<std::vector<std::vector<T>>> cells;

	Grid(int x, int y, int z, Ruleset ruleset) {
		
		sizeX = x;
		sizeY = y;
		sizeZ = z;

		cells = std::vector<std::vector<std::vector<T>>>(sizeX, std::vector<std::vector<T>>(sizeY, std::vector<T>(sizeZ)));

		rules = ruleset;
	}
	void initializeGrid();

	void updateGrid();

	int getAliveNeighbors(int x, int y, int z);


private:
	int sizeX, sizeY, sizeZ;
	
	const T cell;

	RPSState playRPS(RPSState currentState, int x, int y, int z);

	Ruleset rules;
};


#endif // !GRID_H
