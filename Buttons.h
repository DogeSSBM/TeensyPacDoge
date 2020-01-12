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
	struct{
		char btnD;
		char btnU;
		char btnR;
		char btnL;
		char btn2;
		char btn1;
		char btnA;
		char btnB;
	}inverse;
}btnLabel = {'U','D','L','R','1','2','B','A'};

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
	struct{
		uint btnD;
		uint btnU;
		uint btnR;
		uint btnL;
		uint btn2;
		uint btn1;
		uint btnA;
		uint btnB;
	}inverse;
}btnPin = {16,17,18,19,8,7,6,5};

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
	struct{
		bool btnD;
		bool btnU;
		bool btnR;
		bool btnL;
		bool btn2;
		bool btn1;
		bool btnA;
		bool btnB;
	}inverse;
}btnState;

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
	struct{
		bool btnD;
		bool btnU;
		bool btnR;
		bool btnL;
		bool btn2;
		bool btn1;
		bool btnA;
		bool btnB;
	}inverse;
}btnPressed;

void onPress(void)
{
	cli();
	for(uint i = 0; i < BTNNUM; i++) {
		bool newState = !digitalRead(btnPin.arr[i]);
		if(newState != btnState.arr[i]) {
			btnState.arr[i] = newState;
			btnPressed.arr[i] = true;
		}
	}
	sei();
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

void clearPressed(void)
{
	for(uint i = 0; i < BTNNUM; i++)
		btnPressed.arr[i] = false;
}

void btnInit(void)
{
	for(uint i = 0; i < BTNNUM; i++) {
		pinMode(btnPin.arr[i], INPUT_PULLUP);
		attachInterrupt(btnPin.arr[i], onPress, CHANGE);
	}
	clearPressed();
}

} // extern "C"
