#pragma once
#define BlockWidth 4
#define BlockHeight 4
#define BlockCount 7
#define Graph_Width 20
#define Graph_Height 10
#define UNIT_SIZE 10

int score = 0;
int mp[Graph_Height][Graph_Width];
int temp_mp[Graph_Height][Graph_Width];
int game_con = 0;
int game_over = 0;
int nowtype;
int nowshape;
int nextshape;
int nexttype;
int now_mp_x;
int now_mp_y;
wchar_t scoreputs[30];
wchar_t outputs[50];

DWORD now_time;


struct Block
{
	int dir[BlockHeight][BlockWidth][2];
};
Block Blocks[BlockCount] = {
	{ 0, -2, 0, -1, 0, 0, 1, 0, 0, -1, 1, -1, 2, -1, 0, 0, 0, -2, 1, -2, 1, -1, 1, 0, 0, 0, 1, 0, 2, 0, 2, -1 },       //  L
	{ 0, 0, 1, 0, 1, -1, 1, -2, 0, -1, 0, 0, 1, 0, 2, 0, 0, -2, 0, -1, 0, 0, 1, -2, 0, -1, 1, -1, 2, -1, 2, 0 },       //  L·´
	{ 0, -1, 0, 0, 1, -1, 1, 0, 0, -1, 0, 0, 1, -1, 1, 0, 0, -1, 0, 0, 1, -1, 1, 0, 0, -1, 0, 0, 1, -1, 1, 0 },        //  Ìï
	{ 0, 0, 1, -1, 1, 0, 2, 0, 1, -2, 1, -1, 1, 0, 2, -1, 0, -1, 1, -1, 1, 0, 2, -1, 0, -1, 1, -2, 1, -1, 1, 0 },      //  É½
	{ 0, -3, 0, -2, 0, -1, 0, 0, 0, -3, 1, -3, 2, -3, 3, -3, 0, -3, 0, -2, 0, -1, 0, 0, 0, -3, 1, -3, 2, -3, 3, -3 },  //  ¹÷
	{ 0, -1, 1, -1, 1, 0, 2, 0, 0, -1, 0, 0, 1, -2, 1, -1, 0, -1, 1, -1, 1, 0, 2, 0, 0, -1, 0, 0, 1, -2, 1, -1 },      //  Z
	{ 0, 0, 1, -1, 1, 0, 2, -1, 1, -2, 1, -1, 2, -1, 2, 0, 0, 0, 1, -1, 1, 0, 2, -1, 1, -2, 1, -1, 2, -1, 2, 0 }       //  Z·´
};

enum Cmd
{
	Cmd_rotate,
	Cmd_left,
	Cmd_right,
	Cmd_down,
	Cmd_space,
};

