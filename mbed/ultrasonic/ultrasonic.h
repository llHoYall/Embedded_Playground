/*******************************************************************************
 * @brief		Ultrasonic sensor module.
 * @author	llChameleoNll <hoya128@gmail.com>
 * @version	v1.0
 * @history
 * 		2017.07.05	Created.
 * @support
 * 	- HC-SR04P
 ******************************************************************************/

#ifndef __ULTRASONIC_SENSOR_H__
#define __ULTRASONIC_SENSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* API Prototypes ------------------------------------------------------------*/
void ultrasonic_Init(void);
int ultrasonic_MeasureDistance(void);

#ifdef __cplusplus
}
#endif

#endif

