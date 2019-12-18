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
}

#define FRAMETIME	(1000/30)
void loop()
{
	Epoch elapsed;
	inputs();

	moveGhosts();
	drawGhosts();

	movePlayer();
	drawPlayer();

	while(elapsed < FRAMETIME);
}
