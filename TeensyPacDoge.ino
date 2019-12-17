#include "Includes.h"

void setup()
{
	screenInit();
	btnInit();

	drawPlayer();
	drawGhosts();
}

void loop()
{
	delay(250);
}
