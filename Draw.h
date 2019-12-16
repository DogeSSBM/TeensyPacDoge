#pragma once

#define SCALE	(SCREENX / MAPX)
#define HSCALE	(SCALE/2)

void drawMap(void)
{
	for(uint y = 0; y < MAPY; y++){
		for(uint x = 0; x < MAPX; x++){
			switch(blocks[y][x]){
				case '#':	// Wall
					screen.fillRect(x*SCALE, y*SCALE, SCALE-1, SCALE-1, BLUE);
					break;
				case '.':	// Dot
					screen.fillCircle(x*SCALE+HSCALE, y*SCALE+HSCALE, HSCALE/3, YELLOW);
					break;
				case '@':	// Power Dot
					screen.fillCircle(x*SCALE+HSCALE, y*SCALE+HSCALE, HSCALE/2, YELLOW);
					break;
				case '0':	// Warp
					screen.fillRect(x*SCALE, y*SCALE, SCALE-1, SCALE-1, DARKGREY);
					break;
				case ' ':	// Empty
				default:

					break;
			}
		}
	}
}

void drawGhosts()
{
	for(uint i = 0; i < GHOSTSNUM; i++){
		setColor(ghosts[i].color);
		bool lr = ghosts[i].facing == DIR_R || ghosts[i].facing == DIR_L;
		uint sx = HSCALE-1+MTS(ghosts[i].x);
		uint sy = HSCALE-1+MTS(ghosts[i].y);
		lr? sx+=ghosts[i].offset : sy+=ghosts[i].offset;
		fillCircle(sx,sy,HSCALE-1);
		fillRect(sx-4,sy,SCALE,HSCALE);
	}
}

void drawPlayer(void)
{
	setColor(YELLOW);
	bool lr = player.facing == DIR_R || player.facing == DIR_L;
	uint sx = HSCALE-1+MTS(player.x);
	uint sy = HSCALE-1+MTS(player.y);
	lr? sx+=player.offset : sy+=player.offset;
	fillCircle(sx,sy,HSCALE-1);
}
