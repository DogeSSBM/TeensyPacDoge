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

	Direction dir = player.facing;
	for(uint i = 0; i < 4; i++){
		if(btnPressed.arr[i]){
			dir = (Direction)i;
			btnPressed.arr[i] = false;
		}
	}
	if(dir == player.facing)
		return;
	if(player.facing==DIR_U || player.facing==DIR_D){
		if(dir==DIR_L || dir==DIR_R){
			player.turn = dir;
			return;
		}
		player.facing = dir;
		return;
	}
	if(player.facing==DIR_L || player.facing==DIR_R){
		if(dir==DIR_U || dir==DIR_D){
			player.turn = dir;
			return;
		}
		player.facing = dir;
		return;
	}
}
