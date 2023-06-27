 /*****************************
 * Seengreat SG-FAN-HAT-A demo
 * Experimental Platform :Raspberry Pi 4B + SG-FAN-HAT-A
 * The driver codes for WS2812B refers to the following
 * website: https://github.com/jgarff/rpi_ws281x 
 * Author    : Andy Li
 * Web Site  : www.seengreat.com
*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "pca9685.h"

#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
#include "version.h"

#include "ws2811.h"

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE  20

//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)
#define LED_PIN                 18
#define LED_COUNT               6
#define COLOR_RGB(r,g,b)        ((b<<16)|(g<<8)|r)


int main(void)
{
    int i,temp_fd;
    float temp=0.0;
    char buf[MAX_SIZE];
    unsigned int fan_speed = 0; 
        
    PCA9685_Init(100);
	
    ws2811_t ledstrip = {
	.freq = WS2811_TARGET_FREQ,
	.dmanum=10,
	.channel = {
		[0] = {
		    .gpionum = LED_PIN,
		    .count = LED_COUNT,
		    .invert = 0,
		    .strip_type = STRIP_TYPE,
		    .brightness =200, // 0~255	
		},
	  },
    };
    if(ws2811_init(&ledstrip)!=WS2811_SUCCESS)
    {
        printf("Failed to initialize WS281X LEDs \n");
    }

    while(1)
    {
	//read cpu temperature
	temp_fd = open(TEMP_PATH, O_RDONLY);
	if(temp_fd<0)
	{
	    printf("Failed to open temp path!\n");
	    return -1;
	}
	if(read(temp_fd, buf, MAX_SIZE)<0)
	{
	    printf("Failed to read temp\n");
	    return -1;
	}
	temp = atoi(buf)/1000.0;
	close(temp_fd);
	printf("temp:%.2f\n",temp);
	if(temp<40.0)
	{
	    fan_speed = 40;//set FAN speed to 40%
	    for(i=0;i<LED_COUNT;i++)
	    {
		ledstrip.channel[0].leds[i] = COLOR_RGB(rand()%256,rand()%256,rand()%256);
	    }
	}
	else if(temp >= 40.0 && temp < 50.0)
	{
	    fan_speed = 50;//set FAN speed to 50%
	    for(i=0;i<LED_COUNT;i++)
	    {
		ledstrip.channel[0].leds[i] = COLOR_RGB(0,127,255);
	    }
	}
	else if(temp >= 50.0 && temp < 55.0)
	{
	    fan_speed = 75; //set FAN speed to 75%
	    for(i=0;i<LED_COUNT;i++)
	    {
		ledstrip.channel[0].leds[i] = COLOR_RGB(0, 255, 0);
	    }
	}
	else if(temp >= 55.0 && temp < 60.0)
	{
	    fan_speed = 90;//set FAN speed to 90%
	    for(i=0;i<LED_COUNT;i++)
	    {
		ledstrip.channel[0].leds[i] = COLOR_RGB(255, 127, 0);
	    }
	}
	else if(temp >= 60.0)
	{
	    fan_speed = 100;//set FAN speed to 100%
	    for(i=0;i<LED_COUNT;i++)
	    {
		ledstrip.channel[0].leds[i] = COLOR_RGB(255, 0, 0);
	    }
	}
        printf("speed:%d %\n",fan_speed);            
        Set_Fan_Speed(fan_speed);
        Show_Fan_Speed(fan_speed);
	ws2811_render(&ledstrip);
	delay(1000);
    } 
}
