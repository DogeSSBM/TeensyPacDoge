#pragma once
extern "C"{
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
	char arr[BTNNUM] = {'U','D','L','R','1','2','B','A'};
	struct{
		char btnU;
		char btnD;
		char btnL;
		char btnR;
		char btn1;
		char btn2;
		char btnB;
		char btnA;
	};
}btnLabel;

const union{
	uint arr[BTNNUM] = {16,17,18,19,8,7,6,5};
	struct{
		uint btnU;
		uint btnD;
		uint btnL;
		uint btnR;
		uint btn1;
		uint btn2;
		uint btnB;
		uint btnA;
	};
}btnPin;

volatile union{
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

volatile struct{
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
}btnPressed;

void onPress(void)
{
	for(uint i = 0; i < BTNNUM; i++) {
		bool newState = !digitalRead(btnPin.arr[i]);
		if(newState != btnState.arr[i]) {
			btnState.arr[i] = newState;
			btnPressed.arr[i] = true;
		}
	}
}

void showPressed(void)
{
	for(uint i = 0; i < BTNNUM; i++) {
		if(btnPressed.arr[i]){
			screenBlank();
			setCursor(0,0);
			screen.print(btnLabel.arr[i]);
			printText(btnState.arr[i] ? " Pressed":" Released");
			btnPressed.arr[i] = false;
		}
	}
}

void btnInit(void)
{
	for(uint i = 0; i < BTNNUM; i++) {
		pinMode(btnPin.arr[i], INPUT_PULLUP);
		attachInterrupt(btnPin.arr[i], onPress, CHANGE);
	}
}

} // extern "C"
