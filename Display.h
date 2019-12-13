#pragma once

#define SCREENX	240
#define SCREENY	320
#include "ILI9341_t3.h"
#include "Colors.h"

ILI9341_t3 screen = ILI9341_t3(10, 9);

void screenBlank(void)
{
	screen.fillScreen(BLACK);
	screen.setCursor(0,0);
}

void screenInit(void)
{
	screen.begin();
	screen.setTextSize(3);
	screen.setTextColor(WHITE);
	screenBlank();
}
