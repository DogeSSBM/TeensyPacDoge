#define FPS		30
#define FRAMETIME	(1000/FPS)
#include "Includes.h"

void setup()
{
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

	setLine(numLines()-6);
	screen.println("Player");
	screen.print("X: ");		screen.println(player.x);
	screen.print("Y: ");		screen.println(player.y);
	screen.print("Dir: ");		screen.println(btnLabel.arr[player.facing]);

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

	//screenBlank();
	//drawMap();

	moveGhosts();
	drawGhosts();

	movePlayer();
	drawPlayer();
	collidePlayer();

	printStuff();

	while(elapsed < FRAMETIME);
}
