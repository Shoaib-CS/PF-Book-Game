#include <iostream>
#include<conio.h>
#include <fstream>
#include <windows.h>
using namespace std;

// Function declarations
void gotoxy(int x, int y);
void erasePlayer();
void printPlayer();
void drawBoard();
bool LoadMaze(const string &filename);
bool LoadAircraftFromFile();
bool LoadEnemyFromFile();
bool LoadDefaultRecordsFromFile();
void movePlayerLeft();
void movePlayerRight();
void drawRecords();
void createBullet();
void eraseBullet(int count);
void moveBullet();
void moveBulletSteps(int currentBullet, int steps);
void printEnemy();
void eraseEnemy();
void moveEnemy();
void moveEnemyLeft();
void moveEnemyRight();
void removeBullet(int index);
bool isBulletWallCollision(int bulletX, int bulletY);
bool isBulletEnemyCollision(int bulletX, int bulletY);

const int boardHeight = 35, boardWidth = 105;

char board[boardHeight][boardWidth];

int playerX;
int playerY;
int playerHealth;
const int playerHeight = 5;
const int playerWidth = 15;
char aircraft[playerHeight][playerWidth] = {};

int enemyX;
int enemyY;
int enemyHealth;
const int enemyHeight = 5;
const int enemyWidth = 15;
bool isEnemyMovementRight = true;
char enemy[enemyHeight][enemyWidth] = {};

int bulletX[200];
int bulletY[200];
int bulletCount = 0;

int timeStamp = 0; // Add timeStamp variable

bool isGameOver=false;

int main()
{
    system("cls");
    if (LoadMaze("defaultMaze.txt") && LoadAircraftFromFile() && LoadEnemyFromFile() && LoadDefaultRecordsFromFile())
    {
        drawBoard();
        printPlayer();
        printEnemy();

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

            if(isGameOver)
            {
                break;
            }
            moveEnemy();
            moveBullet();
            drawRecords();
            Sleep(70);
            timeStamp++; // Increment timeStamp
            
        }
    }
    else
    {
        cout << "Failed to load maze file." << endl;
    }

    system("cls");
    gotoxy(20,10);
    cout<<"GAME OVER! YOU WON!!";
    gotoxy(20,11);
    cout<<"Press any key to exit";
    getch();
    return 0;
}

void movePlayerLeft()
{
    if (board[playerY][playerX - 1] == ' ')
    {
        erasePlayer();
        board[playerY][playerX] = ' ';
        playerX = playerX - 1;
        board[playerY][playerX] = 'p';
        printPlayer();
    }
}

