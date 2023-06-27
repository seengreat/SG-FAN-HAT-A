#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "pca9685.h"

int i2c_fd  = 0;


	
//PCA9685 initialization 
void PCA9685_Init(unsigned int freq)
{
	float prescaleval;
	unsigned char oldmode;
	unsigned int prescale = 0;

    wiringPiSetup(); //init wiringpi lib
    i2c_fd = wiringPiI2CSetup(DEV_ADRR);
    printf("dev_addr:%d\r\n", i2c_fd);
    	
	wiringPiI2CWriteReg8(i2c_fd, MODE1, 0x00);
	prescaleval = 25000000.0;   
	prescaleval /= 4096.0;     
	prescaleval /= (float)(freq);
	prescaleval -= 1.0;
    
	oldmode = wiringPiI2CReadReg8(i2c_fd, MODE1);
	wiringPiI2CWriteReg8(i2c_fd, MODE1, (oldmode & 0x7F) | 0x10);
	wiringPiI2CWriteReg8(i2c_fd, PRESCALE, prescale);
	wiringPiI2CWriteReg8(i2c_fd, MODE1, oldmode);
	delayMicroseconds(200);

	wiringPiI2CWriteReg8(i2c_fd, MODE1, oldmode | 0x80);
    wiringPiI2CWriteReg8(i2c_fd, MODE2, 0x04);
}

//function:	
//	Set duty cycle
//parameter	:
//	channel : Channel number
//	on      : Drive output turn-on time 
//	off     : PWM duty cycle 
void PCA9685_SetPWM(unsigned char channel, unsigned int on, unsigned int off)
{	
    wiringPiI2CWriteReg8(i2c_fd, LED0_ON_L + 4 * channel, on & 0xFF);
    wiringPiI2CWriteReg8(i2c_fd, LED0_ON_H + 4 * channel, on >> 8);
    wiringPiI2CWriteReg8(i2c_fd, LED0_OFF_L + 4 * channel, off & 0xFF);
    wiringPiI2CWriteReg8(i2c_fd, LED0_OFF_H + 4 * channel, off >> 8);
}

// fan speed percentage: 0~100 represent 0%~100% of fan speed
void Set_Fan_Speed(unsigned int speed)
{  
	unsigned int pulse=0;
    pulse = speed*150+4999;
    pulse = pulse*4096/20000; // PWM frequency is 50HZ,the period is 19999us=20ms
    PCA9685_SetPWM(FAN_PWM, 0, pulse);
}

//fan speed percentage: 0~100 represent 0%~100% of fan speed
void Show_Fan_Speed(unsigned int speed)
{   
	switch(speed)
	{
       case 40:
		  PCA9685_SetPWM(SPEED_LED_D2, 0, 4096);//D2
		  PCA9685_SetPWM(SPEED_LED_D3, 0, 3968);//D3
		  PCA9685_SetPWM(SPEED_LED_D4, 4096, 0);//D4
		  PCA9685_SetPWM(SPEED_LED_D5, 4096, 0);//D5
		  break;
       case 50:
          PCA9685_SetPWM(SPEED_LED_D2, 0, 4096);//D2
          PCA9685_SetPWM(SPEED_LED_D3, 0, 4096);//D3
          PCA9685_SetPWM(SPEED_LED_D4, 4096, 0);//D4
          PCA9685_SetPWM(SPEED_LED_D5, 4096, 0);//D5
          break;
       case 75:
          PCA9685_SetPWM(SPEED_LED_D2, 0, 4096);//D2
          PCA9685_SetPWM(SPEED_LED_D3, 0, 4096);//D3
          PCA9685_SetPWM(SPEED_LED_D4, 0, 4096);//D4
          PCA9685_SetPWM(SPEED_LED_D5, 4096, 0);//D5
          break;
       case 90:
          PCA9685_SetPWM(SPEED_LED_D2, 0, 4096);//D2
          PCA9685_SetPWM(SPEED_LED_D3, 0, 4096);//D3
          PCA9685_SetPWM(SPEED_LED_D4, 0, 4096);//D4
          PCA9685_SetPWM(SPEED_LED_D5, 0, 3968);//D5
          break;
       case 100:
          PCA9685_SetPWM(SPEED_LED_D2, 0, 4096);//D2
          PCA9685_SetPWM(SPEED_LED_D3, 0, 4096);//D3
          PCA9685_SetPWM(SPEED_LED_D4, 0, 4096);//D4
          PCA9685_SetPWM(SPEED_LED_D5, 0, 4096);//D5
          break;
       default:
          break;
	}
}
