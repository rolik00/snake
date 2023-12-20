#include <conio.h> 
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <windows.h> 
using namespace std;

const int width = 80;
const int height = 20;
int x, y;
const char snake = 1;
int fruitX, fruitY;
int Score;
int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection dir;
bool isGameOver;
 
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void GameInit()
{
	isGameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	Score = 0;
}

void GameField()
{
	system("cls");
	hidecursor();
	for (int i = 0; i < width + 2; i++) cout << "\033[1;30m" << "-";
	cout << endl;
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j <= width; j++) 
		{ 
			if (j == 0 || j == width) cout << "\033[1;30m" << "|";
			if (i == y && j == x) cout << "\033[1;32m" << snake;
			else if (i == fruitY && j == fruitX) cout << "\033[1;31m" << "@";
			else 
			{
				bool prTail = false;
				for (int k = 0; k < snakeTailLen; k++) 
				{
					if (snakeTailX[k] == j && snakeTailY[k] == i) 
					{
						cout << "\033[1;32m" << "o";
						prTail = true;
					}
				}
				if (!prTail) cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) cout << "\033[1;30m" << "-";
	cout << endl;
	cout << "\033[1;97m" <<  "Score: " << Score << endl;
}

void GameCycle()
{
	int prevX = snakeTailX[0];
	int prevY = snakeTailY[0];
	int prev2X, prev2Y;
	snakeTailX[0] = x;
	snakeTailY[0] = y;
	for (int i = 1; i < snakeTailLen; i++) {
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		snakeTailX[i] = prevX;
		snakeTailY[i] = prevY;
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
	}
	if (x >= width || x < 0 || y >= height || y < 0) isGameOver = true;
	for (int i = 0; i < snakeTailLen; i++) if (snakeTailX[i] == x && snakeTailY[i] == y) isGameOver = true;
	if (x == fruitX && y == fruitY) 
	{
		Score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		snakeTailLen++;
	}
}

void UserInput()
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
		case '\033': //esc
			isGameOver = true;
			break;
		}
	}
}
 
int main()
{
	srand(time(0)); // for random
	GameInit();
	while (!isGameOver) 
	{
		GameField();
		UserInput();
		GameCycle(); 
		Sleep(50);
	}
	return 0;
}
