#pragma once

typedef enum{DIR_U, DIR_R, DIR_D, DIR_L}Direction;

typedef struct{
	uint x;
	uint y;
	uint lives;
	float speed;
	Direction facing;
	bool power;
}PacDoge;

typedef struct{
	uint x;
	uint y;
	float speed;
	Direction facing;
	Color color;
}Ghost;
