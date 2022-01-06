#include<graphics.h>
#include<conio.h>
#include"Statistic.h"
#include<stdio.h>
#include"functions.h"


int main(void)
{
	InitEvironment();				//320 * 400 
	while (true)
	{
		InitGame();      
		Sleep(500);
		while (!game_over)
		{
			InitBlocks();
			while (!game_con)
			{
				BeginBatchDraw();
				DrawEnvironment();
				DrawMp();
				DrawBlocksNow();
				DrawBlocksNext();
				EndBatchDraw();
				Cmd cmd = getCmd();
				transCmd(cmd);
			}
		}
		swprintf(outputs, 49, L"Game Over!\nYour Score: %d\nOne More Game?", score * 10);
		if (MessageBox(GetHWnd(), outputs, L"One More Game?", MB_ICONQUESTION | MB_YESNO) == IDNO ) 
		{
			break;
		}
	}
	closegraph();
	return 0;
}
