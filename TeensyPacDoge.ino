#include "Includes.h"

void setup()
{
	screenInit();
	btnInit();

	PacDoge doge={MTS(MAPX/2),MTS(MAPY/2),3,1.0f,DIR_L,false};
	drawMap();
	drawPacDoge(doge);
}

void loop()
{
	
}