void movePlayerRight()
{
    if ((board[playerY][playerX + playerWidth] == ' '))
    {
        erasePlayer();
        board[playerY][playerX] = ' ';
        playerX = playerX + 1;
        board[playerY][playerX] = 'p';
        printPlayer();
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

void moveEnemyLeft()
{
    if (board[enemyY][enemyX - 1] != '#')
    {
        eraseEnemy();
        board[enemyY][enemyX] = ' ';
        enemyX = enemyX - 1;
        board[enemyY][enemyX] = 'E';
        printEnemy();
    }
    else
    {
        isEnemyMovementRight = true;
    }
}

void moveEnemyRight()
{
    if ((board[enemyY][enemyX + enemyWidth + 1] != '#'))
    {
        eraseEnemy();
        board[enemyY][enemyX] = ' ';
        enemyX = enemyX + 1;
        board[enemyY][enemyX] = 'E';
        printEnemy();
    }
    else
    {
        isEnemyMovementRight = false;
    }
}

bool LoadMaze(const string &filename)
{
    const string path = "defaultMaze.txt";
    fstream mazeFile(path, ios::in); // Open the file in read mode

    if (mazeFile.is_open())
    {
        string line;
        int i = 0;
        while (getline(mazeFile, line))
        {
            for (int j = 0; j < line.length(); j++)
            {
                board[i][j] = line[j];
                if (board[i][j] == 'P')
                {
                    playerX = j;
                    playerY = i;
                }

                if (board[i][j] == 'E')
                {
                    enemyX = j;
                    enemyY = i;
                }
            }
            i++;
        }
        mazeFile.close();
        return true;
    }
    else
    {
        mazeFile.close();
        return false;
    }
}

void drawBoard()
{
    gotoxy(0, 0);
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void drawRecords()
{
    gotoxy(5, 37);
    cout << "Player Health: " << playerHealth;
    gotoxy(5, 38);
    cout << "Enemy Health: " << enemyHealth;
    gotoxy(5, 39);
    cout << "************";

}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void erasePlayer()
{
    for (int i = 0; i < playerHeight; i++)
    {
        for (int j = 0; j < playerWidth; j++)
        {
            gotoxy(playerX + j, playerY + i);
            cout << " ";
        }
    }
}

void printPlayer()
{
    for (int i = 0; i < playerHeight; i++)
    {
        for (int j = 0; j < playerWidth; j++)
        {
            gotoxy(playerX + j, playerY + i);
            cout << aircraft[i][j];
        }
    }
}

void createBullet()
{
    if (bulletCount < 200)  // Ensure we don't exceed the array bounds
    {
        char bullet = 207;

        bulletX[bulletCount] = playerY - 1;
        bulletY[bulletCount] = playerX + 6;

        board[bulletX[bulletCount]][bulletY[bulletCount]] = bullet;

        gotoxy(bulletY[bulletCount], bulletX[bulletCount]);
        cout << bullet;

        bulletCount++;
    }
}

void eraseBullet(int count)
{
    gotoxy(bulletY[count], bulletX[count]);
    cout << ' ';
    board[bulletX[count]][bulletY[count]] = ' ';
}

void moveBullet()
{
    char bullet = 207;
    for (int i = 0; i < bulletCount; i++)
    {
        eraseBullet(i);
        bulletX[i]--;

        if (bulletX[i] < 0 || isBulletWallCollision(bulletX[i], bulletY[i]))
        {
            // Remove bullet if it hits a wall or goes out of bounds
            removeBullet(i);
            i--; // Adjust index to check the next bullet
        }
        else if (isBulletEnemyCollision(bulletX[i], bulletY[i]))
        {
            // Handle collision with enemy
            removeBullet(i);
            i--; // Adjust index to check the next bullet
            enemyHealth--; // Decrease enemy health
            if (enemyHealth <= 0)
            {
                isGameOver=true;
                return;

            }
        }
        else
        {
            board[bulletX[i]][bulletY[i]] = bullet;
            gotoxy(bulletY[i], bulletX[i]);
            cout << bullet;
        }
    }
}

void printEnemy()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(enemyX + j, enemyY + i);
            cout << enemy[i][j];
        }
    }
}

void eraseEnemy()
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            gotoxy(enemyX + j, enemyY + i);
            cout << " ";
        }
    }
}

bool LoadAircraftFromFile()
{
    string path = "aircraft.txt";
    fstream file(path, ios::in);
    if (file.is_open())
    {
        string line;
        int i = 0;
        while (getline(file, line))
        {
            for (int j = 0; j < line.length(); j++)
            {
                aircraft[i][j] = line[j];
            }
            i++;
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool LoadDefaultRecordsFromFile()
{
    string path = "defaultRecords.txt";
    fstream file(path, ios::in);
    if (file.is_open())
    {
        string line;
        int i = 0;
        getline(file, line);
        playerHealth = stoi(line);

        getline(file, line);
        enemyHealth = stoi(line);

        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool LoadEnemyFromFile()
{
    string path = "enemy.txt";
    fstream file(path, ios::in);
    if (file.is_open())
    {
        string line;
        int i = 0;
        while (getline(file, line))
        {
            for (int j = 0; j < line.length(); j++)
            {
                enemy[i][j] = line[j];
            }
            i++;
        }
        file.close();
        return true;
    }
    else
    {
        return false;
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

bool isBulletWallCollision(int bulletX, int bulletY)
{
    return board[bulletX][bulletY] == '#';
}

bool isBulletEnemyCollision(int bulletX, int bulletY)
{
    for (int i = 0; i < enemyHeight; i++)
    {
        for (int j = 0; j < enemyWidth; j++)
        {
            if (bulletX == enemyY + i && bulletY == enemyX + j && enemy[i][j] != ' ')
            {
                return true;
            }
        }
    }
    return false;
}
