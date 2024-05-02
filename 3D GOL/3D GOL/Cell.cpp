#include <iostream>
#include <glm/glm.hpp>
#include "Cell.h"
#include "Global.h"


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

void Cell::setCellColor(glm::vec3 color) {
	this->color = color;
}


