#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;
// game over variable
bool gameOver;
// varible for box
const int width = 60;
const int height = 20;
//variable for head position & fruit position
int x, y, fruitX, fruitY, score;
// This is the tail.
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, Up, DOWN};
eDirection dir; 
eDirection lastDir = STOP;


void Setup()
{
    gameOver = false;
    // snake wont move until we start moving it:
    dir = STOP;
    // set position of the head (will be centered)
    x = width / 2;
    y = height / 2;
    // fruit position on the map
    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;

    nTail = 0;
}

void Draw()
{
    // clear the screen:
    system("cls");
    for (int i = 0; i < width +2; i++)
        cout << "#";

    cout << endl;

    for (int i = 0; i < height; i++)
    {
        // prints the first row only
        for (int j = 0; j < width; j++)
        {
            // Walls
            if (j == 0 )
                cout << "#";
            // head of snake
            if (i == y && j == x)
                cout << "O";
            // fruit
            else if (i == fruitY && j == fruitX)
                cout << "F";
            // tail of snake
            else 
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width-1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;


}

// controls
void Input()
{
    // when keyboard is pressed. T or F
    if (_kbhit())
    {
        // gets the key 
        switch (_getch())
        {
            case 'a':
                if (lastDir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (lastDir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
                if (lastDir != DOWN)
                    dir = Up;
                break;
            case 's':
                if (lastDir != Up)
                    dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void Logic()
{
    // begining part is for the tail of the snake
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    for( int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        tailX[0] = x;
        tailY[0] = y;
    }
    switch (dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case Up:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // if you run into tail segment, you die 
    for (int i = 0; i < nTail; i ++)
        if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail ++ ;
    }
}
int main()
{
   Setup();
   while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        // Sleep(10);
    }
   return 0;
}