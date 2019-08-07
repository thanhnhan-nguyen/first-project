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
	int lengMap = 5;
	int highMap = 3;
	
	struct Ctrl
	{
		int x, y;
	} ctrl, before, after, listGo[20];
	
	int arrMap[3][5] = {
	{0,0,0,0,0},
	{0,0,0,1,2},
	{0,0,0,0,0}
	};
	
	ctrl.x = 4;
	ctrl.y = 1;
	int countGo = 0;
	listGo[0].x = ctrl.x;
	listGo[0].y = ctrl.y;
	
	while(1)
	{	
		
		system("cls");
		
		int dx = 0;
		int dy = 0;
		
		if (GetAsyncKeyState(VK_RIGHT)) dx = 1;
		if (GetAsyncKeyState(VK_LEFT)) dx = -1;
		if (GetAsyncKeyState(VK_DOWN)) dy = 1;
		if (GetAsyncKeyState(VK_UP)) dy = -1;
		
		if (arrMap[ctrl.y+dy][ctrl.x+dx] == 0)
		{
			countGo++;
			listGo[countGo].x = ctrl.x + dx;
			listGo[countGo].y = ctrl.y + dy;
			ctrl.x += dx;
			ctrl.y += dy;
			arrMap[ctrl.y][ctrl.x] = 2;
		}
		
		bool testGo = 0;
		for (int i = 0; i < countGo; i++)
		if (ctrl.x + dx == listGo[i].x)
		if (ctrl.y + dy == listGo[i].y)
		{	
			for (int j = countGo; j > i; j--)
			{
				arrMap[listGo[j].y][listGo[j].x] = 0;
				listGo[j].x = 0;
				listGo[j].y = 0;
			}
			countGo = i;	
			ctrl.x += dx;
			ctrl.y += dy;
			break;
		}
		
		for (int i=0; i<countGo; i++)
		{
			gotoxy(20, i);
			cout << listGo[i].x << " " << listGo[i].y;
		}
		
		bool test = 1;
		for (int i = 0; i < lengMap; i++)
		for (int j = 0; j < highMap; j++)
		if (arrMap[j][i] == 0) test = 0;
		
		gotoxy(1,15);
		cout << "test = " << test ;
		
		for (int i=0; i<lengMap; i++)
		for (int j=0; j<highMap; j++)
		{
			gotoxy(i * 2, j);
			cout << arrMap[j][i];
		}
		
		gotoxy(ctrl.x*2, ctrl.y);
		cout << "[]";
		
		gotoxy(1,15);
		Sleep(100);
	}
	return 0;
}
