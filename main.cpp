#include <GL/gl.h> // include the header file for OpenGL functions
#include <GL/glut.h> // include the header file for GLUT library
#include "game.h" // include the custom header file for game logic
#include <stdlib.h> // include the header file for standard library functions

#define COLUMNS 40 // define a macro for the number of columns in the game grid
#define ROWS 40 // define a macro for the number of rows in the game grid
#define FPS 10 // define a macro for the frames per second of the animation

extern short sDirection ; // declare an external variable for the snake direction
int gameOver=0; // declare a global variable for the game over flag

int score = 0; // declare a global variable for the player's score

void timer_callback(int); // declare a function prototype for the timer callback
void display_callback(); // declare a function prototype for the display callback
void reshape_callback(int,int); // declare a function prototype for the reshape callback
void keyboard_callback(int , int , int ); // declare a function prototype for the keyboard callback

void init() // define a function for initializing the game
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // set the background color to black
	initGrid(COLUMNS, ROWS);//initialize the grid coordinates

}

int main(int argc,char **argv){ // define the main function

        glutInit(&argc,argv); // initialize the GLUT library
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // set the display mode to use RGB color model and double buffering
        glutInitWindowSize(500,500); // set the initial window size
        glutCreateWindow("SNAKE-Game"); // create a window with the title "SNAKE-Game"
        glutDisplayFunc(display_callback); // register the display callback function
        glutReshapeFunc(reshape_callback); // register the reshape callback function
        glutTimerFunc(0,timer_callback, 0); // register the timer callback function
        glutSpecialFunc(keyboard_callback) ; // register the keyboard callback function
        init(); // call the init function
        glutMainLoop(); // enter the main loop of GLUT
        return 0; // return 0 to indicate a normal exit
}
int index = 0 ; // declare a local variable for the index of the snake nodes
void display_callback(){ // define the display callback function
	glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer of the window
	drawGrid(); //display the grid every time the screen shown
    drawSnake() ; // display the snake on the window
    drawFood(); // display the food on the window
    glutSwapBuffers(); // swap the front and back buffers of the window
    if(gameOver) // check if the game is over
    {
        char _score[10]; // declare a character array for the score
        itoa(score,_score,10); // convert the score from integer to string
        char text[50]= "your score: "; // declare a character array for the message
        strcat(text,_score); // concatenate the message and the score
        MessageBox(NULL,text,"GAME OVER",0); // create a message box with the message and the title
        exit(0); // terminate the program
    }
}

void reshape_callback(int w, int h){ // define the reshape callback function
	glViewport(0,0, (GLsizei)w, (GLsizei)h); // set the viewport to the window size
	glMatrixMode(GL_PROJECTION); // set the matrix mode to projection
	glLoadIdentity(); // load the identity matrix
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);//set the orthogonal projection for the game area
	glMatrixMode(GL_MODELVIEW); // set the matrix mode to modelview
}

void timer_callback(int t) // define the timer callback function
{
    glutPostRedisplay(); // post a redisplay event
    glutTimerFunc(1000/FPS,timer_callback,0); // register the timer callback function again
}

void keyboard_callback(int key , int k1 , int k2){ // define the keyboard callback function
    switch(key) // switch on the key code
    {
        case GLUT_KEY_UP: // if the key is up arrow
            if(sDirection != DOWN) // if the snake is not moving down
                sDirection = UP ; // set the snake direction to up
            break ; // break the switch
        case GLUT_KEY_DOWN: // if the key is down arrow
            if(sDirection != UP) // if the snake is not moving up
                sDirection = DOWN ; // set the snake direction to down
            break ; // break the switch
        case GLUT_KEY_RIGHT: // if the key is right arrow
            if(sDirection != LEFT) // if the snake is not moving left
                sDirection = RIGHT ; // set the snake direction to right
            break ; // break the switch
        case GLUT_KEY_LEFT: // if the key is left arrow
            if(sDirection != RIGHT) // if the snake is not moving right
                sDirection = LEFT ; // set the snake direction to left
            break ; // break the switch
    }

}
