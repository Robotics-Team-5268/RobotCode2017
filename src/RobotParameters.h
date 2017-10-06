/*
 * DECLARE CONSTANTS HERE
 */

#ifndef SRC_ROBOTPARAMETERS_H_
#define SRC_ROBOTPARAMETERS_H_

#define DRIVE_SPEED_CONTROLLER_FL_CHANNEL 2
#define DRIVE_SPEED_CONTROLLER_FR_CHANNEL 1
#define DRIVE_SPEED_CONTROLLER_BL_CHANNEL 4
#define DRIVE_SPEED_CONTROLLER_BR_CHANNEL 3
#define DRIVE_SPEED_CONTROLLER_LIFT_CHANNEL_1 	5
#define DRIVE_SPEED_CONTROLLER_LIFT_CHANNEL_2 	6
#define GYRO_SPI_PORT 							SPI::kOnboardCS0_
//#define GYRO_ANALOG_PORT 0
//relay 0 m- is hooked to red led
//relay 0 m+ is hooked to camera led
//relay 1 m- is hooked to green led
//relay 1 m+ is hooked to blue led
//relay 2 m+ is hooked to led master power
//relay 2 m- is not hooked up

// LED numbers must be in order of relay and then M-/M+ pin
// To determine relay number, divide by 2. To determine M-/M+ pin, mod by 2.
#define LED_RED 0
#define LED_CAMERA 1
#define LED_GREEN 2
#define LED_BLUE 3
#define LED_SPARE 4
#define LED_MASTER 5

#define SCFL_INVERTED true
#define SCBL_INVERTED true
#define SCFR_INVERTED false
#define SCBR_INVERTED false

#define CAMERA_XRES 640
#define CAMERA_YRES 480

#define X_ORIGIN_OFFSET .5 //Scale from -1,1

#define RIGHT_TRIGGER 3
#define LEFT_TRIGGER 2

#define Y_ERROR_MARGIN 15 // PIXELS
#define X_ERROR_MARGIN 20
#define AREA_ERROR_MARGIN .15 // PERCENT ERROR

#endif /* SRC_ROBOTPARAMETERS_H_ */
