#pragma once

#define GHOSTSNUM 4

typedef enum{CHASE, SCATTER, EATEN, FRIGHT}State;

typedef struct{
	uint x, lastx, spawnx;
	uint y, lasty, spawny;
	uint speed;
	Direction facing;
	State state;
	Color color;
}Ghost;

Ghost ghosts[GHOSTSNUM] = {
	{MTS(12), 0, MTS(12), MTS(11), 0, MTS(11), 1, DIR_L, SCATTER, CYAN},
	{MTS(13), 0, MTS(13), MTS(11), 0, MTS(11), 1, DIR_L, SCATTER, RED},
	{MTS(14), 0, MTS(14), MTS(11), 0, MTS(11), 1, DIR_R, SCATTER, PINK},
	{MTS(15), 0, MTS(15), MTS(11), 0, MTS(11), 1, DIR_R, SCATTER, ORANGE}
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
