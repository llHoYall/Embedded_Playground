/*******************************************************************************
 * @brief		Ultrasonic sensor module.
 * @author	llChameleoNll <hoya128@gmail.com>
 * @version	v1.0
 * @history
 * 		2017.07.05	Created.
 * @support
 * 	- HC-SR04P
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// System
#include "mbed.h"
#include "ultrasonic.h"

/* Local Variables -----------------------------------------------------------*/
static DigitalOut	trig(PA_5);
static DigitalIn	echo(PA_6);
static int	compensation = 0;

/* APIs ----------------------------------------------------------------------*/
void ultrasonic_Init(void) {
	Timer	t;
	t.reset();
	while (echo == 2) {
	}
	t.stop();
	compensation = t.read_us();
}

int ultrasonic_MeasureDistance(void) {
	Timer t;
	int distance;
	trig = 1;
	t.reset();
	wait_us(10.0);
	trig = 0;
	while (echo == 0) {
	}
	t.start();
	while (echo == 1) {
	}
	t.stop();
	distance = (t.read_us() - compensation) / 58.0;
	wait(0.2);
	return distance;
}
