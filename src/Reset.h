#pragma once

void resetWait(volatile bool *resetBtn)
{
	uint i = 0;
	char buffer[] = "Restarting in x Seconds";
	Epoch holdTime;
	while(*resetBtn && i < 3){
		buffer[14] = '3'-i;
		setClearLineBottom(0);
		printText(buffer);
		i++;
		while(holdTime < 1000 && *resetBtn);
		holdTime = 0;
	}

	if(i >= 3){
		screenBlank();
		setLine(0);
		printText("Restarting now!");
		delay(250);
		_softRestart();
	}
	setClearLine(numLines()-2);
	setClearLine(numLines()-1);
}
