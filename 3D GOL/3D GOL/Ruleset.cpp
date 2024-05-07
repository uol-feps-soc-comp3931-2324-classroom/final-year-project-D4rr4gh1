#include <vector>
#include <iostream>
#include "Ruleset.h"


// Implement the function to create a new cell based on the ruleset
Cell Ruleset::newCell(Cell currentCell, int neighbours) {

	// Create a new cell
	Cell newCell;


	// Set variables for the cell to be updated for easier use and readability
	State currentState = currentCell.getState();
	bool isDying = currentCell.getIsDying();
	int lifespan = currentCell.getLifespan();


	// Set the new cell's state, lifespan, and color based on the current cell's state, lifespan, and color
	newCell.setState(currentState);
	newCell.setLifespan(lifespan);
	newCell.setIsDying(isDying);
	newCell.setCellColor(currentCell.getColor());

	// Apply the ruleset to the new cell
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

	// If the cell is alive and dying, decrease the lifespan and change the color
	if (newCell.getState() == ALIVE && newCell.getIsDying()) {
		newCell.setLifespan(lifespan - 1);
		newCell.setCellColor(glm::vec3(1.0, 1.0 - ((float)newCell.getLifespan() / defaultLifeSpan), 0.0));
	}

	return newCell;
}