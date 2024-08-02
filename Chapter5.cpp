#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void printMaze();
void printAirCraft();
void clearAirCraft();
void movePlayerLeft();
void movePlayerRight();
int playerX = 3;
int playerY = 23;

void printEnemy();
void clearEnemy();
void moveEnemy();
void moveEnemyRight();
void moveEnemyLeft();

bool isEnemyMovementRight = true;
int enemyX = 10;
int enemyY = 3;

int main()
{
    system("CLS");
    printMaze();
    printAirCraft();

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }

        moveEnemy();
        Sleep(80);

    }
}

void printMaze()
{
    cout << " ####################################################################################" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " #                                                                                  #" << endl;
    cout << " ####################################################################################" << endl;
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
void printAirCraft()
{
    gotoxy(playerX, playerY);
    cout << "      /\\     ";
    gotoxy(playerX, playerY + 1);
    cout << "   __/~~\\__  ";
    gotoxy(playerX, playerY + 2);
    cout << " /   |  |   \\";
    gotoxy(playerX, playerY + 3);
    cout << "=====.  .=====";
    gotoxy(playerX, playerY + 4);
    cout << "     ||||     ";
}
void printEnemy()
{
    gotoxy(enemyX, enemyY);
    cout << "   _---.--_   ";
    gotoxy(enemyX, enemyY + 1);
    cout << "  /__/~~\\__\\";
    gotoxy(enemyX, enemyY + 2);
    cout << " |   |\"\"|   |";
    gotoxy(enemyX, enemyY + 3);
    cout << "|====.  .====|";
    gotoxy(enemyX, enemyY + 4);
    cout << "\\____________/";
}
void clearAirCraft()
{
    gotoxy(playerX, playerY);
    cout << "             ";
    gotoxy(playerX, playerY + 1);
    cout << "             ";
    gotoxy(playerX, playerY + 2);
    cout << "             ";
    gotoxy(playerX, playerY + 3);
    cout << "              ";
    gotoxy(playerX, playerY + 4);
    cout << "             ";
}

void clearEnemy()
{
    gotoxy(enemyX, enemyY);
    cout << "             ";
    gotoxy(enemyX, enemyY + 1);
    cout << "             ";
    gotoxy(enemyX, enemyY + 2);
    cout << "             ";
    gotoxy(enemyX, enemyY + 3);
    cout << "              ";
    gotoxy(enemyX, enemyY + 4);
    cout << "              ";
}
void movePlayerLeft()
{
    if (getCharAtxy(playerX - 1, playerY) == ' ')
    {
        clearAirCraft();
        playerX = playerX - 1;
        printAirCraft();
    }
}
void movePlayerRight()
{
    if (getCharAtxy(playerX + 14, playerY) == ' ')
    {
        clearAirCraft();
        playerX = playerX + 1;
        printAirCraft();
    }
}
void moveEnemy()
{
    if(isEnemyMovementRight)
    {
        moveEnemyRight();
    }
    else
    {
        moveEnemyLeft();
    }
}
void moveEnemyRight()
{
    if (getCharAtxy(enemyX + 14, enemyY) == ' ')
    {
        clearEnemy();
        enemyX = enemyX + 1;
        printEnemy();
    }
    else
    {
        isEnemyMovementRight=false;
    }
}


void moveEnemyLeft()
{
    if (getCharAtxy(enemyX - 1, enemyY) == ' ')
    {
        clearEnemy();
        enemyX = enemyX - 1;
        printEnemy();
    }
    else
    {
        isEnemyMovementRight=true;
    }
}
