#include <iostream>
#include <glm/glm.hpp>
#include "Cell.h"


State Cell::getState() {
    return this->currentState;
}

void Cell::setState(State state) {
    this->currentState = state;
}

int Cell::getLifespan() {
    return lifespan;
}

void Cell::setLifespan(int lifespan) {
    this->lifespan = lifespan;
}

bool Cell::getIsDying() {
    return isDying;
}

void Cell::setIsDying(bool isDying) {
    this->isDying = isDying;
}

glm::vec3 Cell:: getColor() {
    return color;
}

void Cell::updateCell(int neighbours) {


    if (currentState == ALIVE && lifespan == 0) {
   
        currentState = DEAD;
        isDying = false;
        color = glm::vec3(1.0, 0.0, 0.0);
        return;
    }

    if (currentState == ALIVE && isDying) {
            
        lifespan--;
        // Update color from red to yellow as the lifespan decreases
        float redComponent = 1.0;  // Always full red component
        float greenComponent = 1.0 - (float)lifespan / 5.0;  // Gradually increase green component
        color = glm::vec3(redComponent, greenComponent, 0.0);  // No blue component
        return;
    }

    if (currentState == DEAD && (neighbours == 4)) {
            
		currentState = ALIVE;
		lifespan = 2;
		isDying = false;
        return;
    }

    if (currentState == ALIVE && (neighbours != 4)) {
            
		isDying = true;
        return;
	}
}

void Cell::copy(Cell cell) {
    this->currentState = cell.currentState;
    this->lifespan = cell.lifespan;
    this->isDying = cell.isDying;
    this->color = cell.color;
}

