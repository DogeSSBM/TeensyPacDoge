#pragma once

#define GHOSTSNUM 4

typedef struct{
	uint x, lastx;
	uint y, lasty;
	uint speed;
	Direction facing;
	Direction turn;
	Color color;
}Ghost;

Ghost ghosts[GHOSTSNUM] = {
	{MTS(12), 0, MTS(11), 0, 1, DIR_L, DIR_D, CYAN},
	{MTS(13), 0, MTS(11), 0, 1, DIR_L, DIR_U, RED},
	{MTS(14), 0, MTS(11), 0, 1, DIR_R, DIR_U, PINK},
	{MTS(15), 0, MTS(11), 0, 1, DIR_R, DIR_D, ORANGE}
};

bool ghostMask[SCALE][SCALE] = {
	{0,0,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,0},
	{1,1,0,1,1,0,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,0,0,1,1,0,0}
};
