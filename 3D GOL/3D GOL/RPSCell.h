#ifndef RPSCELL_H
#define RPSCELL_H


enum RPSState { ROCK, PAPER, SCISSORS };

class RPSCell {

private:

	RPSState currentState;
	glm::vec3 color;  // RGB color

public:
	RPSCell() : currentState(ROCK), color(glm::vec3(1.0, 0.0, 0.0)) {}

	RPSCell(RPSState state) : currentState(state) {
		if (state == ROCK) {
			color = glm::vec3(1.0, 0.0, 0.0);
		}
		else if (state == PAPER) {
			color = glm::vec3(0.0, 1.0, 0.0);
		}
		else {
			color = glm::vec3(0.0, 0.0, 1.0);
		}
	}

	RPSState getState();
	void setState(RPSState state);
	glm::vec3 getColor();
	void setColor(glm::vec3 color);
	void updateCell(RPSState winner);
	void copy(RPSCell cell);

};



#endif // !RPSCELL_H

