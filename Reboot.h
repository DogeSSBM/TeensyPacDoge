#pragma once

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Application Interrupt and Reset Control location

void _softRestart()
{
	Serial.end();  //clears the serial monitor  if used
	SCB_AIRCR = 0x05FA0004;  //write value for restart
}
