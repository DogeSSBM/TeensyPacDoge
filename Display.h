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
	screen.drawPixel(x, y, drawColor);
}

void drawLine(const uint x1, const uint y1, const uint x2, const uint y2)
{
	screen.drawLine(x1, y1, x2, y2, drawColor);
}

void drawRect(const uint x, const uint y, const uint xlen, const uint ylen)
{
	screen.drawRect(x, y, xlen, ylen, drawColor);
}

void drawCircle(const uint x, const uint y, const uint radius)
{
	screen.drawCircle(x, y, radius, drawColor);
}

void drawSquare(const uint x, const uint y, const uint size)
{
	screen.drawRect(x, y, size, size, drawColor);
}

void fillSquare(const uint x, const uint y, const uint size)
{
	screen.fillRect(x, y, size, size, drawColor);
}

void fillRect(const uint x, const uint y, const uint xlen, const uint ylen)
{
	screen.fillRect(x, y, xlen, ylen, drawColor);
}

void fillCircle(const uint x, const uint y, const uint radius)
{
	screen.fillCircle(x, y, radius, drawColor);
}

uint getTextSize(void)
{
	return screen.getTextSize();
}

void setCursor(const uint x, const uint y)
{
	screen.setCursor(x, y);
}

void printText(const char* text)
{
	screen.print(text);
}

void fillPrintText(const char* text)
{
	const uint len = strlen(text);
	const u8 size = getTextSize();
	const Color temp = drawColor;
	setColor(BLACK);
	fillRect(screen.getCursorX(), screen.getCursorX(), size*8*len, size);
	drawColor = temp;
	printText(text);
}

void drawText(const uint x, const uint y, const char* text)
{
	i16 oldx = 0, oldy = 0;
	screen.getCursor(&oldx, &oldy);
	screen.setCursor(x, y);
	screen.print(text);
	screen.setCursor(oldx, oldy);
}

void fillText(const uint x, const uint y, const char* text)
{
	const uint len = strlen(text);
	const u8 size = getTextSize();
	const Color temp = drawColor;
	setColor(BLACK);
	fillRect(x, y, size*8*len, size);
	drawColor = temp;
	drawText(x, y, text);
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
