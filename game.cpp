#include <GL/gl.h>
#include <GL/glut.h>
#include <ctime>
#include "game.h"

extern int score;

int gridx, gridy;
int snake_length = 5;
int food =1;
int foodX,foodY;
short sDirection  = RIGHT ;
extern int gameOver;

int posX[60]={20,20,20,20,20} , posY[60]={20,19,18,17,16};

void initGrid(int x, int y)//initialize the grid coordinates
{
    gridx = x;
    gridy = y;
}

void drawGrid()
{
    for(int x=0;x<gridx;x++)
    {
        for(int y=0;y<gridy;y++)
        {
            unit(x,y);//draw the hole grid
        }
    }
}

void unit(int x, int y) //one closed square will formed
{
    if(x==0 || y==0 || x==gridx-1 || y==gridy-1)
    {
        glLineWidth(3.0); //set the thickness of the edge line
        glColor3f(1.0,0.0,0.0); // set the color of the edge to be red
    }
    else
    {
        glLineWidth(1.0); //set the thickness of the line
        glColor3f(1.0,1.0,1.0);//set the color of the line to be white
    }

    glBegin(GL_POLYGON);  //line_loop mean connected ends
        glVertex2f(x,y); //first point of the square
        glVertex2f(x+1,y); //second point
        glVertex2f(x+1,y+1);//third point
        glVertex2f(x,y+1); //forth point
    glEnd();
}
void drawFood()
{

    if(food)
        random(foodX,foodY);
    food=0;
    glRectf(foodX,foodY,foodX+1,foodY+1);

}

void drawSnake()
{
    for(int i=snake_length-1;i>0;i--)
        {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    if(sDirection == UP)
        posY[0]++ ;
    else if(sDirection == DOWN)
        posY[0]--;
    else if(sDirection == RIGHT)
        posX[0]++;
    else if(sDirection == LEFT)
        posX[0]--;
    for(int i=0;i<snake_length;i++)
        {
        if(i == 0)
            glColor3f(0.0,1.0,0.0);
        else
            glColor3f(0.0,0.0,1.0);
            glRectd(posX[i] , posY[i] , posX[i]+1 , posY[i]+1);
    }
    if(posX[0]==0 || posX[0] == gridx-1 || posY[0] ==0 || posY[0] == gridy-1)
        gameOver=1;
        if (posX[0]==foodX && posY[0]==foodY)
        {
           score++;
           snake_length++;
           if(snake_length>MAX)
             snake_length = MAX;
           food=1;
        }


}

void random(int &x,int&y)
{
    int _maxX = gridx-2;
    int _maxY = gridy-2;
    int _min=1;
    srand(time(NULL));
    x= _min+rand()% (_maxX-_min);
    y= _min+rand()% (_maxY-_min);

}



