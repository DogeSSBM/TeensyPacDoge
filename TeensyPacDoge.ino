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

#define FRAMETIME	(1000/30)
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

	//showPressed();

	while(elapsed < FRAMETIME);
}
