#pragma once

#define SCREENX	240
#define SCREENY	320
#include "ILI9341_t3.h"
#include "Colors.h"

ILI9341_t3 screen = ILI9341_t3(10, 9);
Color drawColor = WHITE;

void setColor(const Color color)
{
	drawColor = color;
}

void drawPixel(const uint x, const uint y)
{

}

void drawLine(const uint x1, const uint y1, const uint x2, const uint y2)
{

}

void drawRect(const uint x, const uint y, const uint xlen, const uint ylen)
{

}

void drawCircle(const uint x, const uint y, const uint radius)
{
	screen.drawCircle(x,y,radius )
}

void drawSquare(const uint x, const uint y, const uint size)
{

}

void fillRect(const uint x, const uint y)
{

}

void fillCircle(const uint x, const uint y, const uint radius)
{

}

void fillSquare(const uint x, const uint y, const uint size)
{

}

void drawText(const uint x, const uint y, const char const* text)
{
	int oldx = 0, oldy = 0;
	screen.getCursor(&oldx, &oldy);
	screen.setCursor(x, y)
	screen.print(text);
	screen.setCursor(oldx, oldy);
}

void fillText(const uint x, const uint y, const char const* text)
{
	uint len = strlen(text);
	u8 size = screen.getTextSize();
	fillRect(x,y,)
}

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
