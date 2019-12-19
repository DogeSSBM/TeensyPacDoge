#pragma once
#define SCALE	(SCREENX / MAPX)
#define HSCALE	(SCALE/2)


#define EYEY	2
#define EYEL	2
#define EYER	4

typedef enum{DIR_U=0, DIR_D, DIR_L, DIR_R}Direction;

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

/* PSX = Player screen tile X, PTX = Player tile X */
void msg(const uint Psx, const uint Psy, const uint Ptx, const uint Pty,
		const uint Ntx, const uint Nty, const char nt)
{
	setTextSize(1);
	setClearLine(numLines()-4);
	screen.print("Psx: ");	screen.println(Psx);
	screen.print("Psy: ");	screen.println(Psy);
	screen.print("Ptx: ");	screen.println(Ptx);
	screen.print("Pty: ");	screen.println(Pty);

	setLine(numLines()-4);
	setCursorX(HSCREENX);
	screen.print("Ntx: ");	screen.println(Ntx);
	setCursorX(HSCREENX);
	screen.print("Nty: ");	screen.println(Nty);
	setCursorX(HSCREENX);
	screen.print("nt:  ");	screen.println(nt);
}

void movePlayer(void)
{
	player.power -= player.power>0;
	player.lastx = player.x;
	player.lasty = player.y;

	uint tilex = STM(player.x+HSCALE);
	uint tiley = STM(player.y+HSCALE);

	uint nextTilex = tilex;
	uint nextTiley = tiley;

	char nextTile = blocks[tiley][tilex];

	setColor(GREEN);
	fillSquare(MTS(tilex), MTS(tiley), SCALE);

	switch (player.facing) {
		case DIR_R:
			player.x+=player.speed;
			nextTilex+=player.speed;
			break;
		case DIR_L:
			player.x-=player.speed;
			nextTilex-=player.speed;
			break;
		case DIR_U:
			player.y-=player.speed;
			nextTiley-=player.speed;
			break;
		case DIR_D:
			player.y+=player.speed;
			nextTiley+=player.speed;
			break;
	}

	setColor(RED);
	fillSquare(MTS(nextTilex), MTS(nextTiley), SCALE);
	msg(player.x, player.y, tilex, tiley, nextTilex, nextTiley, nextTile);
}

// void movePlayer(void)
// {
// 	player.power -= player.power>0;
// 	player.lastx = player.x;
// 	player.lasty = player.y;
// 	uint newx = player.x;
// 	uint newy = player.y;
// 	switch (player.facing) {
// 		case DIR_R:
// 			newx+=player.speed;
// 			break;
// 		case DIR_L:
// 			newx-=player.speed;
// 			break;
// 		case DIR_U:
// 			newy-=player.speed;
// 			break;
// 		case DIR_D:
// 			newy+=player.speed;
// 			break;
// 	}
// 	setColor(RED);
// 	drawSquare(MTS(STM(newx)), MTS(STM(newy)), SCALE);
// 	switch (whatAt(newx+HSCALE,newy+HSCALE)) {
// 		case '#':	// Wall
// 			return;
// 			break;
// 		case '.':	// Dot
// 			removeAt(newx,newy);
// 			player.dots++;
// 			break;
// 		case '@':	// Power Dot
// 			removeAt(newx,newy);
// 			player.dots++;
// 			player.power = 100;
// 			break;
// 		case '0':	// Warp
// 			if(newx==0 && player.facing==DIR_L){
// 				newx = MTS(MAPX-1);
// 				break;
// 			}
// 			if(newx==MTS(MAPX-1) && player.facing==DIR_R){
// 				newx = 0;
// 				break;
// 			}
// 		default:
// 		case ' ':	// Empty
// 			break;
// 	}
// 	player.x = newx;
// 	player.y = newy;
// }

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
