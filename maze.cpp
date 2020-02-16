/*
원저작자: Nerdydream
수정: LJLee37
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//data types and global variables
typedef struct 
{
	int row;
	int col;
} Movedata;
typedef struct 
{
	int row;
	int col;
	int dir;
} Routedata;
Movedata Movetype[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
Routedata Route[100] = {{ 1, 1, 4 }};
bool Check[10][10] = { false };
int Maze[10][10];
int Turns = 0;

//functions
void MazeReset() 
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if ((i == 0 || i == 9) || (j == 0 || j == 9))
				Maze[i][j] = 1;
			else if ((i == 1 && j == 1) || (i == 8 && j == 8))
				Maze[i][j] = 0;
			else
				Maze[i][j] = rand() % 2;
}

void MazePrint() 
{
	printf("\n");
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
			if (Route[Turns].row == i && Route[Turns].col == j)
				printf("*");
			else if ((i == 1 && j == 1) || (i == 8 && j == 8))
				printf("#");
			else
				printf("%c", Maze[i][j] ? '◆' : '0');
		printf("\n");
	}
	printf("\n\n");
}

void CheckMaze() 
{
	printf("\n\n");
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
			if ((i == 1 && j == 1) || (i == 8 && j == 8))
				printf("#");
			else if (Check[i][j] == true)
				printf("@");
			else
				printf("%c", Maze[i][j] ? '◆' : '0');
		printf("\n");
	}
	printf("\n\n");
}

void Move() 
{
	int dir = 0;
	for (dir = 0; dir < 8; dir++)
		if (Check[Route[Turns].row + Movetype[dir].row][Route[Turns].col + Movetype[dir].col] == false && Maze[Route[Turns].row + Movetype[dir].row][Route[Turns].col + Movetype[dir].col] == 0) 
		{
			Turns++;
			Route[Turns].row = Route[Turns - 1].row + Movetype[dir].row;
			Route[Turns].col = Route[Turns - 1].col + Movetype[dir].col;
			Route[Turns].dir = dir;
			Check[Route[Turns].row][Route[Turns].col] = true;
			printf("Turn %d : (%d, %d, %d)\n\n", Turns, Route[Turns].row, Route[Turns].col, Route[Turns].dir);
			break;
		}
	if (dir == 8) 
	{
		Turns--;
		printf("Back to Turn %d : (%d, %d, %d)\n\n", Turns, Route[Turns].row, Route[Turns].col, Route[Turns].dir);
	}
}

void pause()
{
	printf("계속하려면 [Enter]키를 누르세요...");
	getc(stdin);
}

//main
int main()
{
	Check[1][1] = true;
	MazeReset();
	MazePrint();
	//여기에 턴 표시방식 선택 추가
	printf("한 턴씩 표시하시겠습니까?(Y | N): ");
	char check = 'N';
	scanf("%c", &check);
	bool isOneByOne = (charIsOneByOne == 'Y' | charIsOneByOne == 'y')? true : false;
	while (Turns >= 0 && !(Route[Turns].row == 8 && Route[Turns].col == 8)) 
	{
		Move();
		MazePrint();
		if(isOneByOne)
			pause();
	}
	if (Turns < 0)
		printf("길이 존재하지 않습니다.\n");
	if (Route[Turns].row == 8 && Route[Turns].col == 8)
		printf("도착하였습니다.\n");
	CheckMaze();
	return 0;
}
