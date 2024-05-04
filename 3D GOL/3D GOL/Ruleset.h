#ifndef RULESET_H
#define RULESET_H

#include <vector>
#include "Cell.h"

class Ruleset {

private:
	bool survivalRule[27] = { false };
	bool birthRule[27] = { false };

public:
	Ruleset(std::vector<int> survivalNeighbours, std::vector<int> birthNeighbours) {
		for (int i = 0; i < survivalNeighbours.size(); i++) {
			survivalRule[survivalNeighbours[i]] = true;
		}
		for (int i = 0; i < birthNeighbours.size(); i++) {
			birthRule[birthNeighbours[i]] = true;
		}
	};

	Ruleset() {
		for (int i = 0; i < 27; i++) {
			survivalRule[i] = false;
			birthRule[i] = false;
		}

		survivalRule[4] = true;
		birthRule[4] = true;
	};

	Cell newCell(Cell currentCell, int neighbours);

};


#endif // !RULESET_H

