SG-FAN-HAT-A from seengreat:www.seengreat.com
 =======================================
# Instructions
## 1.1、Overview
The Raspberry Pi cooling fan is a dedicated cooling solution designed for the Raspberry Pi. The Raspberry Pi is a powerful little computer, but it can generate some heat when running under heavy load. The cooling fan is designed to provide effective cooling performance and keep the Raspberry Pi running within a reasonable temperature range. It consists of PWM output chip PCA9685, 6 three-color RGB LEDs WS2812, DC power conversion circuit TPS54331, fan speed indicator LED and other circuits, and can be perfectly connected with the Raspberry Pi 40PIN GPIO header..<br>
## 1.2、Features
The module has strong heat dissipation performance, and the fan can generate forced convection, which can effectively reduce the working temperature of the Raspberry Pi and prevent overheating by exhausting hot air and blowing fresh air.<br>
The module operates with low noise, and the cooling fan adopts high-quality hydraulic bearing design to ensure silent operation <br>
The module is easy to install, and the cooling fan is designed based on the Raspberry Pi 40PIN GPIO header, which is easy to use and can be directly inserted into the 40PIN GPIO header of the Raspberry Pi without an additional power cord.<br>
Raspberry Pi cooling fans are usually compatible with various models of Raspberry Pi, such as Raspberry Pi 4B, 3B+, 3B, Zero, etc.<br>
There are 6 three-color RGB LEDs WS2812 on board, and the drive pin can be selected. This RGB LEDs can be used for various atmosphere displays, such as CPU temperature color display.<br>
There are 4 green LEDs on board, which can be used to indicate the fan speed, and the user can also freely program and define its status.<br>
The onboard power conversion circuit supports a wide range of DC voltage power supply from 7 to 28V, and can supply power to the Raspberry Pi motherboard at the same time.<br>
The on-board fan and the three-color RGB LEDs can be controlled independently  by switch.<br>
The module additionally leads to 11 channels of PWM of PCA9685.<br>
## 1.3、Parameters
|Size	|65mm(L)*56.5mm(W)	|
|----------------------|----------------------|
|Control Chip	|5V	|
|Logic voltage	|3.3V	|
|Fan Driver	|PCA9685	|
|Fan PWM Driver Duty Cycle	|≥25%	|
|Fan Speed (MAX)	|8500rpm	|

# Usage
## 2.1、Wiringpi Library Installation
sudo apt-get install wiringpi<br>
wget https://project-downloads.drogon.net/wiringpi-latest.deb #Version 4B upgrade of Raspberry Pi<br>
sudo dpkg -i wiringpi-latest.deb<br>

gpio -v #<br>
If  version 2.52 appears, the installation is successful<br>
For the Bullseye branch system, use the following command:<br>
git clone https://github.com/WiringPi/WiringPi<br>
cd WiringPi<br>
./build<br>
gpio -v<br>
Running “gpio - v” will result in version 2.70. If it does not appear, it indicates an installation error<br>
If the error prompt "ImportError: No module named 'wiringpi'" appears when running the python version of the demo code, run the following command<br>
For Python 2. x version<br>
pip install wiringpi<br>
For Python 3. x version <br>
pip3 install wiringpi<br>
Note: If the installation fails, you can try the following compilation and installation:<br>
git clone --recursive https://github.com/WiringPi/WiringPi-Python.git<br>
Note: The -- recursive option can automatically pull the submodule, otherwise you need to download it manually.<br>
Enter the WiringPi Python folder you just downloaded, enter the following command, compile and install:<br>
For Python 2. x version<br>
sudo python setup.py install<br>
For Python 3. x version<br>
sudo python3 setup.py install<br>
 If the following error occurs: <br>
