package fallingsandsim;

public class Population {

    // Define our class members
    int width;
    int height;
    Cell[][] cells;

    // Our first constructor will be for the start of the application in which we need
    // to initialise our population with some random living and dead cells
    public Population(int width, int height) {

        // First perform checks for our parameters
        if(width <= 0 || height <= 0)
            throw new IllegalArgumentException("Width and height must be positive");


        // If the parameters are valid, we can set our class members and initialise our 2D array/grid
        this.width = width;
        this.height = height;
        this.cells = new Cell[width][height];

        // Fill a horizontal middle section with Stone cells
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if(j > height / 2 + 100 && j < height / 2 + 120 && i > width / 2 - 200 && i < width / 2 + 200){
                    cells[i][j] = new Cell(State.STONE);
                } else {
                    cells[i][j] = new Cell(State.EMPTY);
                }
            }
        }


    }

    // This constructor is called for creating subsequent generations, 
    // we give it the previous generation and it will set itself up similarly, without
    // filling the grid
    public Population(Population previouPopulation){
        this.width = previouPopulation.width;
        this.height = previouPopulation.height;
        this.cells = new Cell[width][height];
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


    public Population evolve() {
        Population nextPop = new Population(width, height);
        int[] newCoords;

        // Work through the new grid
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Cell currentCell = cells[i][j];
                switch(currentCell.state){
                    case EMPTY:
                        break;
                    case STONE:
                        nextPop.setCell(i, j, currentCell);
                        break;
                    case SAND:
                        if(j + 1 >= height) break;
                        newCoords = updateSand(i, j);
                        nextPop.setCell(newCoords[0], newCoords[1], currentCell);
                        break;
                    case WATER:
                        if(j + 1 >= height) break;
                        newCoords = disperseWater(i, j, currentCell);
                        nextPop.setCell(newCoords[0], newCoords[1], currentCell);
                        break;
                }
    


            }
        }

        return nextPop;
    }

    // This function will be used to update the position of a sand particle
    private int[] updateSand(int x, int y){

        // If the cell below is empty, move the sand down
        if (cells[x][y + 1].state == State.EMPTY){
            return new int[]{x, y + 1};
        }
        

        // If the cell below is not empty, check if we can move left or right
        boolean canMoveLeft = (x - 1 >= 0) && (cells[x - 1][y + 1].state == State.EMPTY);
        boolean canMoveRight = (x + 1 < width) && (cells[x + 1][y + 1].state == State.EMPTY);

        // If we can move left and right, choose randomly
        // else move in the direction we can
        if (canMoveLeft && canMoveRight){
            return new int[]{(Math.random() < 0.5 ? x - 1 : x + 1), y + 1};
        }

        if (canMoveLeft){
            return new int[]{x - 1, y + 1};
        }

        if (canMoveRight){
            return new int[]{x + 1, y + 1};
        }

        // Return the new coordinates of the cell
        return new int[]{x, y};
    }

    // This function will be used to disperse water
    private int[] disperseWater(int x, int y, Cell currentCell){

        // If the cell below is empty, move the water down
        if (cells[x][y + 1].state == State.EMPTY){
            return new int[]{x, y + 1};
        }

        // If the cell below is not empty, check if we can move left or right
        boolean canMoveLeft = (x - 1 >= 0) && (cells[x - 1][y].state == State.EMPTY);
        boolean canMoveRight = (x + 1 < width) && (cells[x + 1][y].state == State.EMPTY);

        // If we can move left and right, move left or right
        if (canMoveLeft || canMoveRight){
            return new int[]{(canMoveLeft ? x - 1 : (canMoveRight ? x + 1 : x)), y};
        }

        // Return the new coordinates of the cell
        return new int[]{x, y};

    }   
 

}
