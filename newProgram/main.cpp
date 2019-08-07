#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}



int main() 
{	
	struct Control_cursor
	{
		int x, y;
	} control_cursor, cursorAfterMove, listOfMoves[100] = {0};
	
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
	
	control_cursor.x = 4;
	control_cursor.y = 1;
	listOfMoves[0].x = control_cursor.x;
	listOfMoves[0].y = control_cursor.y;
	
	while(1)
	{	
		
		system("cls");
		
		int direct_X = 0;
		int direct_Y = 0;
		
		if (GetAsyncKeyState(VK_RIGHT)) direct_X = 1;
		if (GetAsyncKeyState(VK_LEFT)) direct_X = -1;
		if (GetAsyncKeyState(VK_DOWN)) direct_Y = 1;
		if (GetAsyncKeyState(VK_UP)) direct_Y = -1;
		
		cursorAfterMove.x = control_cursor.x + direct_X;
		cursorAfterMove.y = control_cursor.y + direct_Y;
		
		if (arrMap[cursorAfterMove.y][cursorAfterMove.x] == 0)
		{
			arrMap[cursorAfterMove.y][cursorAfterMove.x] = 2;
			numberOfStep++;
			listOfMoves[numberOfStep].x = cursorAfterMove.x;
			listOfMoves[numberOfStep].y = cursorAfterMove.y;
			control_cursor.x = cursorAfterMove.x;
			control_cursor.y = cursorAfterMove.y;
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
			control_cursor.x += direct_X;
			control_cursor.y += direct_Y;
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
		
		gotoxy(control_cursor.x*2, control_cursor.y);
		cout << "[]";
		
		gotoxy(1,15);
		
		if (win) break;
		
		Sleep(100);
	}
	
	system("cls");
	gotoxy(5,5);
	cout << "YOU WIN!";
	
	return 0;
}
