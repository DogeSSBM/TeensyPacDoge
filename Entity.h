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

}

void outlineOffset(int xoff, int yoff)
{
	xoff = player.x+xoff*SCALE;
	yoff = player.y+yoff*SCALE;
	if(ALIGNED(xoff) || ALIGNED(yoff)){
	setColor(traversable(whatAt(xoff,yoff))?GREEN:RED);
	drawLine(player.x+HSCALE,player.y+HSCALE,xoff+HSCALE,yoff+HSCALE);
	}
}

void movePlayer(void)
{
	player.power -= player.power>0;

	outlineOffset(0,1);
	outlineOffset(1,0);
	outlineOffset(0,-1);
	outlineOffset(-1,0);

	volatile bool* dirBtn[] = {
		&btnState.btnU,
		&btnState.btnR,
		&btnState.btnD,
		&btnState.btnL
	};

	volatile bool* idirBtn[] = {
		&btnState.inverse.btnU,
		&btnState.inverse.btnR,
		&btnState.inverse.btnD,
		&btnState.inverse.btnL
	};

	if(*idirBtn[player.facing]&& !(*dirBtn[player.facing]))
		player.facing = INVERT(player.facing);
	else if(*idirBtn[(player.facing+1)%4]&& !(*dirBtn[(player.facing+1)%4]))
		player.facing = INVERT((player.facing+1)%4);
	else if(*idirBtn[(player.facing+3)%4]&& !(*dirBtn[(player.facing+3)%4]))
		player.facing = INVERT((player.facing+3)%4);
	switch (player.facing){
		case DIR_R:
			player.x+=1;
			break;
		case DIR_L:
			player.x-=1;
			break;
		case DIR_D:
			player.y+=1;
			break;
		case DIR_U:
			player.y-=1;
			break;
	}

	player.lastx = player.x;
	player.lasty = player.y;
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
