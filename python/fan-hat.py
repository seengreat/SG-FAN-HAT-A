'''
 * Seengreat SG-FAN-HAT-A demo
 * Experimental Platform :Raspberry Pi 4B + SG-FAN-HAT-A
 * Author    : Andy Li
 * Web Site  : www.seengreat.com
'''
import time
import math
import smbus

from rpi_ws281x import PixelStrip,Color
from random import randint


LED_COUNT = 6
LED_PIN =  18 # D12 or D18 or D21
time_interval = 10
strip = PixelStrip(LED_COUNT, LED_PIN)
strip.begin()

# Raspi PCA9685 16-Channel PWM Servo Driver
# Registers/etc.
SUBADR1            = 0x02
SUBADR2            = 0x03
SUBADR3            = 0x04
MODE1              = 0x00
MODE2              = 0x01
PRESCALE           = 0xFE
LED0_ON_L          = 0x06
LED0_ON_H          = 0x07
LED0_OFF_L         = 0x08
LED0_OFF_H         = 0x09
ALLLED_ON_L        = 0xFA
ALLLED_ON_H        = 0xFB
ALLLED_OFF_L       = 0xFC
ALLLED_OFF_H       = 0xFD
  
USR_PWM0        = 0
USR_PWM1        = 1
USR_PWM2        = 2
USR_PWM8        = 8
USR_PWM9        = 9
USR_PWM10        = 10
USR_PWM11        = 11
USR_PWM12        = 12
USR_PWM13        = 13
USR_PWM14        = 14
USR_PWM15        = 15

SPEED_LED_D2     = 3
SPEED_LED_D3     = 4
SPEED_LED_D4     = 5
SPEED_LED_D5     = 6

FAN_PWM        = 7



class PCA9685:
    def __init__(self):
        self.i2c = smbus.SMBus(1)
        self.dev_addr = 0x7f
        self.write_reg(MODE1, 0x00)
        self.fan_speed = 0 # 0~100 represent 0%~100% of fan speed

    def write_reg(self, reg, value):
        self.i2c.write_byte_data(self.dev_addr, reg, value)

    def read_reg(self, reg):
        res = self.i2c.read_byte_data(self.dev_addr, reg)
        return res

    def setPWMFreq(self, freq):
        prescaleval = 25000000.0    # 25MHz
        prescaleval /= 4096.0       # 12-bit
        prescaleval /= float(freq)
        prescaleval -= 1.0
        prescale = int(math.floor(prescaleval + 0.5))
        
        oldmode = self.read_reg(MODE1)
        newmode = (oldmode & 0x7F) | 0x10  # sleep
        self.write_reg(MODE1, newmode)        # go to sleep
        self.write_reg(PRESCALE, prescale)
        self.write_reg(MODE1, oldmode)
        time.sleep(0.005)
        self.write_reg(MODE1, oldmode | 0x80)  # 0x80

    def setPWM(self, ch, on, off):
        self.write_reg(LED0_ON_L+4*ch, on & 0xFF)
        self.write_reg(LED0_ON_H+4*ch, on >> 8)
        self.write_reg(LED0_OFF_L+4*ch, off & 0xFF)
        self.write_reg(LED0_OFF_H+4*ch, off >> 8)

    def set_fan_speed(self, speed):   # fan speed percentage: 0~100 represent 0%~100% of fan speed
        pulse = int(speed*150+4999)
        pulse = pulse*4096/20000      # PWM frequency is 50HZ,the period is 19999us=20ms
        self.setPWM(FAN_PWM, 0, int(pulse))

    def show_fan_speed(self, speed):   # fan speed percentage: 0~100 represent 0%~100% of fan speed
        if speed == 40:
            self.setPWM(SPEED_LED_D2, 0, 4096) #D2
            self.setPWM(SPEED_LED_D3, 0, 3968) #D3
            self.setPWM(SPEED_LED_D4, 4096, 0) #D4
            self.setPWM(SPEED_LED_D5, 4096, 0) #D5
        elif speed == 50:
            self.setPWM(SPEED_LED_D2, 0, 4096) #D2
            self.setPWM(SPEED_LED_D3, 0, 4096) #D3
            self.setPWM(SPEED_LED_D4, 4096, 0) #D4
            self.setPWM(SPEED_LED_D5, 4096, 0) #D5
        elif speed == 75:
            self.setPWM(SPEED_LED_D2, 0, 4096) #D2
            self.setPWM(SPEED_LED_D3, 0, 4096) #D3
            self.setPWM(SPEED_LED_D4, 0, 4096) #D4
            self.setPWM(SPEED_LED_D5, 4096, 0) #D5
        elif speed == 90:
            self.setPWM(SPEED_LED_D2, 0, 4096) #D2
            self.setPWM(SPEED_LED_D3, 0, 4096) #D3
            self.setPWM(SPEED_LED_D4, 0, 4096) #D4
            self.setPWM(SPEED_LED_D5, 0, 3968) #D5
        elif speed == 100:
            self.setPWM(SPEED_LED_D2, 0, 4096) #D2
            self.setPWM(SPEED_LED_D3, 0, 4096) #D3
            self.setPWM(SPEED_LED_D4, 0, 4096) #D4
            self.setPWM(SPEED_LED_D5, 0, 4096) #D5
if __name__=='__main__':
    pwm = PCA9685()
    pwm.setPWMFreq(100) #
    while True:
        temp_file = open("/sys/class/thermal/thermal_zone0/temp") # read cpu temperature
        temp = float(temp_file.read())/1000
        temp_file.close()
        print("temp:",temp)
        if temp<40.0:
            pwm.fan_speed = 40 # set FAN speed to 40%
            for i in range(6):
                strip.setPixelColor(i, Color(randint(0,256), randint(0,256),randint(0,256)))
                strip.show()
        elif temp>=40.0 and temp<50.0:
            pwm.fan_speed = 50 # set FAN speed to 50%
            for i in range(6):
                strip.setPixelColor(i, Color(0, 127, 255))
                strip.show()
        elif temp>=50.0 and temp<55.0:
            pwm.fan_speed = 75 # set FAN speed to 75%
            for i in range(6):
                strip.setPixelColor(i, Color(0, 255, 0))
                strip.show()
        elif temp>=55.0 and temp<60.0:
            pwm.fan_speed = 90 # set FAN speed to 90%
            for i in range(6):
                strip.setPixelColor(i, Color(255, 127, 0))
                strip.show()
        elif temp>=60.0:
            pwm.fan_speed = 100 # set FAN speed to 100%
            for i in range(6):
                strip.setPixelColor(i, Color(255, 0, 0))
                strip.show()
        print("speed:",pwm.fan_speed,"%")            
        pwm.set_fan_speed(pwm.fan_speed)
        pwm.show_fan_speed(pwm.fan_speed)
        time.sleep(1)

