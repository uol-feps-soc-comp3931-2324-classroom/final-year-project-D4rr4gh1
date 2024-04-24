package gol;

public class Population {

    // Define our class members
    int width;
    int height;
    boolean[][] cells;

    // Our first constructor will be for the start of the application in which we need
    // to initialise our population with some random living and dead cells
    public Population(int width, int height) {

        // First perform checks for our parameters
        if(width <= 0 || height <= 0)
            throw new IllegalArgumentException("Width and height must be positive");


        // If the parameters are valid, we can set our class members and initialise our 2D array/grid
        this.width = width;
        this.height = height;
        this.cells = new boolean[width][height];

        // During the initialisation, we will a weighting of 0.2 for our randomness 
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                cells[i][j] = Math.random() < 0.2;
            }
        }
    }

    // This constructor is called for creating subsequent generations, 
    // we give it the previous generation and it will set itself up similarly, without
    // filling the grid
    public Population(Population previouPopulation){
        this.width = previouPopulation.width;
        this.height = previouPopulation.height;
        this.cells = new boolean[width][height];
    }

    // The following two functions will be used for getting and setting
    // the values of our individual cells.
    public void setCell(int x, int y, boolean value) {
        if(x < 0 || x >= width || y < 0 || y >= height)
            throw new IllegalArgumentException("Invalid cell coordinates");

        cells[x][y] = value;
    }

    public boolean getCell(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= height)
            throw new IllegalArgumentException("Invalid cell coordinates");

        return cells[x][y];
    }

    // This function looks at the 3x3 grid around our current cell and counts
    // the living neighbours, this value is then returned and used by our ruleset
    public int getNeighbours(int x, int y){
        int count = 0;
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(i == 0 && j == 0) continue;
                if(x + i < 0 || x + i >= width) continue;
                if(y + j < 0 || y + j >= height) continue;
                if(getCell(x + i, y + j)) count++;
            }
        }
        return count;
    }
    
}