Error:Building this module requires either that swig is installed(e.g.'sudo apt install swig') or that wiringpi wrap.c from thesource distribution (on pypi) is available.<br>
At this time, enter the command sudo apt install swig to install swig. After that, compile and install sudo python3 setup.py install. If a message similar to the following appears, the installation is successful.<br>
ges<br>
Adding wiringpi 2.60.0 to easy-install.pth file<br>
Installed /usr/local/lib/python3.7/dist-packages/wiringpi-2.60.0-py3.7-linux-armv7<br>
Processing dependencies for wiringpi==2.60.0Finished processing dependencies for wiringpi==2.60.0<br>
## 2.2、Install Python library
#python3<br>
sudo apt-get update<br>
sudo apt-get install python3-pip<br>
sudo apt-get install python3-pil<br>
sudo apt-get install python3-numpy<br>
sudo pip3 install spidev <br>
sudo pip3 install rpi-ws281x<br>
The routine uses the python3 environment, and you need to install smbus to run the python demo code:<br>
sudo apt-get install -y python-smbus<br>
## 2.3、Configure the I2C interface
sudo raspi-config<br>
Enable I2C interface<br>
Interfacing Options -> I2C -> Yes <br>
Install the i2c-tools tool to confirm<br>
sudo apt-get install i2c-tools<br>
View connected I2C devices<br>
i2cdetect -y 1<br>
Check the address and indicate that the connection between the fan board and the Raspberry Pi is successful, the DIP switch is connected to a high level by default (A0~A5 are all OFF), and the displayed address is 0X7F;<br>
## 2.4、Run the demo codes
1) Install the SG-FAN-HAT-A on the Raspberry Pi correctly and power on the Raspberry Pi, make sure the fan switch and the RGB LED switch are in the "ON" state.<br>
2) Run the python program:<br>
Enter the python path of demo_codes according to its own path:<br>
cd xxx/fan-hat/python  # xxx Represented as its own Raspberry Pi path<br>
Run the program：<br>
sudo python3 fan-hat.py<br>
3) Run the C program:<br>
Enter the c path of demo_codes according to its own path:<br>
cd xxx/fan-hat/c  # xxx　Represented as its own Raspberry Pi path<br>
Run the program:<br>
sudo make clean<br>
sudo make <br>
sudo ./main<br>
The program prints out the current CPU temperature and fan speed every 1 second. The fan speed is automatically adjusted according to the CPU temperature. The 4 fan speed LEDs on the board and the 6 RGB LEDs at the bottom display different states, temperature values and their corresponding values according to the CPU temperature. The status is shown in Table 1 below:<br>
|CPU　Temperature：T|	Fan speed (percentage)|	Fan Speed LED Indicators|	RGB LED effect (RGB encoding)|
|----------------------|----------------------|----------------------|----------------------|
|T<40℃	|40%|	From the left, LED 1 is fully on, LED 2 is dimly on, LED 3 and 4 are off|	Color coded randomly generated|
|40℃ =< T < 50℃|	50%|	From the left, LED 1 and 2 are all on, LED 3 and 4 are off|	（0，127，255）Light BLUE|
|50℃ =< T < 55℃|	75%|	From the left, LED 1, 2, and 3 are all on, and LED 4 is off|	（0，255，0）GREEN|
|55℃ =< T < 60℃|	90%|	From the left, the LED 1, 2, and 3 are all on, and the LED 4 is dimly on|	（255，127，0）YELLOW|
|60℃ =< T|	100%|	4 LED all on|	（255，0，0）RED|
4) Switch function<br>
Turn the switch of the fan and the RGB LED from "ON" to "OFF" and check whether the fan and the 6 RGB LEDs have been turned off. If they are not turned off, it is abnormal.<br>
5) Temperature control test<br>
Install sysbench:<br>
sudo apt install sysbench<br>
Start the thread scheduling test:<br>
sysbench --test=threads --num-threads=4 --thread-yields=10000 run<br>
Turn the fan switch to "OFF" and the RGB LED switch to "ON"．<br>
Then observe whether the 4 fan speed LEDs and RGB LEDs are displayed according to the status in Table 1. <br>
   Then turn the fan switch to "ON", at this time the CPU temperature will slowly drop, and then observe whether the 4 fan speed LEDs and RGB LEDs are displayed according to the status in Table 1.<br>
6) Boot self-starting test<br>
  C：<br>
Open /etc/rc.local：<br>
sudo nano /etc/rc.local<br>
Add the following before "exit 0":<br>
sudo /home/pi/fan-hat/c/main &  <br>
Save and restart the Raspberry Pi, and check whether the demo code is running normally after restarting.<br>
  python：<br>
Open /etc/rc.local：<br>
sudo nano /etc/rc.local<br>
Add the following before "exit 0":<br>
sudo python3 /home/pi/fan-hat/python/fan-hat.py &<br>
Save and restart the Raspberry Pi, and check whether the demo code is running normally after restarting.<br>
  Note: c code and python cannot be run at the same time, you should comment out "sudo python3 /home/pi/fan-hat/python/fan-hat.py &" when you need to start up and run C code, and you need to start up to run python code "sudo /home/pi/fan-hat/c/main &" should be commented out.<br>

__Thank you for choosing the products of Shengui Technology Co.,Ltd. For more details about this product, please visit:
www.seengreat.com__

