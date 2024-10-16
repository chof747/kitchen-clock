#ifndef CONFIG_H
#define CONFIG_H

//Board Pin Definitions

#define RDY_IND       6  // charging indicator battery charger
#define CHG_IND       7  // ready indicator battery charger

#define SERVO_DRV     5  // Pin driving Servo high-side switch
#define SERVO_PWM    47  // PWM pin for servo control

#define ADC_00_DRV    8  // Pin driving 3v3 line for ADC 0 (to prevent termister overheat)
#define ADC_01_DRV    9  // Pin driving 3v3 line for ADC 1 (to prevent termister overheat)

#define MODE_BTN     13  // Mode button pin
#define REN_BTN      10  // Rotary ENcoder click button pin
#define REN_DAT      11  // Rotery ENcoder data line
#define REN_CLK      12  // Rotery ENcoder clock line

#define BUZZ_PWM     21  // PWM pin for Buzzer control

#define DISPLAY_CS   38  // TFT display chip select
#define DISPLAY_RS   39  // TFT display register select
#define DISPLAY_RST  40  // TFT display reset
#define DISPLAY_SDA  41  // TFT display data line
#define DISPLAY_SCK  42  // TFT display clock line
#define DISPLAY_BKLT  2  // Pin driving high-side switch for TFT display backlight

#define I2C_SDA      17  // I2C data line
#define I2C_SCL      18  // I2C clock line

//Other board and peripheral definitions
#define SERVO_PWM_CHANNEL     0  // esp32 internal pwm channel
#define SERVO_PWM_RESOLUTION 10  // pwm resolution in bit
#define SERVO_FREQ           50  // frequency of the pwm channel for the servo in Hz
#define SERVO_MIN_PULSE     500  // minmum pulse width for 0°
#define SERVO_MAX_PULSE    2500  // maximum pulse width for 180°

//Battery Management

// Define the voltage thresholds (in millivolts)
#define FULLY_CHARGED_VOLTAGE 3650 // 3.65V, 100%
#define ALMOST_FULL_VOLTAGE 3500   // 3.50V, 90%
#define HIGH_VOLTAGE 3400          // 3.40V, 70%
#define MEDIUM_VOLTAGE 3300        // 3.30V, 40%
#define LOW_VOLTAGE 3200           // 3.20V, 20%
#define VERY_LOW_VOLTAGE 3000      // 3.00V, 10%
#define MINIMUM_VOLTAGE 2800       // 2.80V, 0%

// Define the percentage values at the thresholds
#define PERCENT_FULL 100
#define PERCENT_ALMOST_FULL 90
#define PERCENT_HIGH 70
#define PERCENT_MEDIUM 40
#define PERCENT_LOW 20
#define PERCENT_VERY_LOW 10
#define PERCENT_MINIMUM 0


#endif //CONFIG_H