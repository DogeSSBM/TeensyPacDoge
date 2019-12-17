#pragma once

#define GHOSTSNUM 4

typedef struct{
	uint x, lastx;
	uint y, lasty;
	uint speed;
	Direction facing;
	Color color;
}Ghost;

Ghost ghosts[GHOSTSNUM] = {
	{MTS(12), MTS(12), 0, 0, 1, DIR_L, CYAN},
	{MTS(13), MTS(13), 0, 0, 1, DIR_R, RED},
	{MTS(14), MTS(14), 0, 0, 1, DIR_U, PINK},
	{MTS(15), MTS(15), 0, 0, 1, DIR_D, ORANGE}
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
