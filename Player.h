#pragma once

typedef struct{
	uint x, lastx;
	uint y, lasty;
	uint lives;
	uint speed;
	Direction facing;
	uint power;
	uint dots;
	// bool mask[SCALE][SCALE];
}Player;

Player player={
	MTS(14),
	MTS(14),
	MTS(17),
	MTS(17),
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
