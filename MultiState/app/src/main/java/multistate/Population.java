package multistate;

public class Population {

    // Define our class members
    int width;
    int height;
    Cell[][] cells;

    // Our first constructor will be for the start of the application in which we need
    // to initialise our population with some random living and dead cells
    public Population(int width, int height, int init) {

        // First perform checks for our parameters
        if(width <= 0 || height <= 0)
            throw new IllegalArgumentException("Width and height must be positive");


        // If the parameters are valid, we can set our class members and initialise our 2D array/grid
        this.width = width;
        this.height = height;
        this.cells = new Cell[width][height];

        initialisePopulation(init);

    }

    // This constructor is called for creating subsequent generations, 
    // we give it the previous generation and it will set itself up similarly, without
    // filling the grid
    public Population(Population previouPopulation){
        this.width = previouPopulation.width;
        this.height = previouPopulation.height;
        this.cells = new Cell[width][height];
    }

    private void initialisePopulation(int setting){

        // This Grid is completely randomised, for RPSLSp
        if(setting == 0){
            for(int i = 0; i < width; i++) {
                for(int j = 0; j < height; j++) {         
                    int state = (int) (Math.random() * 100) % 5;
                    cells[i][j] = new Cell(state);
                }
            }
        }


        // For RPS, this is split into thirds
        if(setting == 1){
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    if (j < height * i / width) {
                        cells[i][j] = new Cell(0);
                    } else if (j > height - (height * i / width)) {
                        // Middle triangle
                        cells[i][j] = new Cell(1);
                    } else {
                        // Left triangle
                        cells[i][j] = new Cell(2);
                    }
                }
            }
        }

        // This Grid is completely randomised, for RPS
        if(setting == 2){
            for(int i = 0; i < width; i++) {
                for(int j = 0; j < height; j++) {
                    int state = (int) (Math.random() * 100) % 3;
                    cells[i][j] = new Cell(state);
                }
            }
        }
    }

    // The following two functions will be used for getting and setting
    // the values of our individual cells.
    public void setCell(int x, int y, Cell newCell) {
        if(x < 0 || x >= width || y < 0 || y >= height)
            throw new IllegalArgumentException("Invalid cell coordinates");

        cells[x][y] = newCell;
    }

    public Cell getCell(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= height)
            throw new IllegalArgumentException("Invalid cell coordinates");

        return cells[x][y];
    }

    // This function looks at the 3x3 grid around our current cell and counts
    // the living neighbours, this value is then returned and used by our ruleset
    public int[] playRPS(int curCellState, int x, int y){
        int[] WLCount = {1, 0};
        int winnerState1 = 0;
        int winnerState2 = 0;
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(i == 0 && j == 0) continue;
                if(x + i < 0 || x + i >= width || y + j < 0 || y + j >= height) continue;
                
                int col = (x + i);
                int row = (y + j);

                int opponentState = cells[col][row].state;
                
                // Rules for RPSLSp
                switch(curCellState)
                {
                    case 0:
                        if(opponentState == 1){
                            winnerState1++;
                            WLCount[1]++;
                        }
                        if(opponentState == 4){
                            winnerState2++;
                            WLCount[1]++;
                        }
                        break;
                    case 1:
                        if(opponentState == 2){
                            winnerState1++;
                            WLCount[1]++;
                        }
                        if(opponentState == 3){
                            winnerState2++;
                            WLCount[1]++;
                        }
                        break;
                    case 2:
                        if(opponentState == 0){
                            winnerState1++;
                            WLCount[1]++;
                        }
                        if(opponentState == 4){
                            winnerState2++;
                            WLCount[1]++;
                        }
                        break;
                    case 3:
                        if(opponentState == 0){
                            winnerState1++;
                            WLCount[1]++;
                        }
                        if(opponentState == 2){
                            winnerState2++;
                            WLCount[1]++;
                        }
                        break;
                    case 4:
                        if(opponentState == 1){
                            winnerState1++;
                            WLCount[1]++;
                        }
                        if(opponentState == 3){
                            winnerState2++;
                            WLCount[1]++;
                        }
                        break;
                }
            }
        }
        if(winnerState1 > winnerState2)
            WLCount[0] = 0;
        return WLCount;
    }
    
}
