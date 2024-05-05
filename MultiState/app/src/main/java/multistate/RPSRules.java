package multistate;

public class RPSRules {

    private int threshold, randomFactor;

    public RPSRules(int threshold, int randomFactor)
    {
        this.threshold = threshold;
        this.randomFactor = randomFactor;
    }
    
    public Population evolve(Population currentPop)
    {
        Population nextPop = new Population(currentPop);

        // Work through the new grid, applying the Conway rules to each of our cells.
        for (int i = 0; i < nextPop.width; i++) {
            for (int j = 0; j < nextPop.height; j++) {
                Cell curCell = currentPop.getCell(i, j);
                int[] neighbours = currentPop.playRPS(curCell.state, i, j);
                nextPop.setCell(i,j, applyRules(curCell, neighbours));
            }
            
        }

        return nextPop;
    }

    private Cell applyRules(Cell cell, int[] RPSScore)
    {   
        int randomness = (int) (Math.random() * randomFactor);
        int cellState = cell.state;

        //RPS Cell updating
        // if(RPSScore[1] > threshold + randomness){
        //     cell.state = (cell.state + 1) % 3;
        // }
        

        // RPSLSp Cell Updating
        if(RPSScore[1] > threshold + randomness){
            switch(cellState)
            {
                case 0:
                    if(RPSScore[0] == 0)
                        cell.state = 1;
                    else
                        cell.state = 4;
                    break;
                case 1:
                    if(RPSScore[0] == 0)
                        cell.state = 2;
                    else
                        cell.state = 3;
                    break;
                case 2:
                    if(RPSScore[0] == 0)
                        cell.state = 0;
                    else
                        cell.state = 4;
                    break;
                case 3:
                    if(RPSScore[0] == 0)
                        cell.state = 0;
                    else
                        cell.state = 2;
                    break;
                case 4:
                    if(RPSScore[0] == 0)
                        cell.state = 1;
                    else
                        cell.state = 3;
                    break;
            }    
        }

        return cell;
    }
}
