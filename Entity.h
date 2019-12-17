#pragma once
#define SCALE	(SCREENX / MAPX)
#define HSCALE	(SCALE/2)


#define EYEY	2
#define EYEL	2
#define EYER	4

typedef enum{DIR_U=0, DIR_R, DIR_D, DIR_L}Direction;

#include "Player.h"
#include "Ghost.h"

char whatAt(const uint x, const uint y)
{
	return blocks[STM(y)][STM(x)];
}

void removeAt(const uint x, const uint y)
{
	blocks[STM(y)][STM(x)] = ' ';
}

void movePlayer(void)
{
	player.power -= player.power>0;
	player.lastx = player.x;
	player.lasty = player.y;
	uint newx = player.x;
	uint newy = player.y;
	switch (player.facing) {
		case DIR_R:
			newx+=player.speed;
			break;
		case DIR_L:
			newx-=player.speed;
			break;
		case DIR_U:
			newy-=player.speed;
			break;
		case DIR_D:
			newy+=player.speed;
			break;
	}
	switch (whatAt(newx,newy)) {
		default:
		case '#':	// Wall
			return;
			break;
		case '.':	// Dot
			removeAt(newx,newy);
			player.dots++;
			break;
		case '@':	// Power Dot
			removeAt(newx,newy);
			player.dots++;
			player.power = 100;
			break;
		case '0':	// Warp
			player.x = player.x == 0 ? MTS(MAPX-1) : 0;
			break;
		case ' ':	// Empty
			break;
	}
	player.x = newx;
	player.y = newy;
}

void moveGhosts(void)
{

}
