#define FPS		30
#define FRAMETIME	(1000/FPS)
#include "Includes.h"

void setup()
{
	randomSeed(analogRead(0));
	screenInit();
	btnInit();
	screen.println("Pac-Doge");
	screen.println("\nPress A");
	screen.println("to start!");

	while(!btnPressed.btnA){
		inputs();
	}
	btnPressed.btnA = false;
	screenBlank();
	drawMap();
	setTextSize(1);
}

void printStuff(void)
{
	for(uint i = 1; i < 6; i++)
		setClearLine(numLines()-i);

	const static char dirChar[] {'U', 'R', 'D', 'L'};

	setLine(numLines()-6);
	screen.println("Player");
	screen.print("X: ");		screen.println(player.x);
	screen.print("Y: ");		screen.println(player.y);
	screen.print("Dir: ");		screen.println(dirChar[player.facing]);

	setLine(numLines()-6);
	setCursorX(HSCREENX/2);
	screen.println("Tile");
	setCursorX(HSCREENX/2);
	screen.print("X: ");		screen.println((player.x+HSCALE)/SCALE);
	setCursorX(HSCREENX/2);
	screen.print("Y: ");		screen.println((player.y+HSCALE)/SCALE);
	setCursorX(HSCREENX/2);
	screen.print("Char: ");		screen.println(whatsAtS(player.x+HSCALE,player.y+HSCALE));

	setLine(numLines()-6);
	setCursorX(HSCREENX);
	screen.println("Score");
	setCursorX(HSCREENX);
	screen.print("Dots: ");		screen.println(player.dots);
	setCursorX(HSCREENX);
	screen.print("Power: ");	screen.println(player.power);
}

void loop()
{
	Epoch elapsed;
	inputs();

	moveGhostsClosestTurn();
	drawGhosts();
	collideGhosts();

	movePlayer();
	drawPlayer();
	collidePlayer();

	printStuff();

	while(elapsed < FRAMETIME);
}
