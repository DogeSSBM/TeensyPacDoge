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

typedef union{
	uint arr[4];
	struct{
		uint dirU;
		uint dirR;
		uint dirD;
		uint dirL;
	};
	struct{
		uint dirD;
		uint dirL;
		uint dirU;
		uint dirR;
	}inverse;
}AdjBounds;

typedef union Node{
	union Node *arr[4];
	struct{
		union Node *dirU;
		union Node *dirR;
		union Node *dirD;
		union Node *dirL;
	};
	struct{
		union Node *dirD;
		union Node *dirL;
		union Node *dirU;
		union Node *dirR;
	}inverse;
}Node;

// count number of valid adjacent tiles
#define ADJC(d)	((d.arr[0]) + (d.arr[1]) + (d.arr[2]) + (d.arr[3]))

// evaluates to the opposite direction INVERT(DIR_U) == DIR_D
#define INVERT(d)	((Direction)((d+2)%4))

// true if d is a vertical direction (DIR_U || DIR_D)
#define UD(d)	(~(d)&1)

// true if d is a horizontal direction (DIR_L || DIR_R)
#define LR(d)	( (d)&1)

// true if s is aligned with the map coordanates when scaled down
#define ALIGNED(s)(!(s%SCALE))

// true if both x and y are both map coordanate aligned otherwise false
#define ALIGNED2(x, y)(( (ALIGNED(x)) && (ALIGNED(y)) ))

// evaluates to the perpendicular direction
// (the direction pointing 90deg clockwise)
#define PERP1(d)	((Direction)((d+1)%4))

// evaluates to the perpendicular direction
// (the direction pointing 90deg counterclockwise)
#define PERP2(d)	((Direction)((d+3)%4))

uint wrapMx(const int x)
{
	if(x < 0)
		return (uint)(MAPX + x);
	else if(x>=MAPX)
		return (uint)(x - MAPX);
	return (uint)x;
}

uint wrapMy(const int y)
{
	if(y < 0)
		return (uint)(MAPY + y);
	else if(y>=MAPY)
		return (uint)(y - MAPY);
	return (uint)y;
}

uint wrapSx(const int x)
{
	if(x < 0)
		return (uint)(SCREENX + x);
	else if(x>=SCREENX)
		return (uint)(x - SCREENX);
	return (uint)x;
}

uint wrapSy(const int y)
{
	if(y < 0)
		return (uint)(SCREENY + y);
	else if(y>=SCREENY)
		return (uint)(y - SCREENY);
	return (uint)y;
}

void shiftCoordsM(uint *x, uint *y, const Direction d)
{
	if(UD(d))
		d == DIR_U? *y=wrapMy(*y-1) : *y=wrapMy(*y+1);
	else
		d == DIR_L? *x=wrapMx(*x-1) : *x=wrapMx(*x+1);
}

void shiftCoordsS(uint *x, uint *y, const Direction d)
{
	if(UD(d))
		d == DIR_U? *y=wrapSy(*y-SCALE) : *y=wrapSy(*y+SCALE);
	else
		d == DIR_L? *x=wrapSx(*x-SCALE) : *x=wrapSx(*x+SCALE);
}

void shiftCoordsSH(uint *x, uint *y, const Direction d)
{
	if(UD(d))
		d == DIR_U? *y=wrapSy(*y-HSCALE) : *y=wrapSy(*y+HSCALE);
	else
		d == DIR_L? *x=wrapSx(*x-HSCALE) : *x=wrapSx(*x+HSCALE);
}

