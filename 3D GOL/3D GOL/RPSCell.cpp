#include <iostream>
#include <glm/glm.hpp>
#include "RPSCell.h"


RPSState RPSCell::getState() {
    return currentState;
}

void RPSCell::setState(RPSState state) {
    this->currentState = state;

    if (state == ROCK) {
        this->color = glm::vec3(1.0, 0.0, 0.0);
    }
    else if (state == PAPER) {
        this->color = glm::vec3(0.0, 1.0, 0.0);
    }
    else {
        this->color = glm::vec3(0.0, 0.0, 1.0);
    }
}

void RPSCell::setColor(glm::vec3 color) {
    this->color = color;
}

glm::vec3 RPSCell::getColor() {
    return color;
}

void RPSCell::updateCell(RPSState winner) {

    if (currentState == ROCK) {
        if (winner == PAPER) {
            currentState = PAPER;
            color = glm::vec3(0.0, 0.0, 1.0);
        }
    }
    else if (currentState == PAPER) {
        if (winner == SCISSORS) {
            currentState = SCISSORS;
            color = glm::vec3(0.0, 1.0, 0.0);
        }
    }
    else {
        if (winner == ROCK) {
            currentState = ROCK;
            color = glm::vec3(1.0, 0.0, 0.0);
        }
    }
}

void RPSCell::copy(RPSCell cell) {
    this->currentState = cell.currentState;
    this->color = cell.color;
}

