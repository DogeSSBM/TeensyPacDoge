#pragma once

void inputs(void)
{
	if(btnPressed.btn2){
		resetWait(&btnState.btn2);
		btnPressed.btn2 = false;
	}

	if(btnState.btn1){
		setClearLine(screenToLine(MTS(MAPY)));
		printText("Frame Advance");
		btnPressed.btn1 = false;
		btnPressed.btnB = false;
		while(!btnPressed.btnB || !btnState.btnB);
		delay(30);
		setClearLine(screenToLine(MTS(MAPY)));
	}
}
