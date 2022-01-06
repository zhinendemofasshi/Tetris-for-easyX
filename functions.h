#pragma once
#include<graphics.h>
#include "Statistic.h"
#include<time.h>
#include<stdlib.h>

void InitEvironment();
void InitGame();
void DrawBlock(int x, int y);
void InitBlocks();
void DrawBlocksNow();
void DrawBlocksNext();
void DrawEnvironment();
void DrawMp();
void MoveDown();
void MoveLeft();
void MoveRight();
void Rotate();
void Pause();
void RecordBlocksNow();
void ClearBlocks();
bool IsGameOver();
void transCmd(Cmd cmd);
bool Check(int mp_x, int mp_y, int shape);

Cmd getCmd();

void InitEvironment()
{
	initgraph(320, 400);
	HWND window = GetHWnd();
	SetWindowText(window, _T("Tetris"));
	SetWindowPos(window, HWND_TOP, 700, 20, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);

	srand(time(NULL));
}
void DrawEnvironment()
{
	setfillcolor(BLACK);
	fillrectangle(0, 0, 200, 400);
	fillrectangle(200, 0, 320, 100);
	fillrectangle(200, 100, 320, 400);
	settextstyle(20, 0, _T("Consolas"));
	swprintf(scoreputs, 29, L"Score: %d", score * 10);
	outtextxy(205, 125, scoreputs);

	settextstyle(32, 0, _T("Consolas"));
	outtextxy(220, 260, _T("HELP:"));

	settextstyle(16, 0, _T("Consolas"));
	outtextxy(205, 300, _T("¡ü:rotate"));
	outtextxy(205, 320, _T("¡ý:speed up"));
	outtextxy(205, 340, _T("¡û:left"));
	outtextxy(205, 360, _T("¡ú:right"));
	outtextxy(205, 380, _T("Space:suspend"));
}
void DrawBlock(int x, int y)
{
	setlinecolor(WHITE);
	setfillcolor(RED);
	
	fillrectangle(x, y, x+20, y+20);

}
void DrawBlocksNow()
{
	DrawBlock((now_mp_x + Blocks[nowtype].dir[nowshape][0][0]) * 20, (now_mp_y + Blocks[nowtype].dir[nowshape][0][1]) * 20);
	DrawBlock((now_mp_x + Blocks[nowtype].dir[nowshape][1][0]) * 20, (now_mp_y + Blocks[nowtype].dir[nowshape][1][1]) * 20);
	DrawBlock((now_mp_x + Blocks[nowtype].dir[nowshape][2][0]) * 20, (now_mp_y + Blocks[nowtype].dir[nowshape][2][1]) * 20);
	DrawBlock((now_mp_x + Blocks[nowtype].dir[nowshape][3][0]) * 20, (now_mp_y + Blocks[nowtype].dir[nowshape][3][1]) * 20);
}
void DrawBlocksNext()
{
	int prev_x = 235, prev_y = 65;
	DrawBlock(prev_x + Blocks[nexttype].dir[nextshape][0][0] * 20, prev_y + Blocks[nexttype].dir[nextshape][0][1] * 20);
	DrawBlock(prev_x + Blocks[nexttype].dir[nextshape][1][0] * 20, prev_y + Blocks[nexttype].dir[nextshape][1][1] * 20);
	DrawBlock(prev_x + Blocks[nexttype].dir[nextshape][2][0] * 20, prev_y + Blocks[nexttype].dir[nextshape][2][1] * 20);
	DrawBlock(prev_x + Blocks[nexttype].dir[nextshape][3][0] * 20, prev_y + Blocks[nexttype].dir[nextshape][3][1] * 20);
}
void DrawMp()
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (mp[i][j])
			{
				DrawBlock(i * 20, j * 20);
			}
		}
	}
}
void MoveDown()
{
	if (Check(now_mp_x, now_mp_y+1, nowshape))
	{
		++now_mp_y;
		return;
	}

	game_con = 1;
	RecordBlocksNow();
	ClearBlocks();
	if (IsGameOver())
	{
		game_over = 1;
	}
}
void MoveLeft()
{
	if (Check(now_mp_x-1, now_mp_y, nowshape))
	{
		--now_mp_x;
	}
}
void MoveRight()
{
	if (Check(now_mp_x+1, now_mp_y, nowshape))
	{
		++now_mp_x;
	}
}
void InitGame()
{
	memset(mp, 0, sizeof(mp));
	now_time = GetTickCount();
	nextshape = rand() % 4;
	nexttype = rand() % 7;               //Tetris has 7 kinds of types of blocks. Every block has 4 kinds of shapes
	game_over = 0;
	score = 0;
}
void InitBlocks()
{
	game_con = 0;

	now_mp_x = 4;
	now_mp_y = -1;

	nowshape = nextshape;
	nowtype = nexttype;

	nextshape = rand() % 4;
	nexttype = rand() % 7;
}

