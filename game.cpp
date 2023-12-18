#include <GL/gl.h> // include the header file for OpenGL functions
#include <GL/glut.h> // include the header file for GLUT library
#include <ctime> // include the header file for time functions
#include "game.h" // include the custom header file for game logic

// define some constants or macros for the magic numbers
#define MAX_LENGTH 60 // the maximum length of the snake
#define INIT_LENGTH 5 // the initial length of the snake
#define INIT_X 20 // the initial x position of the snake
#define INIT_Y 20 // the initial y position of the snake
#define EDGE_WIDTH 3.0 // the width of the edge line
#define RED 1.0,0.0,0.0 // the RGB color of the edge
#define WHITE 1.0,1.0,1.0 // the RGB color of the grid
#define BLACK 0.0,0.0,0.0 // the RGB color of the background
#define OFFSET 2 // the offset from the edge of the grid
#define UNIT 1 // the unit size of the grid

extern int score; // declare an external variable for the player's score

int gridx, gridy; // declare global variables for the grid size
int snake_length = INIT_LENGTH; // declare and initialize a global variable for the snake length
int food =1; // declare and initialize a global variable for the food flag
int foodX,foodY; // declare global variables for the food position
short sDirection  = RIGHT ; // declare and initialize a global variable for the snake direction
extern int gameOver; // declare an external variable for the game over flag

int posX[MAX_LENGTH]={INIT_X,INIT_X,INIT_X,INIT_X,INIT_X} , posY[MAX_LENGTH]={INIT_Y,INIT_Y-1,INIT_Y-2,INIT_Y-3,INIT_Y-4}; // declare and initialize global arrays for the snake positions

void initGrid(int x, int y)//initialize the grid coordinates
{
    gridx = x;
    gridy = y;
}

void drawGrid() // draw the grid on the window
{
    for(int x=0;x<gridx;x++) // loop through the x coordinates
    {
        for(int y=0;y<gridy;y++) // loop through the y coordinates
        {
            unit(x,y);//draw one unit of the grid
        }
    }
}

void unit(int x, int y) // draw one unit of the grid
{
    if(x==0 || y==0 || x==gridx-1 || y==gridy-1) // check if the unit is on the edge
    {
        glLineWidth(EDGE_WIDTH); //set the thickness of the edge line
        glColor3f(RED); // set the color of the edge to be red
    }
    else // otherwise
    {
        glLineWidth(1.0); //set the thickness of the line
        glColor3f(WHITE);//set the color of the line to be white
    }

    glBegin(GL_POLYGON);  //line_loop mean connected ends
        glVertex2f(x,y); //first point of the square
        glVertex2f(x+UNIT,y); //second point
        glVertex2f(x+UNIT,y+UNIT);//third point
        glVertex2f(x,y+UNIT); //forth point
    glEnd();
}
void drawFood() // draw the food on the window
{

    if(food) // check if the food flag is true
        random(foodX,foodY); // generate a random position for the food
    food=0; // set the food flag to false
    glColor3f(WHITE); // set the color of the food to be white
    glRectf(foodX,foodY,foodX+UNIT,foodY+UNIT); // draw a rectangle for the food

}

void drawSnake() // draw the snake on the window
{
    for(int i=snake_length-1;i>0;i--) // loop through the snake nodes from the tail to the head
    {
        posX[i]=posX[i-1]; // update the x position of the node to the previous node
        posY[i]=posY[i-1]; // update the y position of the node to the previous node
    }
    switch(sDirection) // switch on the snake direction
    {
        case UP: // if the direction is up
            posY[0]++ ; // increment the y position of the head
            break; // break the switch
        case DOWN: // if the direction is down
            posY[0]--; // decrement the y position of the head
            break; // break the switch
        case RIGHT: // if the direction is right
            posX[0]++; // increment the x position of the head
            break; // break the switch
        case LEFT: // if the direction is left
            posX[0]--; // decrement the x position of the head
            break; // break the switch
    }
    for(int i=0;i<snake_length;i++) // loop through the snake nodes
    {
        if(i == 0) // if the node is the head
            glColor3f(0.0,1.0,0.0); // set the color to be green
        else // otherwise
            glColor3f(0.0,0.0,1.0); // set the color to be blue
        glRectd(posX[i] , posY[i] , posX[i]+UNIT , posY[i]+UNIT); // draw a rectangle for the node
    }
    if(posX[0]==0 || posX[0] == gridx-1 || posY[0] ==0 || posY[0] == gridy-1) // check if the snake hits the edge
        gameOver=1; // set the game over flag to true
    if (posX[0]==foodX && posY[0]==foodY) // check if the snake eats the food
    {
        score++; // increment the score
        snake_length++; // increment the snake length
        if(snake_length>MAX_LENGTH) // check if the snake length exceeds the maximum length
            snake_length = MAX_LENGTH; // set the snake length to the maximum length
        food=1; // set the food flag to true
    }


}

void random(int &x,int&y) // generate a random position for the food
{
    int _maxX = gridx-OFFSET; // calculate the maximum x coordinate
    int _maxY = gridy-OFFSET; // calculate the maximum y coordinate
    int _min=OFFSET; // calculate the minimum coordinate
    srand(time(NULL)); // seed the random number generator with the current time
    x= _min+rand()% (_maxX-_min); // generate a random x coordinate within the range
    y= _min+rand()% (_maxY-_min); // generate a random y coordinate within the range

}
