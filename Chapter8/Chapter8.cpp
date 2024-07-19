#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
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
char aircraftRow1[aircraftWidth];
char aircraftRow2[aircraftWidth];
char aircraftRow3[aircraftWidth];
char aircraftRow4[aircraftWidth];
char aircraftRow5[aircraftWidth];

// Enemy rows defined as parallel arrays
const int enemyWidth = 15;
const int enemyHeight = 5;

char enemyRow1[enemyWidth];
char enemyRow2[enemyWidth];
char enemyRow3[enemyWidth];
char enemyRow4[enemyWidth];
char enemyRow5[enemyWidth];

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

string getField(string record, int field);
bool saveRecordsToFile(string path);
bool LoadRecordsFromFile(string path);
bool LoadAircraftFromFile();
bool LoadEnemyFromFile();
void saveGameState();

int main()
{
    
    bool isGameOver = false;
    string recordsPath;
    system("cls");

    // Ask user whether to load default or saved files
    cout << "Do you want to load default or saved files? (D/S): ";
    char choice = getch();

    if (choice == 'S' || choice == 's')
    {
        recordsPath = "savedRecords.txt";
    }
    else
    {
        recordsPath = "defaultRecords.txt";
    }

    if (LoadRecordsFromFile(recordsPath)&& LoadAircraftFromFile() && LoadEnemyFromFile())
    {
        system("Color 03");
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
            if (GetAsyncKeyState(VK_SPACE) && timeStamp >= 3) // Check if enough time has passed
            {
                createBullet();
                timeStamp = 0; // Reset timeStamp
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
    else
    {
        cout << "Failed to load files." << endl;
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
    cout << enemyRow1 << endl;
    gotoxy(enemyX, enemyY+1);
    cout << enemyRow2 << endl;
    gotoxy(enemyX, enemyY+2);
    cout << enemyRow3 << endl;
    gotoxy(enemyX, enemyY+3);
    cout << enemyRow4 << endl;
    gotoxy(enemyX, enemyY+4);
    cout << enemyRow5 << endl;
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

    //NOTE: If you don't want to harcore values, you can use the following approach too.
    //More over, you can also use two for loops too for this purpose.

    // gotoxy(playerX, playerY);
    // for (int i = 0; i < aircraftWidth; i++)
    // {
    //     cout << ' ';
    // }
    // gotoxy(playerX, playerY + 1);
    // for (int i = 0; i < aircraftWidth; i++)
    // {
    //     cout << ' ';
    // }
    // gotoxy(playerX, playerY + 2);
    // for (int i = 0; i < aircraftWidth; i++)
    // {
    //     cout << ' ';
    // }
    // gotoxy(playerX, playerY + 3);
    // for (int i = 0; i < aircraftWidth; i++)
    // {
    //     cout << ' ';
    // }
    // gotoxy(playerX, playerY + 4);
    // for (int i = 0; i < aircraftWidth; i++)
    // {
    //     cout << ' ';
    // }
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
    if (getCharAtxy(playerX + 15, playerY) == ' ')
    {
        clearAirCraft();
        playerX = playerX + 1;
        printAirCraft();
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
    cout << "Press esc to save file and exit!";
    gotoxy(5, 40);
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
        bulletY[i]--;

        if (bulletY[i] < 2 || isBulletWallCollision(bulletX[i], bulletY[i]))
        {
            // Remove bullet if it hits a wall or goes out of bounds
            removeBullet(i);
            i--; // Adjust index to check the next bullet
        }
        else if (isBulletEnemyCollision(bulletX[i], bulletY[i]))
        {
            // Handle collision with enemy
            removeBullet(i);
            i--;           // Adjust index to check the next bullet
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

bool LoadAircraftFromFile()
{
    string path = "aircraft.txt";
    ifstream file(path);
    if (file.is_open())
    {
        string line;
        int i = 0;
        while (getline(file, line))
        {
            for (int j = 0; j < line.length(); j++)
            {
                if (i == 0)
                {
                    aircraftRow1[j] = line[j];
                }
                else if (i == 1)
                {
                    aircraftRow2[j] = line[j];
                }
                else if (i == 2)
                {
                    aircraftRow3[j] = line[j];
                }
                else if (i == 3)
                {
                    aircraftRow4[j] = line[j];
                }
                else if (i == 4)
                {
                    aircraftRow5[j] = line[j];
                }
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

bool LoadEnemyFromFile()
{
    string path = "enemy.txt";
    ifstream file(path);
    if (file.is_open())
    {
        string line;
        int i = 0;
        while (getline(file, line))
        {
            for (int j = 0; j < line.length(); j++)
            {
                if (i == 0)
                {
                    enemyRow1[j] = line[j];
                }
                else if (i == 1)
                {
                    enemyRow2[j] = line[j];
                }
                else if (i == 2)
                {
                    enemyRow3[j] = line[j];
                }
                else if (i == 3)
                {
                    enemyRow4[j] = line[j];
                }
                else if (i == 4)
                {
                    enemyRow5[j] = line[j];
                }
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

string getField(string record, int field)
{
    int commaCount = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}

bool saveRecordsToFile(string path)
{
    fstream recordsFile(path, ios::out);
    if (recordsFile.is_open())
    {
        recordsFile <<playerX<<","<<playerY<<","<< playerHealth << endl;
        recordsFile <<enemyX<<","<<enemyY<<","<< enemyHealth << endl;
        recordsFile.close();
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
        playerX = stoi(getField(line,1));
        playerY = stoi(getField(line,2));
        playerHealth = stoi(getField(line,3));

        getline(file, line);
        enemyX = stoi(getField(line,1));
        enemyY = stoi(getField(line,2));
        enemyHealth = stoi(getField(line,3));

        file.close();
        return true;
    }
    else
    {
        return false;
    }
}
void saveGameState()
{
    bool recordsSaved = saveRecordsToFile("savedRecords.txt");

    if (recordsSaved)
    {
        cout << "Game state saved successfully." << endl;
    }
    else
    {
        cout << "Failed to save game state. Files not found or error occurred." << endl;
    }
}