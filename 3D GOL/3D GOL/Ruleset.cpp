#include <vector>
#include <iostream>
#include "Ruleset.h"

Cell Ruleset::newCell(Cell currentCell, int neighbours) {
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
		if (!this->survivalRule[neighbours]) {
			newCell.setIsDying(true);
			newCell.setLifespan(lifespan - 1);
		}
	}
	else if (currentState == DEAD) {
		if (this->birthRule[neighbours])
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