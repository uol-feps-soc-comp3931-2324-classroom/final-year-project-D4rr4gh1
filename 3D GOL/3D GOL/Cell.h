#ifndef CELL_H
#define CELL_H
#include <glm/glm.hpp>
#include "Global.h"


// Define the State enum
enum State { DEAD, ALIVE };


// Define the Cell class
class Cell {

private:
	State currentState;
	int lifespan;
	bool isDying;
	glm::vec3 color;  // RGB color

	public:
		Cell() : currentState(DEAD), lifespan(0), isDying(false), color(glm::vec3(1.0, 0.0, 0.0)) {}
		Cell(State state, bool deathStatus = false) :
			currentState(state), lifespan(defaultLifeSpan), isDying(deathStatus), color(glm::vec3(1.0, 0.0, 0.0)) {}
		State getState();
		void setState(State state);
		int getLifespan();
		void setLifespan(int lifespan);
		bool getIsDying();
		void setIsDying(bool isDying);
		glm::vec3 getColor();
		void setCellColor(glm::vec3 color);


};



#endif