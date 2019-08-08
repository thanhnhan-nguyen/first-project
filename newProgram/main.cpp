#include <iostream>
#include <windows.h>
#include <winbgim.h>
using namespace std;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

void cell(int x, int y, int size, int shrink)
{
	int start_X = x * size + shrink;
	int start_Y = y * size + shrink;
	int end_X = x * size + size - shrink;
	int end_Y = y * size + size - shrink;
	rectangle(start_X, start_Y, end_X, end_Y);
}

void fillCell(int x, int y, int size, int shrink)
{
	int start_X = x * size + shrink;
	int start_Y = y * size + shrink;
	int end_X = x * size + size - shrink;
	int end_Y = y * size + size - shrink;
	bar(start_X, start_Y, end_X, end_Y);
}

void drawArrow(int x, int y, string direct, int size)
{
	int imageArrow[5][5] = 
	{
		{0,0,11,0,0},
		{0,11,3,11,0},
		{11,3,9,3,11},
		{0,0,9,0,0},
		{0,0,1,0,0}
	};
	
	for (int i=0; i<5; i++)
	for (int j=0; j<5; j++)
	{
		if (direct=="right")setcolor(imageArrow[4-i][j]);
		if (direct=="left")setcolor(imageArrow[i][4-j]);
		if (direct=="down")setcolor(imageArrow[4-j][4-i]);
		if (direct=="up")setcolor(imageArrow[j][i]);
		cell(i + x * 5,j + y * 5, size, 1);
	}
}

int main()
{
	struct Image
	{	
		int size;
		string directArrow;
	} image;
	
	struct Control
	{
		int x;
		int y;
		string direct;
	}controlCursor, cursorAfterMove, listOfMoves[100] = {0};
	
	int arrMap[5][5] = {	
	{0,0,0,0,0},
	{1,0,0,1,2},
	{0,0,0,0,1},
	{0,0,0,0,0},
	{0,0,0,0,0}
	};
	
	int lengMap = 5;
	int widthMap = 5;
	int numberOfStep = 0;
	
	image.size = 5;
	controlCursor.direct = "up";
	controlCursor.x = 4;
	controlCursor.y = 1	;
	
	listOfMoves[0].x = controlCursor.x;
	listOfMoves[0].y = controlCursor.y;
	
	initwindow(300, 300);
	
	while(1)
	{
		system("cls");
		
		int direct_x = 0;
		int direct_y = 0;
		
		if (GetAsyncKeyState(VK_RIGHT))
		{
			controlCursor.direct = "right";
			direct_x = 1;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			controlCursor.direct = "left";
			direct_x = -1;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			controlCursor.direct = "down";
			direct_y = 1;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			controlCursor.direct = "up";
			direct_y = -1;
		}
		
		cursorAfterMove.x = controlCursor.x + direct_x;
		cursorAfterMove.y = controlCursor.y + direct_y;
		
		if (arrMap[cursorAfterMove.y][cursorAfterMove.x] == 0)
		{
			arrMap[cursorAfterMove.y][cursorAfterMove.x] = 2;
			numberOfStep++;
			listOfMoves[numberOfStep].x = cursorAfterMove.x;
			listOfMoves[numberOfStep].y = cursorAfterMove.y;
			controlCursor.x = cursorAfterMove.x;
			controlCursor.y = cursorAfterMove.y;
		}
		
		for (int i = 0; i < numberOfStep; i++)
		if (cursorAfterMove.x == listOfMoves[i].x)
		if (cursorAfterMove.y == listOfMoves[i].y)
		{	
			for (int j = numberOfStep; j > i; j--)
			{
				arrMap[listOfMoves[j].y][listOfMoves[j].x] = 0;
				listOfMoves[j].x = 0;
				listOfMoves[j].y = 0;
			}
			numberOfStep = i;	
			controlCursor.x += direct_x;
			controlCursor.y += direct_y;
			break;
		}
		
		bool win = true;
		
		for (int i = 0; i < lengMap; i++)
		for (int j = 0; j < widthMap; j++)
		if (arrMap[j][i] == 0) win = false;
		
		for (int i = 0; i < lengMap; i++)
		for (int j = 0; j < widthMap; j++)
		{
			gotoxy(i * 2, j);
			cout << arrMap[j][i];
		}
		
		drawArrow(controlCursor.x, controlCursor.y, controlCursor.direct, image.size);
		
		for (int i = 0; i < lengMap; i++)
		for (int j = 0; j < widthMap; j++)
		{
			setcolor(arrMap[j][i]);
			cell(i,j,image.size*5, 1);
		}
		
		for (int i = 0; i < lengMap; i++)
		for (int j = 0; j < widthMap; j++)
		if (arrMap[j][i]==0)
		{
			setfillstyle(1,0);
			fillCell(i,j,image.size*5, 1);
		}
		
		gotoxy(controlCursor.x*2, controlCursor.y);
		cout << "[]";
		
		gotoxy(1,15);
		
		if (win) break;
		
		Sleep(100);
		getch();
	}
}
