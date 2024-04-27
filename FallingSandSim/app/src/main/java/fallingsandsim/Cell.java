package fallingsandsim;

enum State {SAND, WATER, STONE, EMPTY};

public class Cell {
    State state;

    public Cell(State state)
    {
        this.state = state;
    }

}
