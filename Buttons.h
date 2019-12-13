#pragma once

#define BTNNUM	8

#define BTN_U	16
#define BTN_D	17
#define BTN_L	18
#define BTN_R	19
#define BTN_1	8
#define BTN_2	7
#define BTN_B	6
#define BTN_A	5

const union{
	char arr[BTNNUM];
	struct{
		char btnU = 'U';
		char btnD = 'D';
		char btnL = 'L';
		char btnR = 'R';
		char btn1 = '1';
		char btn2 = '2';
		char btnB = 'B';
		char btnA = 'A';
	};
}btnLabel;

const union{
	uint arr[BTNNUM];
	struct{
		uint btnU = 16;
		uint btnD = 17;
		uint btnL = 18;
		uint btnR = 19;
		uint btn1 = 8;
		uint btn2 = 7;
		uint btnB = 6;
		uint btnA = 5;
	};
}btnPin;

union{
	bool arr[BTNNUM];
	struct{
		bool btnU;
		bool btnD;
		bool btnL;
		bool btnR;
		bool btn1;
		bool btn2;
		bool btnB;
		bool btnA;
	};
}btnState;

void showPressed(void)
{
	static bool prev[BTNNUM] = {0};
	for(uint i = 0; i < BTNNUM; i++){
		bool newState = !digitalRead(i);
		if(newState != btnState.arr[i]){
			btnState.arr[i] = newState;
			screenBlank();
			drawText(0, 0)
		}
	}
}

void btnInit(void)
{
	pinMode(BTN_U, INPUT_PULLUP);
	pinMode(BTN_D, INPUT_PULLUP);
	pinMode(BTN_L, INPUT_PULLUP);
	pinMode(BTN_R, INPUT_PULLUP);
	pinMode(BTN_1, INPUT_PULLUP);
	pinMode(BTN_2, INPUT_PULLUP);
	pinMode(BTN_B, INPUT_PULLUP);
	pinMode(BTN_A, INPUT_PULLUP);
}
