package fallingsandsim;

enum Direction {
    LEFT,
    RIGHT
}

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
                        boolean moved = false;
                        // Down
                        if(j + 1 < height && cells[i][j + 1].state == State.EMPTY){
                            nextPop.setCell(i, j + 1, currentCell); // Reuse currentCell instead of new Cell(State.SAND)
                            moved = true;
                        }
                        // Down-left or down-right with randomness
                        else if(j + 1 < height) {
                            boolean canMoveLeft = i - 1 >= 0 && cells[i - 1][j + 1].state == State.EMPTY;
                            boolean canMoveRight = i + 1 < width && cells[i + 1][j + 1].state == State.EMPTY;
                            if (canMoveLeft && canMoveRight) {
                                nextPop.setCell((Math.random() < 0.5 ? i - 1 : i + 1), j + 1, currentCell);
                                moved = true;
                            } else if (canMoveLeft) {
                                nextPop.setCell(i - 1, j + 1, currentCell);
                                moved = true;
                            } else if (canMoveRight) {
                                nextPop.setCell(i + 1, j + 1, currentCell);
                                moved = true;
                            }
                        }
                        // Stay in place if no movement is possible
                        if (!moved) {
                            nextPop.setCell(i, j, currentCell);
                        }
                        break;
                    case WATER:
                        if(j + 1 >= height) break;
                        moved = false;
                        // Try to move down
                        if(j + 1 < height && cells[i][j + 1].state == State.EMPTY){
                            nextPop.setCell(i, j + 1, currentCell);
                            moved = true;
                        }
                        // Spread out horizontally if the cell below is water
                        else if(j + 1 < height) {
                            boolean canMoveLeft = i - 1 >= 0 && cells[i - 1][j].state == State.EMPTY;
                            boolean canMoveRight = i + 1 < width && cells[i + 1][j].state == State.EMPTY;
                            if (canMoveLeft && canMoveRight) {
                                nextPop.setCell((Math.random() < 0.5 ? i - 1 : i + 1), j, currentCell);
                                moved = true;
                            } else if (canMoveLeft) {
                                nextPop.setCell(i - 1, j, currentCell);
                                moved = true;
                            } else if (canMoveRight) {
                                nextPop.setCell(i + 1, j, currentCell);
                                moved = true;
                            }
                        }

                        if (!moved) {
                            nextPop.setCell(i, j, currentCell);
                        }
                        break;
                }
    


            }
        }

        return nextPop;
    }


    private int countSpace(int x, int y, Direction direction) {
        int space = 0;
        int i = x;
        while (i >= 0 && i < width && cells[i][y].state == State.EMPTY) {
            space++;
            i += direction == Direction.LEFT ? -1 : 1;
        }
        return space;
    }

}