Cmd getCmd()
{
	while (true)
	{
		DWORD temp_time = GetTickCount();
		if (temp_time - now_time >= 1000)
		{
			now_time = temp_time;
			return Cmd_down;
		}
		if (_kbhit())
		{
			switch (_getch())
			{
			case 72:
				return Cmd_rotate;
			case 75:
				return Cmd_left;
			case 77:
				return Cmd_right;
			case 80:
				return Cmd_down;
			case 32:
				return Cmd_space;		
			}
		}
		Sleep(20);
	}
}
void Rotate()
{
	for (size_t i = 1; i <= 3; i++)
	{
		if (Check(now_mp_x, now_mp_y, (nowshape+i) % 4))
		{
			nowshape = (nowshape + i) % 4;
			break;
		}
	}
}
void Pause()
{
	while(true)
	{
		if(_getch() == 32)
			break;
	}
}
void transCmd(Cmd cmd)
{
	switch (cmd)
	{
	case Cmd_rotate:
		Rotate();
		break;
	case Cmd_left:
		MoveLeft();
		break;
	case Cmd_right:
		MoveRight();
		break;
	case Cmd_down:
		MoveDown();
		break;
	}
}
bool Check(int mp_x, int mp_y, int shape)
{
	int b_x[4], b_y[4];                          //the coordinate of the blocks where they should be
	for (int i = 0; i < 4; i++)
	{
		b_x[i] = mp_x + Blocks[nowtype].dir[shape][i][0];
		b_y[i] = mp_y + Blocks[nowtype].dir[shape][i][1];
	}
	for (int i = 0; i < 4; i++)
	{
		if (b_x[i] < 0 || b_x[i] > 9 || b_y[i] > 19)                // 10 * 20 
		{
			return false;
		}
		if (b_y[i] < 0)
		{
			continue;
		}
		if (mp[b_x[i]][b_y[i]])           // if the coordinate has been occupied
		{
			return false;
		}
	}
	return true;
}
void RecordBlocksNow()
{
	int b_x[4], b_y[4];
	for (int i = 0; i < 4; ++i)
	{
		b_x[i] = now_mp_x + Blocks[nowtype].dir[nowshape][i][0];
		b_y[i] = now_mp_y + Blocks[nowtype].dir[nowshape][i][1];
	}
	for (int i = 0; i < 4; ++i)
	{
		if (b_y[i] >= 0)
		{
			mp[b_x[i]][b_y[i]] = 1;
		}
	}
}
void ClearBlocks()
{
	memset(temp_mp, 0, sizeof(temp_mp));
	int cur_j = 19;
	for (int j = 19; j >= 0; j--)
	{
		int cnt = 0;
		for (int i = 0; i < 10; ++i)
		{
			if (mp[i][j])
			{
				++cnt;
			}
		}
		if (cnt != 10)
		{
			for (int i = 0; i < 10; i++)
			{
				temp_mp[i][cur_j] = mp[i][j];
			}
			--cur_j;
		}
		else
			score++;
	}
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			mp[i][j] = temp_mp[i][j];
		}
	}
}

bool IsGameOver()
{
	for (int i = 0; i < 10; i++)
	{
		if (mp[i][0])
		{
			return true;
		}
	}
	return false;
}
