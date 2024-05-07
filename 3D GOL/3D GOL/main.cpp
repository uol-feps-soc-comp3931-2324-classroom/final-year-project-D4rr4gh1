#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "stb_image_write.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Camera.h"
#include "Cell.h"
#include "RPSCell.h"
#include "Cube.h"
#include "Shader.h"
#include "Grid.h"
#include "Global.h"
#include "Ruleset.h"


// Game Variables
int generalORrps = 1; // 1 for Chosen Ruleset, 2 for Rock-Paper-Scissors
int defaultLifeSpan = 5; // Lifespan of a cell
int initialCellChance = 10; // Initial chance of a cell being alive
std::vector<int> survivalNeighbours = { 4 }; // Defined number of neighbours for a cell to survive, input each number of desire neighbours into the vector
std::vector<int> birthNeighbours = { 4 }; // Defined number of neighbours for a cell to be born, input each number of desire neighbours into the vector

// RPS Variables
int RPSWinThreshold = 10; // Number of wins needed by winning counter part to turn the cell
int RPSRandomness = 5; // Randomness of the game, the higher the number, the more random the game


// Global Variables for easy access throught the program
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const int sizeX = 50, sizeY = 50, sizeZ = 50;
float deltaTime;
const Cell cell;
const RPSCell RPScell;
int renderStartPoint = sizeZ;
unsigned int VBO, VAO;
bool paused = false;


// Base initial ruleset
Ruleset ruleset(survivalNeighbours, birthNeighbours);

// Grids for the models, one for the chosen ruleset and one for the Rock-Paper-Scissors
Grid<Cell> grid(sizeX, sizeY, sizeZ, ruleset);
Grid<RPSCell> RPSgrid(sizeX, sizeY, sizeZ, ruleset);
unsigned int shaderProgram;

// Camera set up
Camera camera;

// Render function to render the models
void render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    

    // Set up the shader program
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // Set up the model, view and projection matrices, used for the camera and the model
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);


    // Set up the uniforms for the shader program
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    GLint colorLoc = glGetUniformLocation(shaderProgram, "objectColor"); 

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    // Draw the filled cubes, based on the model method selected
    if (generalORrps == 1) {

        // Loop through the grid and draw the filled cubes
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                for (int z = 0; z < sizeZ; z++) {

                    // Check if the cell is alive, if so, draw the cube
                    if (grid.cells[x][y][z].getState() == ALIVE) {

                        // Set the position of the cube and draw it
                        glm::vec3 pos(x - sizeX / 2, y - sizeY / 2, z - sizeZ / 2);
                        model = glm::translate(glm::mat4(1.0f), pos);
                        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                        glUniform3f(colorLoc, grid.cells[x][y][z].getColor().x, grid.cells[x][y][z].getColor().y, grid.cells[x][y][z].getColor().z);  // Color for filled cubes
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }
                }
            }
        }
    }

    // Perform the same as above, but for the Rock-Paper-Scissors model
    else {
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                for (int z = 0; z < renderStartPoint; z++) {
                    glm::vec3 pos(x - sizeX / 2, y - sizeY / 2, z - sizeZ / 2);
                    model = glm::translate(glm::mat4(1.0f), pos);
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glUniform3f(colorLoc, RPSgrid.cells[x][y][z].getColor().x, RPSgrid.cells[x][y][z].getColor().y, RPSgrid.cells[x][y][z].getColor().z);  // Color for filled cubes
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }
    }

    // Render wireframe borders for each cube
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            for (int z = 0; z < sizeZ; z++) {
                if (grid.cells[x][y][z].getState() == ALIVE) {
                    glm::vec3 pos(x - sizeX / 2, y - sizeY / 2, z - sizeZ / 2);
                    model = glm::translate(glm::mat4(1.0f), pos);
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glUniform3f(colorLoc, 0.0f, 0.0f, 0.0f);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
    glBindVertexArray(0);
}


// Define the behaviour for user inputs
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS)
            camera.moveForward = true;
        else if (action == GLFW_RELEASE)
            camera.moveForward = false;
    }

    else if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS)
            camera.moveBackward = true;
        else if (action == GLFW_RELEASE)
            camera.moveBackward = false;
    }

    else if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS)
            camera.moveLeft = true;
        else if (action == GLFW_RELEASE)
            camera.moveLeft = false;
    }

    else if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS)
            camera.moveRight = true;
        else if (action == GLFW_RELEASE)
            camera.moveRight = false;
    }

    else if (key == GLFW_KEY_LEFT_SHIFT)
    {
        if (action == GLFW_PRESS)
            camera.speedUp = true;
        else if (action == GLFW_RELEASE)
            camera.speedUp = false;
    }
    else if (key == GLFW_KEY_LEFT_CONTROL)
    {
        if (action == GLFW_PRESS)
            camera.slowDown = true;
        else if (action == GLFW_RELEASE)
            camera.slowDown = false;
    }

    // Allow the user to view a cross section of th grid
    else if (key == GLFW_KEY_C)
    {
        if(action == GLFW_PRESS)
            renderStartPoint = renderStartPoint == sizeZ ? sizeZ / 2 : sizeZ;
    }

    // Allow the user to pause the evoliution of the grid
    else if (key == GLFW_KEY_SPACE) {
        if (action == GLFW_PRESS)
            paused = paused == true ? false : true;

    }
}

// Define the behaviour for the mouse inputs, allowing the user to look around the grid
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = WIDTH / 2.0f;
    static float lastY = HEIGHT / 2.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, -yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((float)yoffset);
}

// Main function to run the program
int main() {

    // Set up the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Game of Life", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    // Use GLFW to assign user input behaviour to the specified functions
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, &key_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // Error handling for GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set up the OpenGL window
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);


    // Set up the shaders for the program
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    // Set up the grid, based on the specifiec mode, and the VAO for the cubes
    generalORrps == 1 ? grid.initializeGrid() : RPSgrid.initializeGrid();
    setupCubeVAO();

    // Setup timer to allow for the evolution of the grid
    deltaTime = 0.0f;
    float lastFrame = glfwGetTime();
    float timer = lastFrame;

    // Main while loop that runs until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        // Check for user inputs and update the camera and time
        glfwPollEvents();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.ProcessKeyboard(window, deltaTime);

        // Update the grid based at every time step
        if (currentFrame - timer >= 0.5f) {
            if (!paused)
                generalORrps == 1 ? grid.updateGrid() : RPSgrid.updateGrid();
            timer = currentFrame;
        }

        // Render the grid
        render();
    
        // Swap the buffers and clear the screen, readyt for the next frame
        glfwSwapBuffers(window);
    }

    // Delete the VAO, VBO and shader program, and terminate the GLFW window
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
