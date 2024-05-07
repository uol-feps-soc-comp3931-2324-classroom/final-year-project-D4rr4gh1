package multistate;

import java.util.Timer;
import java.util.TimerTask;
import javax.swing.*;
import java.awt.*;

public class App {


    // Create an iniitial population
    private static Population p;

    public static void main(String[] args) {


        // Check for the correct number of arguments
        if(args.length != 3)
            throw new IllegalArgumentException("Not enough arguments. Correct Usage is: ./gradlew run --args='<Threshold> <Randomness Factor> <Initial Grid>'");
        
        // Create our ruleset and population, based on the arguments given
        // catching any errors that may occur
        RPSRules rules;
        try{
            rules = new RPSRules(Integer.valueOf(args[0]), Integer.valueOf(args[1]));
            p = new Population(400, 300, Integer.valueOf(args[2]));
        }
        catch(NumberFormatException e){
            throw new NumberFormatException("Illegal values");
        }

        // Create our GUI for the application
        JFrame frame = new JFrame("Rock Paper Scissors");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(p.width, p.height);
        gamePanel panel = new gamePanel();
        frame.add(panel, BorderLayout.CENTER);
        frame.pack();
        frame.setLayout(null);
        frame.setVisible(true);


        // Set up our timer for repeatedly running the evolution function
        Timer timer = new Timer();

        // The function that will be called continually, it gets the new,
        // evolved population from the ruleset and sets it to the classes
        // population member. It then redraws the UI to match the new population.
        TimerTask doThing = new TimerTask() {
            @Override
            public void run() {
                p = rules.evolve(p);
                panel.repaint();
            }  
        }; 

        timer.scheduleAtFixedRate(doThing, 0, 50);
    }


    // This class is implemented to create the panel to be drawn on, this 
    // requires extending the JPanel class so that the paint method can 
    // be adjusted to implement our new logic as to what should be drawn.
    static class gamePanel extends JPanel {
        
        public gamePanel(){
            setPreferredSize(new Dimension(p.width, p.height));
            setBackground(Color.BLACK);
        }
        

        // This function is called whenever the panel needs to be redrawn
        @Override
        public void paint(Graphics g){
            super.paint(g);
            int color;

            for (int x = 0; x < p.width; x++) {
                for (int y = 0; y < p.height; y++) {
                    color = p.getCell(x, y).state;

                    switch(color){
                        case 0:
                            g.setColor(Color.RED);
                            g.drawLine(x, y, x, y);
                            break;
                        case 1:
                            g.setColor(Color.GREEN);
                            g.drawLine(x, y, x, y);
                            break;
                        case 2:
                            g.setColor(Color.BLUE);
                            g.drawLine(x, y, x, y);
                            break;

                        // RPSLSp Extra Colours
                        case 3:
                            g.setColor(Color.ORANGE);
                            g.drawLine(x, y, x, y);
                            break;
                        case 4:
                            g.setColor(Color.BLACK);
                            g.drawLine(x, y, x, y);
                            break;
                    }
                }
            }
        }
    }
}
