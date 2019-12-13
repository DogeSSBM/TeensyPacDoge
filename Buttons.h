#pragma once

#define BTNNUM	8
#define BTNLEN	(SCREENX/BTNNUM)
#define BTNY	(SCREENY-BTNLEN*2)

typedef struct{
	uint pin, x, y;
	char label;
	bool pressed, prevPressed;
}Button;

union{
	struct{
		Button u;
		Button d;
		Button l;
		Button r;
		Button s1;
		Button s2;
		Button b;
		Button a;
	};
	Button arr[BTNNUM];
}btn;

void btnRedraw(uint n)
{
	screen.fillRect(btn.arr[n].x,btn.arr[n].y,BTNLEN,BTNLEN,btn.arr[n].pressed?LIGHTGREY:DARKGREY);
	screen.drawRect(btn.arr[n].x,btn.arr[n].y,BTNLEN,BTNLEN,btn.arr[n].pressed?DARKGREY:LIGHTGREY);
	screen.fillRect(0,0,SCREENX,SCREENY/2,BLACK);

	// screen.setCursor(0,0);
	// screen.setTextColor(WHITE);
	// screen.print("Redrawing ");
	// screen.println(btn.arr[n].label);

	screen.setCursor(btn.arr[n].x+4,btn.arr[n].y);
	screen.setTextColor(btn.arr[n].pressed?RED:BLUE);
	screen.println(btn.arr[n].label);
}

void btnDraw(void)
{
	for(uint i = 0; i < BTNNUM; i++){
		if(btn.arr[i].pressed != btn.arr[i].prevPressed)
			btnRedraw(i);
	}
}

void btnRead(void)
{
	for(uint i = 0; i < BTNNUM; i++){
		btn.arr[i].prevPressed = btn.arr[i].pressed;
		btn.arr[i].pressed = !digitalRead(btn.arr[i].pin);
	}
}

void btnInit(void)
{
	btn.arr[0].label = 'u';
	btn.arr[0].pin = 16;
	btn.arr[0].y = BTNY - BTNLEN;
	btn.arr[0].x = BTNLEN/2;

	btn.arr[1].label = 'd';
	btn.arr[1].pin = 17;
	btn.arr[1].y = BTNY + BTNLEN;
	btn.arr[1].x = BTNLEN/2;

	btn.arr[2].label = 'l';
	btn.arr[2].pin = 18;
	btn.arr[2].y = BTNY;
	btn.arr[2].x = 0;

	btn.arr[3].label = 'r';
	btn.arr[3].pin = 19;
	btn.arr[3].y = BTNY;
	btn.arr[3].x = BTNLEN;

	btn.arr[4].label = '1';
	btn.arr[4].pin = 8;
	btn.arr[4].y = BTNY;
	btn.arr[4].x = (SCREENX/2)-BTNLEN;

	btn.arr[5].label = '2';
	btn.arr[5].pin = 7;
	btn.arr[5].y = BTNY;
	btn.arr[5].x = SCREENX/2;

	btn.arr[6].label = 'b';
	btn.arr[6].pin = 6;
	btn.arr[6].y = BTNY;
	btn.arr[6].x = SCREENX-(BTNLEN*2);

	btn.arr[7].label = 'a';
	btn.arr[7].pin = 5;
	btn.arr[7].y = BTNY;
	btn.arr[7].x = SCREENX-BTNLEN;

	for(uint i = 0; i < BTNNUM; i++){
		pinMode(btn.arr[i].pin, INPUT_PULLUP);
		btn.arr[i].prevPressed = false;
		btn.arr[i].pressed = true;
	}
}