char whatsAtM(const uint x, const uint y)
{
	return blocks[y][x];
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

// returns traversability struct of adjacent tiles located 1 screen coord away
AdjDir getValidAdjS(const uint x, const uint y)
{
	AdjDir ret = {
		checkBounds(wrapSx(x),	wrapSy(y-1)),
		checkBounds(wrapSx(x+1),wrapSy(y)),
		checkBounds(wrapSx(x),	wrapSy(y+1)),
		checkBounds(wrapSx(x-1),wrapSy(y))
	};
	return ret;
}

// returns traversability struct of surrounding tiles
AdjDir getValidAdjM(const uint x, const uint y)
{
	AdjDir ret = {
		traversable(whatsAtM(wrapMx(x),	wrapMy(y-1))),
		traversable(whatsAtM(wrapMx(x+1),	wrapMy(y))),
		traversable(whatsAtM(wrapMx(x),	wrapMy(y+1))),
		traversable(whatsAtM(wrapMx(x-1),	wrapMy(y)))
	};
	return ret;
}

AdjBounds getBounds(const uint x, const uint y)
{
	AdjBounds ret = {
		y,
		x+SCALE-1,
		y+SCALE-1,
		x
	};
	return ret;
}

uint countValidAdj(const AdjDir d)
{
	return d.arr[0] + d.arr[1] + d.arr[2] + d.arr[3];
}

void drawConnection(uint x, uint y, const Direction d)
{
	setColor(DARKGREEN);
	//drawSquare(MTS(x)+1, MTS(y)+1, SCALE-1);
	x = MTHS(x);
	y = MTHS(y);
	uint x2 = x;
	uint y2 = y;
	shiftCoordsSH(&x2, &y2, d);
	drawLine(x, y, x2, y2);
}

Node* generateGraphAt(const uint xorigin, const uint yorigin)
{
	if(!traversable(whatsAtM(xorigin,yorigin)))
		return NULL;
	Node *temp[MAPX][MAPY] = {{0}};

	// allocate memory for each valid node
	// if valid node, link to any surrounding valid nodes
	for(uint y = 0; y < MAPY; y++){
		for(uint x = 0; x < MAPX; x++){
			if(traversable(whatsAtM(x,y))){
				temp[x][y] = (Node*)malloc(sizeof(Node));
				AdjDir validAdj = getValidAdjM(x,y);
				for(uint i = 0; i < 4; i++){
					if(validAdj.arr[i]){
						// get the tile coords of valid adjacent
						uint adjx = x;
						uint adjy = y;
						shiftCoordsM(&adjx,&adjy,(Direction)i);
						temp[x][y]->arr[i] = temp[adjx][adjy];
						drawConnection(x,y,(Direction)i);
					}else{
						temp[x][y]->arr[i] = NULL;
					}
				}
			}
		}
	}

	return temp[xorigin][yorigin];
}

#include "Player.h"
#include "Ghost.h"

void movePlayer(void)
{
	player.power -= player.power>0;
	player.lastx = player.x;
	player.lasty = player.y;

	AdjDir validAdj = getValidAdjS(player.x, player.y);

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
		if(
		STM(player.y) == STM(g->y) ||
		STM(player.x) == STM(g->x)){

			int dx = (player.x+HSCALE) - (g->x+HSCALE);
			int dy = (player.y+HSCALE) - (g->y+HSCALE);
			dx*=dx;
			dy*=dy;
			if(dy+dx < SCALE*SCALE){
				if(player.power){
					g->x = g->spawnx;
					g->y = g->spawny;
				}else{
					_softRestart();
				}
			}
		}
	}
}

Direction randomValidAdjDir(const AdjDir d)
{
	Direction ret = (Direction)random(4);
	while(!d.arr[ret = (Direction)random(4)]);
	return ret;
}

Direction closestValidDir(const uint x, const uint y, const AdjDir d)
{
	Direction closeDir = randomValidAdjDir(d);
	uint closeDist = 10000;
	AdjBounds dist = {
		(x  -player.x)*(x  -player.x) + (y-1-player.y)*(y-1-player.y),
		(x+1-player.x)*(x+1-player.x) + (y  -player.y)*(y  -player.y),
		(x  -player.x)*(x  -player.x) + (y+1-player.y)*(y+1-player.y),
		(x-1-player.x)*(x-1-player.x) + (y  -player.y)*(y  -player.y),
	};
	for(uint i = 0; i < 4; i++){
		if(!d.arr[i])
			continue;
		if(dist.arr[i] < closeDist){
			closeDist = dist.arr[i];
			closeDir = (Direction)i;
		}
	}
	return closeDir;
}

void moveGhostsClosestTurn(void)
{
	for(uint i = 0; i < 4; i++){
		Ghost *g = &ghosts[i];
		g->lastx = g->x;
		g->lasty = g->y;
		AdjDir validAdj = getValidAdjS(g->x, g->y);
		if(!validAdj.arr[g->facing] && ALIGNED2(g->x, g->y)){
			g->facing = closestValidDir(g->x, g->y, validAdj);
		}

		// move ghost in the direction they are facing if possible
		if(validAdj.arr[g->facing]){
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
}

void moveGhostsRandom(void)
{
	for(uint i = 0; i < 4; i++){
		Ghost *g = &ghosts[i];
		g->lastx = g->x;
		g->lasty = g->y;
		AdjDir validAdj = getValidAdjS(g->x,g->y);
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


}// extern "C"
