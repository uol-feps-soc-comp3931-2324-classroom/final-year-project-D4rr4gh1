package fallingsandsim;

enum State {SAND, WATER, STONE, EMPTY};
enum Direction {LEFT, RIGHT, NONE};

public class Cell {
    State state;
    float momentum;
    Direction direction;


    public Cell(State state)
    {
        this.state = state;
        this.momentum = 1;
        this.direction = Direction.NONE;
    }

    public void updateMomentum(float updatedValue)
    {
        this.momentum = updatedValue;
    }

    public void updateDirection(Direction direction)
    {
        this.direction = direction;
    }

}
