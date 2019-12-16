#pragma once

#define GHOSTSNUM 4

typedef enum{DIR_U, DIR_R, DIR_D, DIR_L}Direction;

typedef struct{
	uint x;
	uint y;
	int offset;
	uint lives;
	uint speed;
	Direction facing;
	bool power;
}Player;

Player player={
	14,
	17,
	0,
	3,
	1,
	DIR_L,
	false
};

typedef struct{
	uint x;
	uint y;
	int offset;
	float speed;
	Direction facing;
	Color color;
}Ghost;

Ghost ghosts[GHOSTSNUM] = {
	{12, 11, 0, 1, DIR_L, BLUE},
	{13, 11, 0, 1, DIR_L, RED},
	{14, 11, 0, 1, DIR_R, PINK},
	{15, 11, 0, 1, DIR_R, ORANGE}
};

typedef enum{E_MOVE, E_COLLIDE, E_EXIT}EventType;
