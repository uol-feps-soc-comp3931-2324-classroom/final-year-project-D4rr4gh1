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
			if (survivalNeighbours[i] > 26 || survivalNeighbours[i] < 0) {
				throw std::invalid_argument("Invalid number of neighbours");
			}
			survivalRule[survivalNeighbours[i]] = true;
		}
		for (int i = 0; i < birthNeighbours.size(); i++) {
			if (birthNeighbours[i] > 26 || birthNeighbours[i] < 0) {
				throw std::invalid_argument("Invalid number of neighbours");
			}
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

