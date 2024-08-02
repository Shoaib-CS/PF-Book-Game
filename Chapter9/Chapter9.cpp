#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

// Function declarations
void gotoxy(int x, int y);
void erasePlayer();
void printPlayer();
void drawBoard();
bool LoadMaze(string path);
bool LoadAircraftFromFile();
bool LoadEnemyFromFile();
bool LoadRecordsFromFile(string path);
void movePlayerLeft();
void movePlayerRight();
void drawRecords();
void createBullet();
void eraseBullet(int count);
void moveBullet();
void printEnemy();
void eraseEnemy();
void moveEnemy();
void moveEnemyLeft();
void moveEnemyRight();
void removeBullet(int index);
bool isBulletWallCollision(int bulletX, int bulletY);
bool isBulletEnemyCollision(int bulletX, int bulletY);
bool checkGameStatus();
bool saveMazeToFile(string path);
bool saveRecordsToFile(string path);
void saveGameState();
void handleGameOver();

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
int timeStamp = 0;

int main()
{
    bool isGameOver = false;
    string mazePath;
    string recordsPath;

    system("cls");

    // Ask user whether to load default or saved files
    cout << "Do you want to load default or saved files? (D/S): ";
    char choice = getch();

    if (choice == 'S' || choice == 's')
    {
        mazePath = "savedMaze.txt";
        recordsPath = "savedRecords.txt";
    }
    else
    {
        mazePath = "defaultMaze.txt";
        recordsPath = "defaultRecords.txt";
    }

    if (LoadMaze(mazePath) && LoadRecordsFromFile(recordsPath) && LoadAircraftFromFile() && LoadEnemyFromFile())
    {
        system("cls");

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
            if (GetAsyncKeyState(VK_SPACE) && timeStamp >= 3)
            {
                createBullet();
                timeStamp = 0;
            }
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                saveGameState();

                system("cls");
                gotoxy(20, 10);
                cout << "GAME Save!";
                gotoxy(20, 11);
                cout << "Press any key to exit";
                getch();
                return 0;
            }

            isGameOver = checkGameStatus();
            if (isGameOver)
            {
                handleGameOver();
                break;
            }
            moveEnemy();
            moveBullet();
            drawRecords();
            Sleep(70);
            timeStamp++;
        }
    }
    else
    {
        cout << "Failed to load files." << endl;
    }

    return 0;
}

void movePlayerLeft()
{
    if (playerX > 0 && board[playerY][playerX - 1] == ' ')
    {
        erasePlayer();
        board[playerY][playerX] = ' ';
        playerX = playerX - 1;
        board[playerY][playerX] = 'P';
        printPlayer();
    }
}

void movePlayerRight()
{
    if (playerX + playerWidth < boardWidth && board[playerY][playerX + playerWidth] == ' ')
    {
        erasePlayer();
        board[playerY][playerX] = ' ';
        playerX = playerX + 1;
        board[playerY][playerX] = 'P';
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
    if (enemyX > 0 && board[enemyY][enemyX - 1] != '#')
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
    if (enemyX + enemyWidth < boardWidth && board[enemyY][enemyX + enemyWidth + 1] != '#')
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

bool LoadMaze(string path)
{
    char bullet = 207; // char of bullet

    fstream mazeFile(path, ios::in);

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
    cout << "Player Health: " << playerHealth << "   ";
    gotoxy(5, 38);
    cout << "Enemy Health: " << enemyHealth << "   ";
    gotoxy(5, 39);
    cout << "Press esc to save file and exit!";

    gotoxy(5, 40);
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

bool LoadRecordsFromFile(string path)
{
    fstream file(path, ios::in);
    if (file.is_open())
    {
        string line;
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

void createBullet()
{
    char bullet = 207;

    bulletX[bulletCount] = playerY - 1;
    bulletY[bulletCount] = playerX + 6;

    board[bulletX[bulletCount]][bulletY[bulletCount]] = bullet;

    gotoxy(bulletY[bulletCount], bulletX[bulletCount]);
    cout << bullet;

    bulletCount++;
}

void moveBullet()
{
    char bullet = 207;
    for (int i = 0; i < bulletCount; i++)
    {
        eraseBullet(i);
        bulletX[i] = bulletX[i] - 1;

        if (bulletX[i] < 0 || isBulletWallCollision(bulletX[i], bulletY[i]))
        {
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
            board[bulletX[i]][bulletY[i]] = bullet;
            gotoxy(bulletY[i], bulletX[i]);
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
    gotoxy(bulletY[count], bulletX[count]);
    cout << ' ';
    board[bulletX[count]][bulletY[count]] = ' ';
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

bool checkGameStatus()
{
    if (enemyHealth <= 0)
    {
        return true;
    }
    return false;
}
bool saveMazeToFile(string path)
{
    char bullet = 207; // char for bullet
    fstream mazeFile(path, ios::out);
    if (mazeFile.is_open())
    {
        for (int i = 0; i < boardHeight; i++)
        {
            for (int j = 0; j < boardWidth; j++)
            {
                if (board[i][j] == bullet)
                {
                    mazeFile << ' ';
                }
                else
                {
                    mazeFile << board[i][j];
                }
            }
            // Only add a newline if it's not the last line
            if (i < boardHeight - 1)
            {
                mazeFile << endl;
            }
        }
        mazeFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool saveRecordsToFile(string path)
{
    fstream recordsFile(path, ios::out);
    if (recordsFile.is_open())
    {
        recordsFile << playerHealth << endl;
        recordsFile << enemyHealth;
        recordsFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

void saveGameState()
{
    bool mazeSaved = saveMazeToFile("savedMaze.txt");
    bool recordsSaved = saveRecordsToFile("savedRecords.txt");

    if (mazeSaved && recordsSaved)
    {
        cout << "Game state saved successfully." << endl;
    }
    else
    {
        cout << "Failed to save game state. Files not found or error occurred." << endl;
    }
}

void handleGameOver()
{
    system("cls");
    gotoxy(20, 10);
    cout << "GAME OVER! YOU WON!!";
    gotoxy(20, 11);
    cout << "Press any key to exit";
    getch();
}
