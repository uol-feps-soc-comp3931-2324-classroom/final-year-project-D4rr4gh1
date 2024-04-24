package gol;


public class ConwayRules {

    /*
     * Conways rules:
     * 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
     * 2. Any live cell with two or three live neighbours lives on to the next generation.
     * 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
     * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     * 
     * Simpler rules:
     * 1. Any live cell with fewer than two or more than three live neighbours dies.
     * 2. Any live cell with two or three live neighbours lives on to the next generation.
     * 3. Any dead cell with exactly three live neighbours dies.
     */

     public static Population evolve(Population curPopulation){
        // Create a new Population as altering the current one would throw off our calcualtions
        Population nextPop = new Population(curPopulation);

        // Work through the new grid, applying the Conway rules to each of our cells.
        for (int i = 0; i < nextPop.width; i++) {
            for (int j = 0; j < nextPop.height; j++) {
                boolean curCell = curPopulation.getCell(i, j);
                int neighbours = curPopulation.getNeighbours(i, j);
                nextPop.setCell(i,j, applyRules(curCell, neighbours));
            }
            
        }

        return nextPop;
     }

     public static boolean applyRules(boolean cell, int neighbours){
        // Rule 1 & 2
        if(cell){
            // if number of neighbours incorrect, cell dies
           if(neighbours < 2 || neighbours > 3){
            return false;
           }

           // if code has not already returned, then number of neighbours must 
           // be correct, so cell lives
           return true;
        }

        //Rule 3
        if(!cell && neighbours == 3){
            return true;
        }

        // cell is dead and number of neighbours is incorrect
        return false;
     }
}
