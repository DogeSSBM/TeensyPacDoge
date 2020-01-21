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

// count number of valid adjacent tiles
#define ADJC(d)	((d.arr[0]) + (d.arr[1]) + (d.arr[2]) + (d.arr[3]))

// evaluates to the opposite direction INVERT(DIR_U) == DIR_D
#define INVERT(d)	((Direction)((d+2)%4))

// true if d is a vertical direction (DIR_U || DIR_D)
#define UD(d)	(~(d)&1)

// true if d is a horizontal direction (DIR_L || DIR_R)
#define LR(d)	( (d)&1)

// true if s is alligned with the map coordanates when scaled down
#define ALIGNED(s)(!(s%SCALE))

// evaluates to the perpendicular direction
// (the direction pointing 90deg clockwise)
#define PERP1(d)	((Direction)((d+1)%4))

// evaluates to the perpendicular direction
// (the direction pointing 90deg counterclockwise)
#define PERP2(d)	((Direction)((d+3)%4))

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

void setAtS(const uint x, const uint y, const char c)
{
	blocks[STM(y)][STM(x)] = c;
}

// returns true if all 4 corners of the screen coordanates
// at index map[x][y] are traversable
bool checkBounds(const uint x, const uint y)
{
	return(
	 	traversable(whatsAtS(x,y)) &&
		traversable(whatsAtS(x+SCALE-1, y)) &&
		traversable(whatsAtS(x,y+SCALE-1)) &&
		traversable(whatsAtS(x+SCALE-1, y+SCALE-1))
	);
}

// check adjacent tile boundaries and return traversability struct
AdjDir getValidAdj(const uint x, const uint y)
{
	AdjDir ret = {
		checkBounds(x,y-1),
		checkBounds(x+1,y),
		checkBounds(x,y+1),
		checkBounds(x-1,y)
	};
	return ret;
}

uint countValidAdj(AdjDir d)
{
	return d.arr[0] + d.arr[1] + d.arr[2] + d.arr[3];
}

void movePlayer(void)
{
	player.power -= player.power>0;
	player.lastx = player.x;
	player.lasty = player.y;

	AdjDir validAdj = getValidAdj(player.x, player.y);

	// check buttons and buffer turns to try
	AdjDir tryAdj = {
		btnState.btnU && !btnState.inverse.btnU,
		btnState.btnR && !btnState.inverse.btnR,
		btnState.btnD && !btnState.inverse.btnD,
		btnState.btnL && !btnState.inverse.btnL
	};

	// turn player if possible
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

	// move player in the direction they are facing if possible
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

void collidePlayer(void)
{
	const uint x = player.x+HSCALE;
	const uint y = player.y+HSCALE;
	switch(whatsAtS(x, y)){
		case '.':
			setAtS(x,y,' ');
			player.dots++;
			break;
		case '@':
			setAtS(x,y,' ');
			player.dots++;
			player.power = 10*FPS;
			break;
		case '0':
			if(player.facing == DIR_R && x > MAPSX/2){
				player.x = SCALE+HSCALE;
			}else if(player.facing == DIR_L && x < MAPSX/2){
				player.x = MAPSX-(SCALE+HSCALE+1);
			}
		default:
		case ' ':
			break;
	}
}

void collideGhosts(void)
{
	for(uint i = 0; i < 4; i++){
		Ghost *g = &ghosts[i];
		const uint x = g->x+HSCALE;
		const uint y = g->y+HSCALE;
		switch(whatsAtS(x, y)){
			case '0':
				if(g->facing == DIR_R && x > MAPSX/2){
					g->x = SCALE+HSCALE;
				}else if(g->facing == DIR_L && x < MAPSX/2){
					g->x = MAPSX-(SCALE+HSCALE+1);
				}
			default:
			case ' ':
				break;
		}
	}
}

Direction randomValidAdjDir(AdjDir d)
{
	Direction ret = (Direction)random(4);
	while(!d.arr[ret = (Direction)random(4)]);
	return ret;
}

void moveGhostsRandom(void)
{
	for(uint i = 0; i < 4; i++){
		Ghost *g = &ghosts[i];
		g->lastx = g->x;
		g->lasty = g->y;
		AdjDir validAdj = getValidAdj(g->x,g->y);
		if(validAdj.arr[PERP1(g->facing)] ||
		validAdj.arr[PERP2(g->facing)] ||
		!validAdj.arr[g->facing]){
			g->facing = randomValidAdjDir(validAdj);
		}
		switch(g->facing){
			case DIR_U:
				g->y--;
				break;
			case DIR_R:
				g->x++;
				break;
			case DIR_D:
				g->y++;
				break;
			case DIR_L:
				g->x--;
				break;
		}
	}
}

// void moveGhosts(void)
// {
// 	for(uint i = 0; i < GHOSTSNUM; i++){
// 		ghosts[i].lastx = ghosts[i].x;
// 		ghosts[i].lasty = ghosts[i].y;
// 		uint newx = ghosts[i].x;
// 		uint newy = ghosts[i].y;
// 		switch (ghosts[i].facing) {
// 			case DIR_R:
// 				newx+=ghosts[i].speed;
// 				break;
// 			case DIR_L:
// 				newx-=ghosts[i].speed;
// 				break;
// 			case DIR_U:
// 				newy-=ghosts[i].speed;
// 				break;
// 			case DIR_D:
// 				newy+=ghosts[i].speed;
// 				break;
// 		}
// 		switch (whatsAtS(newx,newy)) {
// 			case '#':	// Wall
// 				return;
// 				break;
// 			case '0':	// Warp
// 				if(newx==0 && ghosts[i].facing==DIR_L){
// 					newx = MTS(MAPX-1);
// 					break;
// 				}
// 				if(newx==MTS(MAPX-1) && ghosts[i].facing==DIR_R){
// 					newx = 0;
// 					break;
// 				}
// 				break;
// 			default:
// 			case ' ':	// Empty
// 				break;
// 		}
// 		ghosts[i].x = newx;
// 		ghosts[i].y = newy;
// 	}
// }

}// extern "C"
