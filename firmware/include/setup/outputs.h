#ifndef SETUP_OUTPUTS_H
#define SETUP_OUTPUTS_H

#include "config.h"

#include "servo.h"

/*******************************************************************************
 * 
 * OUTPUTS:
 * 
 * - clock servo
 * - piezzo buzzer (TODO: add)
 */

ModFirmWare::Servo clock_servo(SERVO_PWM, SERVO_DRV, 
                               SERVO_PWM_CHANNEL, SERVO_PWM_RESOLUTION, SERVO_FREQ,
                               SERVO_MIN_PULSE, SERVO_MAX_PULSE);


#endif //SETUP_OUTPUTS_H