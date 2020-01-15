#pragma once

void drawDot(uint x, uint y, bool power)
{
	screen.fillCircle(MTHS(x), MTHS(y), HSCALE/(power?2:3), YELLOW);
}

void drawWall(uint x, uint y)
{
	screen.fillRect(MTS(x)+HSCALE/2, MTS(y)+HSCALE/2, HSCALE, HSCALE, BLUE);
}

void drawMap(void)
{
	for(uint y = 0; y < MAPY; y++){
		for(uint x = 0; x < MAPX; x++){
			switch(blocks[y][x]){
				case '#':	// Wall
					drawWall(x, y);
					break;
				case '.':	// Dot
					drawDot(x, y, false);
					break;
				case '@':	// Power Dot
					drawDot(x, y, true);
					break;
				case '0':	// Warp
					screen.fillRect(MTS(x), MTS(y), SCALE-1, SCALE-1, DARKGREY);
					break;
				case ' ':	// Empty
				default:

					break;
			}
		}
	}
}

void drawMask(const uint x, const uint y, const bool m[][SCALE])
{
	for(uint yoff = 0; yoff < SCALE; yoff++){
		for(uint xoff = 0; xoff < SCALE; xoff++){
			if(m[yoff][xoff])
				drawPixel(x+xoff,y+yoff);
		}
	}
}

void drawGhosts(void)
{
	for(uint i = 0; i < GHOSTSNUM; i++){
		// if(ghosts[i].x == ghosts[i].lastx && ghosts[i].y == ghosts[i].lasty)
			// continue;
		setColor(BLACK);
		drawMask(ghosts[i].lastx, ghosts[i].lasty, fillMask);
		setColor(player.power?BLUE:ghosts[i].color);
		drawMask(ghosts[i].x, ghosts[i].y, ghostMask);
	}
	for(uint i = 0; i < SCALE; i++)
		ghostMask[SCALE-1][i]=ghostMask[SCALE-1][(i+1)%SCALE];
}

void drawPlayer(void)
{
	setColor(BLACK);
	drawMask(player.lastx, player.lasty, playerMask);
	setColor(YELLOW);
	drawMask(player.x, player.y, playerMask);
	setColor(BLACK);
	if(UD(player.facing)){
		if(player.facing == DIR_U)
			drawLine(player.x,player.y,player.x,player.y-SCALE);
		else
			drawLine(player.x,player.y,player.x,player.y+SCALE);
	}else{
		if(player.facing == DIR_L)
			drawLine(player.x,player.y,player.x-SCALE,player.y);
		else
			drawLine(player.x,player.y,player.x+SCALE,player.y);
	}
}
