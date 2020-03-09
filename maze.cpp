/*
원저작자: Nerdydream
수정: LJLee37
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stack>
#include <queue>
#include <memory>
#include <iostream>
using namespace std;

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
Movedata movetype[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
bool check[10][10] = { false };
int maze[10][10];
shared_ptr<Routedata> INIT_DATA = make_shared<Routedata, Routedata>({1,1,4});
//function prototypes
//미로 초기화
void mazeReset();
//최초 상태 출력
void mazePrint();
//지나간 길 표시
void checkMaze();
//일시정지
void pause();
//DFS방식을 이용하여 경로 탐색 후 queue<shared_ptr<Routedata>>& 타입으로 반환
queue<shared_ptr<Routedata>> DFSFind();
//BFS방식을 이용하여 경로 탐색 후 queue<shared_ptr<Routedata>>& 타입으로 반환
queue<shared_ptr<Routedata>> BFSFind();
//각 턴마다 호출, 한 움직임을 출력.
void mazePrint(shared_ptr<Routedata> move, int turn);

//function definitions

void mazeReset() 
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if ((i == 0 || i == 9) || (j == 0 || j == 9))
				maze[i][j] = 1;
			else if ((i == 1 && j == 1) || (i == 8 && j == 8))
				maze[i][j] = 0;
			else
				maze[i][j] = rand() % 2;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			check[i][j] = false;
	check[1][1] = true;
}
void pause()
{
	printf("계속하려면 [Enter]키를 누르세요...");
	getc(stdin);
}
queue<shared_ptr<Routedata>> DFSFind()
{
	stack<shared_ptr<Routedata>> route;
	route.push(INIT_DATA);
	queue<shared_ptr<Routedata>> retval;
	retval.push(INIT_DATA);
	int dir = 0;
	while (!check[8][8])
	{
		for (; dir < 8; dir++)
			if (check[route.top()->row + movetype[dir].row][route.top()->col + movetype[dir].col] == false &&
			 maze[route.top()->row + movetype[dir].row][route.top()->col + movetype[dir].col] == 0) 
			{
				shared_ptr<Routedata> tempRoute = make_shared<Routedata>(*route.top());
				tempRoute->row += movetype[dir].row;
				tempRoute->col += movetype[dir].col;
				tempRoute->dir = dir;
				check[tempRoute->row][tempRoute->col] = true;
				route.push(tempRoute);
				retval.push(tempRoute);
				dir = 0;
				break;
			}
		if(dir == 8)
		{
			if(route.top() == INIT_DATA)
			{
				mazeReset();
				while(!retval.empty())
					retval.pop();
				retval.push(INIT_DATA);
				dir = 0;
				continue;
			}
			shared_ptr<Routedata> tempRoute1 = route.top();
			route.pop();
			shared_ptr<Routedata> tempRoute2 = make_shared<Routedata>(*route.top());
			if(tempRoute2->dir >= 4)
				tempRoute2->dir -= 4;
			else
				tempRoute2->dir += 4;
			retval.push(tempRoute2);
			dir = tempRoute1->dir;
		}
	}
	return retval;
}
void checkMaze() 
{
	printf("\n\n");
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
			if ((i == 1 && j == 1) || (i == 8 && j == 8))
				printf(" #");
			else if (check[i][j] == true)
				printf(" @");
			else
				printf("%s", maze[i][j] ? " ◆" : " 0");
		printf("\n");
	}
	printf("\n\n");
}
//각 턴마다 호출, 한 움직임을 출력.
void mazePrint(shared_ptr<Routedata> move, int turn)
{
	printf("Turn %d : (%d, %d, ", turn, move->row, move->col);
	switch(move->dir)
	{
		case 0:
		printf("N");break;
		case 1:
		printf("NE");break;
		case 2:
		printf("E");break;
		case 3:
		printf("SE");break;
		case 4:
		printf("S");break;
		case 5:
		printf("SW"); break;
		case 6:
		printf("W");break;
		case 7:
		printf("NW");break;
	}
	printf(")\n\n");
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
			if (move->row == i && move->col == j)
				printf(" *");
			else if ((i == 1 && j == 1) || (i == 8 && j == 8))
				printf(" #");
			else
				printf("%s", maze[i][j] ? " ◆" : " 0");
		printf("\n");
	}
	printf("\n\n");
}
void mazePrint()
{
	printf("\n\n");
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
			if (i == 1 && j == 1)
				printf(" *");
			else if (i == 8 && j == 8)
				printf(" #");
			else
				printf("%s", maze[i][j] ? " ◆" : " 0");
		printf("\n");
	}
	printf("\n\n");
}

//main
int main()
{
	mazeReset();
	cout << "미로찾기 프로그램입니다. 1: DFS찾기, 2: BFS찾기(미구현), 0: 종료" << endl;
	cout << "선택: ";
	int sw = 0;
	cin >> sw;
	switch(sw)
	{
		case 1:
			cout << "DFS 찾기를 수행합니다." << endl;
			break;
		case 2:
			cout << "현재 미구현된 방식입니다." << endl;
		default:
			cout << "종료합니다..." << endl << endl;
			return 0;
	}
	queue<shared_ptr<Routedata>> route = DFSFind();
	mazePrint();
	printf("한 턴씩 표시하시겠습니까?(Y | N): ");
	char check = 'N';
	cin >> check;
	bool isOneByOne = (check == 'Y' || check == 'y')? true : false;
	int turn = 0;
	while(!route.empty())
	{
		mazePrint(route.front(), turn);
		turn++;
		route.pop();
		if(isOneByOne)
			pause();
	}
	checkMaze();
	return 0;
}
