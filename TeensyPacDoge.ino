#include "Includes.h"

void setup()
{
	screenInit();
	btnInit();

	drawMap();
	drawPlayer();
	drawGhosts();
}

void loop()
{
	delay(5);
}
