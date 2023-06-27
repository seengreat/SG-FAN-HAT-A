#ifndef __PCA9685_H_
#define __PCA9685_H_

#include <stdio.h>

#define SUBADR1          0x02
#define SUBADR2          0x03
#define SUBADR3          0x04
#define MODE1            0x00
#define MODE2            0x01
#define PRESCALE         0xFE
#define LED0_ON_L        0x06
#define LED0_ON_H        0x07
#define LED0_OFF_L       0x08
#define LED0_OFF_H       0x09
#define ALLLED_ON_L      0xFA
#define ALLLED_ON_H      0xFB
#define ALLLED_OFF_L     0xFC
#define ALLLED_OFF_H     0xFD

#define DEV_ADRR         0x7F
#define PWM_MAX_Hz 	 	 1000 
#define PWM_MIN_Hz 	 	 40 

#define USR_PWM0        0
#define USR_PWM1        1
#define USR_PWM2        2
#define USR_PWM8        8
#define USR_PWM9        9
#define USR_PWM10       10
#define USR_PWM11       11
#define USR_PWM12       12
#define USR_PWM13       13
#define USR_PWM14       14
#define USR_PWM15       15

#define SPEED_LED_D2    3
#define SPEED_LED_D3    4
#define SPEED_LED_D4    5
#define SPEED_LED_D5    6

#define FAN_PWM         7

void PCA9685_Init(unsigned int freq);
void PCA9685_SetPWM(unsigned char channel, unsigned int on, unsigned int off);
void Set_Fan_Speed(unsigned int speed);
void Show_Fan_Speed(unsigned int speed);


#endif
