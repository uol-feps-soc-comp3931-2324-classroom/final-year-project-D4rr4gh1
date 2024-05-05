package multistate;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class AppTest {
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
                System.out.println("Test state is: " + testPopulation.getCell(i, j).state + " Should be: " + result[i][j].state);
                assertEquals(testPopulation.getCell(i, j).state, result[i][j].state);
            }

            System.out.println();
        }
    }
}
