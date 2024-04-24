#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"
#include "RPSCell.h"

template <class T>
class Grid {

public:

	std::vector<std::vector<std::vector<T>>> cells;

	Grid(int x, int y, int z) {
		
		sizeX = x;
		sizeY = y;
		sizeZ = z;

		cells = std::vector<std::vector<std::vector<T>>>(sizeX, std::vector<std::vector<T>>(sizeY, std::vector<T>(sizeZ)));
	}
	void initializeGrid();

	void updateGrid();

	int getAliveNeighbors(int x, int y, int z);


private:
	int sizeX, sizeY, sizeZ;
	const int threshold = 10;
	
	const T cell;

	RPSState playRPS(RPSState currentState, int x, int y, int z);
};


#endif // !GRID_H
