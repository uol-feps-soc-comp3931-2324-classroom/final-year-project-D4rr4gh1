package multistate;

public class Cell {
    int lifespan, state;

    public Cell(int state)
    {
        this.state = state;
    }

    public Cell(int state, int lifespan)
    {
        this.state = state;
        this.lifespan = lifespan;
    }
}
