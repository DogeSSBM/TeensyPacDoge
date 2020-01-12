#pragma once

void inputs(void)
{
	if(btnPressed.btn2){
		resetWait(&btnState.btn2);
		btnPressed.btn2 = false;
	}

	if(btnPressed.btn1){
		setClearLine(screenToLine(MTS(MAPY)));
		printText("Frame Advance");
		btnPressed.btn1 = false;
		while(btnState.btn1 );
		delay(20);
		setClearLine(screenToLine(MTS(MAPY)));
	}
}
