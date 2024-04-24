#include "pch.h"
#include "../3D GOL/Cell.h"
#include "../3D GOL/RPSCell.h"
#include "../3D GOL/Grid.h"
#include "../3D GOL/Cell.cpp"
#include "../3D GOL/RPSCell.cpp"
#include "../3D GOL/Grid.cpp"
#include <gtest/gtest.h>


Cell cell(ALIVE, 5, false);
Cell cell2(DEAD, 0, false);

RPSCell rockCell(ROCK);
RPSCell paperCell(PAPER);
RPSCell scissorsCell(SCISSORS);


Grid<Cell> grid(3, 3, 3);
Grid<RPSCell> rpsGrid(3, 3, 3);

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

TEST(GridTest, updateGrid) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				grid.cells[i][j][k].copy(cell2);
			}
		}
	}
	grid.updateGrid();

	std::cout << "Updated grid: \n";
	grid.cells[1][1][1].copy(cell);
	grid.cells[0][2][0].copy(cell);
	grid.cells[1][2][0].copy(cell);
	grid.cells[1][2][1].copy(cell);
	grid.cells[2][2][0].copy(cell);

	grid.updateGrid();

	EXPECT_EQ(grid.cells[1][1][1].getState(), ALIVE);
	EXPECT_FALSE(grid.cells[1][1][1].getIsDying());
	EXPECT_TRUE(grid.cells[0][2][0].getIsDying());
	EXPECT_TRUE(grid.cells[1][2][0].getIsDying());
	EXPECT_TRUE(grid.cells[1][2][1].getIsDying());
	EXPECT_TRUE(grid.cells[2][2][0].getIsDying());

}

TEST(GridTest, updateGrid2) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				grid.cells[i][j][k].copy(cell2);
			}
		}
	}
	grid.updateGrid();

	std::cout << "Updated grid: \n";
	grid.cells[1][1][1].copy(cell);
	grid.cells[0][2][0].copy(cell);
	grid.cells[1][2][0].copy(cell);
	grid.cells[1][2][1].copy(cell);
	grid.cells[2][2][0].copy(cell);

	grid.updateGrid();

	EXPECT_EQ(grid.cells[1][1][1].getState(), ALIVE);
	EXPECT_FALSE(grid.cells[1][1][1].getIsDying());
	EXPECT_TRUE(grid.cells[0][2][0].getIsDying());
	EXPECT_TRUE(grid.cells[1][2][0].getIsDying());
	EXPECT_TRUE(grid.cells[1][2][1].getIsDying());
	EXPECT_TRUE(grid.cells[2][2][0].getIsDying());

}	
