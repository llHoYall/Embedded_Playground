/*******************************************************************************
 * @brief		Application with ultrasonic sensor.
 * @author	llChameleoNll <hoya128@gmail.com>
 * @version	v1.0
 * @history
 * 		2017.07.05	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// Standard
#include <stdio.h>
// System
#include "mbed.h"
#include "ultrasonic.h"

/* Global Variables ----------------------------------------------------------*/
Serial	pc(USBTX, USBRX);

/* Main Routine --------------------------------------------------------------*/
int main(int _argc, char* _argv[]) {
	pc.baud(115200);
	pc.printf("[APP] Start Application\n\r");

	ultrasonic_Init();

	while (1) {
		pc.printf("[APP] Distance = %u cm\n\r", ultrasonic_MeasureDistance());
	}

	return 0;
}
