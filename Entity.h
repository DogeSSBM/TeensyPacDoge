#pragma once
extern "C"{

typedef enum{DIR_U=0, DIR_R, DIR_D, DIR_L}Direction;

typedef union{
	bool arr[4];
	struct{
		bool dirU;
		bool dirR;
		bool dirD;
		bool dirL;
	};
	struct{
		bool dirD;
		bool dirL;
		bool dirU;
		bool dirR;
	}inverse;
}AdjDir;

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

char whatsAtM(const uint x, const uint y)
{
	return blocks[x][y];
}

char whatsAtS(const uint x, const uint y)
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

bool checkBounds(const uint x, const uint y)
{
	bool ret =
	 	traversable(whatsAtS(x,y)) &&
		traversable(whatsAtS(x+SCALE-1, y)) &&

		traversable(whatsAtS(x,y+SCALE-1)) &&
		traversable(whatsAtS(x+SCALE-1, y+SCALE-1));
	//setColor(ret?GREEN:RED);
	return ret;
}

AdjDir validPlayerMoves(void)
{
	AdjDir ret = {0};

	ret.dirU = checkBounds(player.x,player.y-1);
	// drawLine(
		// player.x+HSCALE,player.y-HSCALE,
		// player.x+HSCALE,player.y);

	ret.dirR = checkBounds(player.x+1,player.y);
	// drawLine(
		// player.x+SCALE,player.y+HSCALE,
		// player.x+SCALE+HSCALE,player.y+HSCALE);

	ret.dirD = checkBounds(player.x,player.y+1);
	// drawLine(
		// player.x+HSCALE,player.y+SCALE,
		// player.x+HSCALE,player.y+SCALE+HSCALE);

	ret.dirL = checkBounds(player.x-1,player.y);
	// drawLine(
		// player.x-HSCALE,player.y+HSCALE,
		// player.x,player.y+HSCALE);

	return ret;
}

void movePlayer(void)
{
	player.power -= player.power>0;
	player.lastx = player.x;
	player.lasty = player.y;

	AdjDir validAdj = validPlayerMoves();
	AdjDir tryAdj = {0};
	tryAdj.dirU = btnState.btnU && !btnState.inverse.btnU;
	tryAdj.dirR = btnState.btnR && !btnState.inverse.btnR;
	tryAdj.dirD = btnState.btnD && !btnState.inverse.btnD;
	tryAdj.dirL = btnState.btnL && !btnState.inverse.btnL;

	if(UD(player.facing)){
		if(tryAdj.dirL && validAdj.dirL){
			player.facing = DIR_L;
		}else if(tryAdj.dirR && validAdj.dirR){
			player.facing = DIR_R;
		}else{
			if(player.facing == DIR_U &&
				tryAdj.dirD && validAdj.dirD){
				player.facing = DIR_D;
			}else if(player.facing == DIR_D &&
				tryAdj.dirU && validAdj.dirU){
				player.facing = DIR_U;
			}
		}
	}else{
		if(tryAdj.dirU && validAdj.dirU){
			player.facing = DIR_U;
		}else if(tryAdj.dirD && validAdj.dirD){
			player.facing = DIR_D;
		}else{
			if(player.facing == DIR_L &&
				tryAdj.dirR && validAdj.dirR){
				player.facing = DIR_R;
			}else if(player.facing == DIR_R &&
				tryAdj.dirL && validAdj.dirL){
				player.facing = DIR_L;
			}
		}
	}

	if(validAdj.arr[player.facing]){
		switch(player.facing){
			case DIR_U:
				player.y--;
				break;
			case DIR_R:
				player.x++;
				break;
			case DIR_D:
				player.y++;
				break;
			case DIR_L:
				player.x--;
				break;
		}
	}
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
		switch (whatsAtS(newx,newy)) {
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
