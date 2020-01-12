#pragma once
extern "C"{

typedef enum{DIR_U=0, DIR_R, DIR_D, DIR_L}Direction;
#define INVERT(d)	((Direction)((d+2)%4))
#define UD(d)	(~(d)&1)
#define LR(d)	( (d)&1)
#define ALIGNED(s)(!(s%SCALE))

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

bool traversable(const char t)
{
	return t!='#' && t!='g';
}

void removeAt(const uint x, const uint y)
{
	blocks[STM(y)][STM(x)] = ' ';
}

void playerMsg(const uint x, const uint y, const uint nextx, const uint nexty)
{
	setTextSize(1);
	for(uint i = 1; i < 6; i++)
		setClearLine(numLines()-i);

	setLine(numLines()-6);
	screen.println("Player");
	screen.print("x: ");		screen.println(x);
	screen.print("y: ");		screen.println(y);
	screen.print("next x: ");	screen.println(nextx);
	screen.print("next y: ");	screen.println(nexty);
}

void tileMsg(const uint x, const uint y, const uint nextx, const uint nexty)
{
	setLine(numLines()-6);
	setCursorX(HSCREENX);
	screen.println("Tile");
	setCursorX(HSCREENX);
	screen.print("x: ");		screen.println(x);
	setCursorX(HSCREENX);
	screen.print("y: ");		screen.println(y);
	setCursorX(HSCREENX);
	screen.print("next x: ");	screen.println(nextx);
	setCursorX(HSCREENX);
	screen.print("next y: ");	screen.println(nexty);
}

bool gridAligned(const uint x, const uint y)
{
	return ALIGNED(x) && ALIGNED(y);
}

void turnPlayer(void)
{
	volatile bool* dirBtn[] = {
			&btnState.btnU,
			&btnState.btnR,
			&btnState.btnD,
			&btnState.btnL
		};
	Direction turn = player.facing;

	if(UD(player.facing)){
		if(ALIGNED(player.y)){
		if(btnState.btnL && !btnState.inverse.btnL){
			if(traversable(
				whatAt(STM(player.x)-1, STM(player.y))
			)){
				turn = DIR_L;
			}
		}else if(btnState.btnR && !btnState.inverse.btnR){
			if(traversable(
				whatAt(OSTM(player.x)+1, STM(player.y))
			)){
				turn = DIR_R;
			}
		}
		if(turn == player.facing){
			if(*dirBtn[INVERT(player.facing)] &&
			!(*dirBtn[player.facing])){
				turn = INVERT(turn);
			}
		}
		}
	}

	if(LR(player.facing)){
		if(ALIGNED(player.x)){
		if(btnState.btnU && !btnState.inverse.btnU){
			if(traversable(
				whatAt(STM(player.x), STM(player.y)-1)
			)){
				turn = DIR_U;
			}
		}else if(btnState.btnD && !btnState.inverse.btnD){
			if(traversable(
				whatAt(STM(player.x), OSTM(player.y)+1)
			)){
				turn = DIR_D;
			}
		}
		if(turn == player.facing){
			if(*dirBtn[INVERT(player.facing)] &&
			!(*dirBtn[player.facing])){
				turn = INVERT(turn);
			}
		}
		}
	}

	player.facing = turn;
}

void movePlayer(void)
{
	turnPlayer();

	player.power -= player.power>0;
	player.lastx = player.x;
	player.lasty = player.y;

	uint nextPlayerx = player.x;
	uint nextPlayery = player.y;

	uint tilex = player.x;
	uint tiley = player.y;

	uint nextTilex = tilex;
	uint nextTiley = tiley;
	switch (player.facing){
		case DIR_R:
			nextPlayerx+=1;
			nextTilex = OSTM(nextPlayerx);
			nextTiley = STM(nextPlayery);
			break;
		case DIR_L:
			nextPlayerx-=1;
			nextTilex = STM(nextPlayerx);
			nextTiley = STM(nextPlayery);
			break;
		case DIR_U:
			nextPlayery-=1;
			nextTilex = STM(nextPlayerx);
			nextTiley = STM(nextPlayery);
			break;
		case DIR_D:
			nextPlayery+=1;
			nextTilex = STM(nextPlayerx);
			nextTiley = OSTM(nextPlayery);
			break;
	}

	if(traversable(whatAt(nextTilex, nextTiley))){
		player.x = nextPlayerx;
		player.y = nextPlayery;
	}
	// if trying to turn and turnable check potential tile
	// change facing if valid next tile

	// find next x and y
	// find next tile x and y
	// if valid move, update player x and y (warp if necessesarry)
	// check ghost colissions


	playerMsg(player.x, player.y, nextPlayerx, nextPlayery);
	tileMsg(tilex, tiley, nextTilex, nextTiley);
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

}// extern "C"
