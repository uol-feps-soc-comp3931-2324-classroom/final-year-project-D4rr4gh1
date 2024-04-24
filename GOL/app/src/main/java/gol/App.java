package gol;

import java.util.Timer;
import java.util.TimerTask;
import javax.swing.*;
import java.awt.*;

public class App {

    // Create and populate the initial generation
    private static Population p = new Population(1280, 720);


    public static void main(String[] args) {

        // Create our GUI for the application
        JFrame frame = new JFrame("Game of Life");
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
        TimerTask runEvolution = new TimerTask() {
            @Override
            public void run() {
                p = ConwayRules.evolve(p);
                panel.repaint();
            }  
        }; 

        timer.scheduleAtFixedRate(runEvolution, 0, 100);
    }


    // This class is implemented to create the panel to be drawn on, this 
    // requires extending the JPanel class so that the paint method can 
    // be adjusted to implement our new logic as to what should be drawn.
    static class gamePanel extends JPanel {
        
        public gamePanel(){
            setPreferredSize(new Dimension(p.width, p.height));
            setBackground(Color.BLACK);
        }
    
        @Override
        public void paint(Graphics g){
            super.paint(g);
            g.setColor(Color.WHITE);

            for (int x = 0; x < p.width; x++) {
                for (int y = 0; y < p.height; y++) {
                    if(p.getCell(x, y)){
                        g.drawLine(x, y, x, y);
                    }
                }
            }
        }
    }
}




