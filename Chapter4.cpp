#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void printMaze();
void printAirCraft();
void clearAirCraft();
int x = 3;
int y = 23;

int main()
{
    system("CLS");
    printMaze();
    printAirCraft();

    while (true)
    {

        if (GetAsyncKeyState(VK_LEFT))
        {
            if (getCharAtxy(x - 1, y) == ' ')
            {
                clearAirCraft();
                x=x-1;
                printAirCraft();
            }
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (getCharAtxy(x + 14, y) == ' ')
            {
                clearAirCraft();
                x=x+1;
                printAirCraft();
            }
        }
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
