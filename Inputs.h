#pragma once

void inputs(void)
{
	if(btnPressed.btn2){
		setLine(numLines()-2);
		printText("Restarting in");
		setLine(numLines()-1);
		printText("3 Seconds");
		Epoch holdTime;
		while(btnState.btn2){
			if(holdTime > 3000){
				screenBlank();
				setLine(0);
				printText("Restarting now!");
				delay(250);
				_softRestart();
			}
		}
		setColor(BLACK);
		fillRect(0,MTS(MAPY),SCREENX,SCREENY-MTS(MAPY));
		btnPressed.btn2 = false;
	}

	if(btnPressed.btn1){
		player.speed = btnState.btn1;
		btnPressed.btn1 = false;
	}

	for(uint i = 0; i < 4; i++){
		if(btnPressed.arr[i]){
			if(btnState.arr[i])
				player.facing = (Direction)i;
			btnPressed.arr[i] = false;
		}
	}
}
