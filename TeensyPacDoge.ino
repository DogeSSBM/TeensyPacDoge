#include "Includes.h"

typedef enum{DIR_U, DIR_R, DIR_D, DIR_L}Direction;

struct Pacman {
	uint x = 0;
	uint y = 0;
	uint lives = 0;
	float speed = 1.0;
	Direction facing = DIR_L;
};

struct Ghost {
	uint x = 0;
	uint y = 0;
	float speed = 1.0;
	Direction facing = DIR_L;
	Color color;
};

void setup()
{
	screenInit();
	drawMap();
}

void loop()
{

}
