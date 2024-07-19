#include <iostream>
#include <windows.h>
using namespace std;


void gotoxy(int x, int y);
void printMaze();
void printAirCraft();
void clearAirCraft();
    int x = 3;
    int y = 23;

int main()
{
    system("Color 04");
    system("CLS");
    printMaze();


    while (true)
    {
        clearAirCraft();
        x = x + 1;
        if (x == 70)
        {
            x = 3;
        }
        printAirCraft();
        Sleep(100);
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

void printAirCraft()
{
    gotoxy(x, y);
    cout << "      /\\     ";
    gotoxy(x, y + 1);
    cout << "   __/~~\\__  ";
    gotoxy(x, y + 2);
    cout << " /   |  |   \\";
    gotoxy(x, y + 3);
    cout << "=====.  .=====";
    gotoxy(x, y + 4);
    cout << "     ||||     ";
}

void clearAirCraft()
{
    gotoxy(x, y);
    cout << "             ";
    gotoxy(x, y + 1);
    cout << "             ";
    gotoxy(x, y + 2);
    cout << "             ";
    gotoxy(x, y + 3);
    cout << "              ";
    gotoxy(x, y + 4);
    cout << "             ";
}
