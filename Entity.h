#pragma once
#define SCALE	(SCREENX / MAPX)
#define HSCALE	(SCALE/2)


#define EYEY	2
#define EYEL	2
#define EYER	4

typedef enum{DIR_U=0, DIR_R, DIR_D, DIR_L}Direction;

#include "Player.h"
#include "Ghost.h"

const bool fillMask[SCALE][SCALE] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1}
};

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
			if(newx==0 && player.facing==DIR_L){
				newx = MTS(MAPX-1);
				break;
			}
			if(newx==MTS(MAPX-1) && player.facing==DIR_R){
				newx = 0;
				break;
			}
		default:
		case ' ':	// Empty
			break;
	}
	player.x = newx;
	player.y = newy;
}

void moveGhosts(void)
{
	for(uint i = 0; i < GHOSTSNUM; i++){
		ghosts[i].lastx = ghosts[i].x;
		ghosts[i].lasty = ghosts[i].y;
		uint newx = ghosts[i].x;
		uint newy = ghosts[i].y;
		switch (ghosts[i].facing) {
			case DIR_R:
				newx+=ghosts[i].speed;
				break;
			case DIR_L:
				newx-=ghosts[i].speed;
				break;
			case DIR_U:
				newy-=ghosts[i].speed;
				break;
			case DIR_D:
				newy+=ghosts[i].speed;
				break;
		}
		switch (whatAt(newx,newy)) {
			case '#':	// Wall
				return;
				break;
			case '0':	// Warp
				if(newx==0 && ghosts[i].facing==DIR_L){
					newx = MTS(MAPX-1);
					break;
				}
				if(newx==MTS(MAPX-1) && ghosts[i].facing==DIR_R){
					newx = 0;
					break;
				}
				break;
			default:
			case ' ':	// Empty
				break;
		}
		ghosts[i].x = newx;
		ghosts[i].y = newy;
	}
}
