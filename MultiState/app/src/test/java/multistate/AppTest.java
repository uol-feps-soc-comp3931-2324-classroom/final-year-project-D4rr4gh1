package multistate;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class AppTest {


    // Test that the cell constructor works
    @Test void cellConstructorWorks() {
        Cell testCell = new Cell(1, 2);
        assertEquals(testCell.state, 1);
        assertEquals(testCell.lifespan, 2);
    }

    // Test that RPS rules correctly identify the number of losses
    @Test void rpsCorrectlyIdentifiesNumberOfLosses() {
        Cell rock = new Cell(0);
        Cell paper = new Cell(1);
        Cell scissors = new Cell(2);

        Cell[][] init = {{rock, rock, paper},
                         {rock, scissors, rock},
                         {scissors, paper, rock}};
        
        Population testPopulation = new Population(3,3, 0);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testPopulation.setCell(i, j, init[i][j]);
            }
        }
        int[] results = testPopulation.playRPS(2, 1, 1);
        
        // there are 5 rocks in the neighbourhood, all of which
        // beat scissors, so the result should be 5
        assertEquals(results[1], 5);
    }



    // Test that RPS rules correctly identify the number of losses
    // and the new grid is being correctly generated
    @Test void playRPSWorks() {
        Cell rock = new Cell(0);
        Cell paper = new Cell(1);
        Cell scissors = new Cell(2);

        Cell[][] init = {{rock, rock, paper},
                         {rock, scissors, rock},
                         {scissors, paper, rock}};
        

        Cell[][] result = {{rock, rock, paper},
                            {rock, rock, rock},
                            {scissors, paper, rock}};
        
        Population testPopulation = new Population(3,3, 0);
        RPSRules rules = new RPSRules(3, 0);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testPopulation.setCell(i, j, init[i][j]);
            }
        }

        testPopulation = rules.evolve(testPopulation);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                assertEquals(testPopulation.getCell(i, j).state, result[i][j].state);
            }

            System.out.println();
        }
    }
}
