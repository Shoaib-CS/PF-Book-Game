#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void printMaze();
void printAircraft();
void clearAircraft();
void movePlayerLeft();
void movePlayerRight();
int playerX = 3;
int playerY = 23;
int playerHealth = 20;

void printEnemy();
void clearEnemy();
void moveEnemy();
void moveEnemyRight();
void moveEnemyLeft();

bool isEnemyMovementRight = true;
int enemyX = 10;
int enemyY = 3;
int enemyHealth = 25;

const int aircraftWidth = 15;
const int aircraftHeight = 5;

// Aircraft rows defined as parallel arrays
char aircraftRow1[aircraftWidth] = "      /\\     ";
char aircraftRow2[aircraftWidth] = "   __/~~\\__  ";
char aircraftRow3[aircraftWidth] = " /   |  |   \\";
char aircraftRow4[aircraftWidth] = "=====.  .=====";
char aircraftRow5[aircraftWidth] = "     ||||     ";

// Enemy rows defined as parallel arrays
const int enemyWidth = 15;
const int enemyHeight = 5;

char enemyRow1[enemyWidth] = "   _---.--_   ";
char enemyRow2[enemyWidth] = "  /__/~~\\__\\";
char enemyRow3[enemyWidth] = " |   |\"\"|   |";
char enemyRow4[enemyWidth] = "|====.  .====|";
char enemyRow5[enemyWidth] = "\\____________/";

void drawRecords();

void createBullet();
void moveBullet();
void removeBullet(int index);
void eraseBullet(int count);
bool isBulletWallCollision(int bulletX, int bulletY);
bool isBulletEnemyCollision(int bulletX, int bulletY);
bool checkGameStatus();
int bulletX[200];
int bulletY[200];
int bulletCount = 0;

int timeStamp = 0; // Add timeStamp variable for bullet speed

int main()
{
    bool isGameOver = false;
    system("CLS");
    printMaze();
    printAircraft();

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
        if (GetAsyncKeyState(VK_SPACE) && timeStamp >= 3) // Check if enough time has passed
        {
            createBullet();
            timeStamp = 0; // Reset timeStamp
        }

        isGameOver = checkGameStatus();
        if (isGameOver)
        {
            break;
        }

        moveEnemy();
        moveBullet();
        drawRecords();
        timeStamp++;
        Sleep(80);
    }

    system("cls");
    gotoxy(20, 10);
    cout << "GAME OVER! YOU WON!!";
    gotoxy(20, 11);
    cout << "Press any key to exit";
    getch();
    return 0;
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

void printAircraft()
{
    
    gotoxy(playerX, playerY);
    cout << aircraftRow1 << endl;
    gotoxy(playerX, playerY+1);
    cout << aircraftRow2 << endl;
    gotoxy(playerX, playerY+2);
    cout << aircraftRow3 << endl;
    gotoxy(playerX, playerY+3);
    cout << aircraftRow4 << endl;
    gotoxy(playerX, playerY+4);
    cout << aircraftRow5 << endl;
}

void printEnemy()
{
    
    gotoxy(enemyX, enemyY);
    cout << enemyRow1 << endl; //Note that char array is actually a string, so we can print directly without loop on the array.
    gotoxy(enemyX, enemyY+1);
    cout << enemyRow2 << endl;
    gotoxy(enemyX, enemyY+2);
    cout << enemyRow3 << endl;
    gotoxy(enemyX, enemyY+3);
    cout << enemyRow4 << endl;
    gotoxy(enemyX, enemyY+4);
    cout << enemyRow5 << endl;
}

void clearAircraft()
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
        clearAircraft();
        playerX = playerX - 1;
        printAircraft();
    }
}
void movePlayerRight()
{
    if (getCharAtxy(playerX + 15, playerY) == ' ')
    {
        clearAircraft();    
        playerX = playerX + 1;
        printAircraft(); 
    }
}
void moveEnemy()
{
    if (isEnemyMovementRight)
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
    if (getCharAtxy(enemyX + 15, enemyY) == ' ')
    {
        clearEnemy();
        enemyX = enemyX + 1;
        printEnemy();
    }
    else
    {
        isEnemyMovementRight = false;
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
        isEnemyMovementRight = true;
    }
}
void drawRecords()
{
    gotoxy(5, 37);
    cout << "Player Health: " << playerHealth << "   "; // Add spaces to clear previous value
    gotoxy(5, 38);
    cout << "Enemy Health: " << enemyHealth << "   "; // Add spaces to clear previous value
    gotoxy(5, 39);
    cout << "************";
}

void createBullet()
{
    char bullet = 207;

    bulletX[bulletCount] = playerX + 6;
    bulletY[bulletCount] = playerY - 1;

    gotoxy(bulletX[bulletCount], bulletY[bulletCount]);
    cout << bullet;

    bulletCount++;
}

void moveBullet()
{
    char bullet = 207;
    for (int i = 0; i < bulletCount; i++)
    {
        eraseBullet(i);
        bulletY[i] = bulletY[i]-1;

        if (bulletY[i] < 2 || isBulletWallCollision(bulletX[i], bulletY[i]))
        {
            // Remove bullet if it hits a wall or goes out of bounds
            removeBullet(i);
        }
        else if (isBulletEnemyCollision(bulletX[i], bulletY[i]))
        {
            // Handle collision with enemy
            removeBullet(i);
            enemyHealth--; // Decrease enemy health
        }
        else
        {
            gotoxy(bulletX[i], bulletY[i]);
            cout << bullet;
        }
    }
}

void removeBullet(int index)
{
    for (int i = index; i < bulletCount - 1; i++)
    {
        bulletX[i] = bulletX[i + 1];
        bulletY[i] = bulletY[i + 1];
    }
    bulletCount--;
}
void eraseBullet(int count)
{
    gotoxy(bulletX[count], bulletY[count]);
    cout << ' ';
}

bool isBulletWallCollision(int bulletX, int bulletY)
{
    return getCharAtxy(bulletX, bulletY) == '#'; // if this is equal then true is returned, else false.

    /*
    //It can also be implemented as:
    if(getCharAtxy(bulletX, bulletY) == '#')
    {
        return true;
    }
    return false; 
    */
}

bool isBulletEnemyCollision(int bulletX, int bulletY)
{
    for (int i = 0; i < 14; i++) // enemy width
    {
        for (int j = 0; j < 5; j++) // enemy height
        {
            if (bulletX == enemyX + i && bulletY == enemyY + j && getCharAtxy(enemyX + i, enemyY + j) != ' ')
            {
                // this checks the whole enemy width and height.
                // The 3rd conditions ensures that even in this range, space is not considered to be a place of collision.

                return true;
            }
        }
    }
    return false;
}
bool checkGameStatus()
{
    if (enemyHealth <= 0) // if multiple enemies, it can be added here using && operator.
    {
        return true;
    }
    return false;
}