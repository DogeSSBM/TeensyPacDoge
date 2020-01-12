#pragma once

typedef struct{
	uint x, lastx;
	uint y, lasty;
	uint lives;
	uint speed;
	Direction facing;
	uint power;
	uint dots;
}Player;

Player player={
	MTS(14),
	MTS(0),
	MTS(17),
	MTS(0),
	3,
	1,
	DIR_L,
	0,
	0
};

bool playerMask[SCALE][SCALE] = {
	{0,0,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{0,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,0,0}
};
