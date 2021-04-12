#include <iostream>
#include <conio.h>
#include <windows.h>
#define REDB "\e[41m"
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int scoresList[3];
//int count = 1;
char answer;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//void sortScores(int[], int);

void ShowScores(int scoresList[], int score)
{
    static int count = 0;
    cout << endl << "Last " << 3 << " Scores" << endl;
    scoresList[count] = score;
    count++;
    for (int i = 0; i < 3; i++)
    {
        cout << "Score " << i + 1 << ":\t\t" << scoresList[i] << endl;
    }
}


void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|";
            SetConsoleTextAttribute(h, 12);
            if (i == y && j == x)
                cout << "O";


            else if (i == fruitY && j == fruitX)
                cout << "*";
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


            if (j == width - 1)
                cout << "|";

        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    SetConsoleTextAttribute(h, 11);
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
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
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x > width || x < 0 || y > height || y < 0)
    {
        ShowScores(scoresList, score);
        cout << endl << "Do you want to play again? (Y/N) " << endl;
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            nTail = 0;
            system("cls");
            Setup();
        }
        else if (answer == 'n' || answer == 'N')
        {
            gameOver = true;
        }
    }
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) {

            ShowScores(scoresList, score);

            cout << endl << "Do you want to play again? (Y/N) " << endl;
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {
                nTail = 0;
                system("cls");
                Setup();
            }
            else if (answer == 'n' || answer == 'N')
            {
                gameOver = true;
            }
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}