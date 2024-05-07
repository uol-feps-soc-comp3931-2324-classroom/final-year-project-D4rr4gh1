package fallingsandsim;

// This enum represents the possible states of a cell
enum State {SAND, WATER, STONE, EMPTY};

// This class represents a cell in the simulation
public class Cell {
    State state;

    // Constructor
    public Cell(State state)
    {
        this.state = state;
    }
}
