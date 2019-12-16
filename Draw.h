#pragma once

#define SCALE	(SCREENX / MAPX)
#define HSCALE	(SCALE/2)

void drawMap(void)
{
	for(uint y = 0; y < MAPY; y++){
		for(uint x = 0; x < MAPX; x++){
			switch(blocks[y][x]){
				case '#':	// Wall
					screen.fillRect(x*SCALE, y*SCALE, SCALE, SCALE, BLUE);
					break;
				case '.':	// Dot
					screen.fillCircle(x*SCALE+HSCALE, y*SCALE+HSCALE, HSCALE/3, YELLOW);
					break;
				case '@':	// Power Dot
					screen.fillCircle(x*SCALE+HSCALE, y*SCALE+HSCALE, HSCALE/2, YELLOW);
					break;
				case '0':	// Warp
					screen.fillRect(x*SCALE, y*SCALE, SCALE, SCALE, DARKGREY);
					break;
				case ' ':	// Empty
				default:

					break;
			}
		}
	}
}

void drawGhost(const Ghost g)
{
	setColor(g.color);
	fillCircle(g.x,g.y,HSCALE-1);
}

void drawPacDoge(const PacDoge p)
{
	setColor(YELLOW);
	fillCircle(p.x,p.y,HSCALE-1);
}
