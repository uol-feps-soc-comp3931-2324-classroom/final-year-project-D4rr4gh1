#include "pch.h"
#include "../3D GOL/Cell.h"
#include "../3D GOL/RPSCell.h"
#include "../3D GOL/Grid.h"
#include "../3D GOL/Cell.cpp"
#include "../3D GOL/RPSCell.cpp"
#include "../3D GOL/Grid.cpp"
#include "../3D GOL/Global.h"
#include "../3D GOL/Ruleset.h"
#include "../3D GOL/Ruleset.cpp"
#include <gtest/gtest.h>

int initialCellChance = 10;
int defaultLifeSpan = 5;
std::vector<int> survivalNeighbours = { 4 };
std::vector<int> birthNeighbours = { 4 };

int RPSWinThreshold = 10;
int RPSRandomness = 5; 

Cell cell(ALIVE, false);
Cell cell2(DEAD, false);

RPSCell rockCell(ROCK);
RPSCell paperCell(PAPER);
RPSCell scissorsCell(SCISSORS);

Ruleset ruleset(survivalNeighbours, birthNeighbours);


Grid<Cell> grid(3, 3, 3, ruleset);
Grid<RPSCell> rpsGrid(3, 3, 3, ruleset);

// Test the default state of Cell
TEST(CellTest, DefaultState) {
    Cell cell;
    EXPECT_EQ(cell.getState(), DEAD);  
}

// Test the state transition of Cell
TEST(CellTest, StateTransition) {
    Cell cell;
    cell.setState(ALIVE);  
    EXPECT_EQ(cell.getState(), ALIVE);
}

// Test default RPSCell 
TEST(RPSCellTest, DefaultState) {
    RPSCell rpsCell;
    EXPECT_EQ(rpsCell.getState(), ROCK);  
}

// Test RPSCell state transition
TEST(RPSCellTest, StateTransition) {
    RPSCell rpsCell;
    rpsCell.setState(ROCK);  
    EXPECT_EQ(rpsCell.getState(), ROCK);
}

// Test RPSCell update
TEST(RPSCellTest, Update) {
	RPSCell rpsCell(ROCK);
	rpsCell.updateCell(PAPER);  
	EXPECT_EQ(rpsCell.getState(), PAPER);
}

// Test RPSCell update
TEST(RPSCellTest, Update2) {
	RPSCell rpsCell(PAPER);
	rpsCell.updateCell(SCISSORS);  
	EXPECT_EQ(rpsCell.getState(), SCISSORS);
}

// Test RPSCell update
TEST(RPSCellTest, Update3) {
	RPSCell rpsCell(SCISSORS);
	rpsCell.updateCell(ROCK);  
	EXPECT_EQ(rpsCell.getState(), ROCK);
}

// Test RPSCell update
TEST(RPSCellTest, Update4) {
	RPSCell rpsCell(ROCK);
	rpsCell.updateCell(SCISSORS);
	EXPECT_EQ(rpsCell.getState(), ROCK);
}

TEST(GridTest, NeighbourCountTest) {
	// Check if the number of alive neighbours is correct
	Grid<Cell> largeGrid(10, 10, 10, ruleset);
	largeGrid.cells[0][0][0].setState(ALIVE);
	largeGrid.cells[0][0][1].setState(ALIVE);
	largeGrid.cells[0][1][0].setState(ALIVE);
	largeGrid.cells[0][1][1].setState(ALIVE);
	largeGrid.cells[1][0][0].setState(ALIVE);
	largeGrid.cells[1][0][1].setState(ALIVE);
	largeGrid.cells[1][1][0].setState(ALIVE);
	largeGrid.cells[1][1][1].setState(ALIVE);

	

	EXPECT_EQ(largeGrid.getAliveNeighbors(0, 0, 0), 7);
	EXPECT_EQ(largeGrid.getAliveNeighbors(1, 1, 1), 7);
	EXPECT_EQ(largeGrid.getAliveNeighbors(0, 0, 1), 7);
	EXPECT_EQ(largeGrid.getAliveNeighbors(7, 10, 3), 0);

}

TEST(GridTest, NeighbourCount2) {
	Grid<Cell> largeGrid(10, 10, 10, ruleset);
	largeGrid.cells[0][0][0].setState(ALIVE);
	largeGrid.cells[1][0][0].setState(ALIVE);
	largeGrid.cells[0][1][0].setState(ALIVE);
	largeGrid.cells[1][1][0].setState(ALIVE);

	EXPECT_EQ(largeGrid.getAliveNeighbors(0, 0, 1), 4);
	EXPECT_EQ(largeGrid.cells[0][0][0].getIsDying(), false);

	largeGrid.updateGrid();

	EXPECT_TRUE(largeGrid.cells[0][0][0].getIsDying());
	EXPECT_EQ(largeGrid.cells[0][0][1].getState(), ALIVE);

}

TEST(GridTest, LifeSpanTest) {
	Grid<Cell> largeGrid(10, 10, 10, ruleset);
	largeGrid.cells[0][0][0].setState(ALIVE);
	largeGrid.cells[1][0][0].setState(ALIVE);
	largeGrid.cells[0][1][0].setState(ALIVE);
	largeGrid.cells[1][1][0].setState(ALIVE);

	largeGrid.updateGrid();

	EXPECT_TRUE(largeGrid.cells[0][0][0].getIsDying());
	EXPECT_EQ(largeGrid.cells[0][0][0].getLifespan(), 4);
	EXPECT_EQ(largeGrid.cells[0][0][1].getState(), ALIVE);
	EXPECT_EQ(largeGrid.cells[0][0][1].getLifespan(), 5);

}	