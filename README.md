# OotBait
Open Source Arduino Standing Desk

## Introduction

Standing desks are a good starting point to introduce some physical motion into a programmer's sedentary work hours. However the controls on the motorized desks available on the market are not very customizable. 

The objective of this project is to build a smart, hackable and budget-friendly standing desk that works with you to change your posture on schedule.

## Features

### Basic features

- Motorized Sit/stand motion
- Single-click preset heights
- Display with GUI

### Advanced features (Todo) 

- Automatic sit/stand scheduling 
- LAN/browser based control
- Laser and Ultrasonic Collision detection
- Google Assistant/Alexa integration

## Hardware choices

### Under-desk Frame

This project is built around the Ikea [Skarsta](https://www.ikea.com/us/en/p/skarsta-desk-sit-stand-white-s89324812/) table, as this is an easily available and basic adjustable sit/stand desk. The Skarsta comes with a hand crank for manually raising or lowering the tabletop. It has all the mechanical parts we need, and we can add the motor, controller, sensors and display to it. These upgrades will convert it from a manual crank to a fully automable sit/stand desk, and should not cost more than US $50.

<p align="center">
    <img src="https://www.ikea.com/us/en/images/products/skarsta-desk-sit-stand-white__0777623_PE758665_S4.JPG"/>
</p>

Other desks can also be used.

### Motor

We can use any DC geared motor. The 12V 180RPM motor from Aliexpress is a decent choice at around 3 revolutions of the crank per second. At 12V it draws around 0.2A and if jammed, it has peak current draw of ~3A.

### Motor Driver

We can use any DC Motor Driver that has a 3-wire interface for a microcontroller. The MD10C from Cytron is a decent choice - it can drive a single DC motor up to 13A and also has two small SMD buttons to drive the motor in both directions. This means that if you don't want the smart electronics, arduino and the display, getting just this board and the motor is an economical way to motorize the Skarsta which costs only around $25.

### Microcontroller

We use the Arduino Uno + ESP8266 combination board. This provides a way to get Wifi, enabling you to add any functionality you can imagine.

## Circuit

#### Fritzing 

![ootbait_v01b](https://user-images.githubusercontent.com/6374430/135815432-be1cbd4b-80fc-4e09-8c00-a449f5f50a37.png)

## Obtaining the Hardware

#### Electronic components
The components can be purchased individually from:

| **Component** | **Links** | **Notes** |
| :-------- |:---:|:---------|
| **Basic Motorized Desk** |     |     | 
| Cytron Enhanced 13Amp DC Motor Driver 30A peak (10 seconds) MD10C | [Google](https://www.google.com/search?q=Cytron+Enhanced+13Amp+DC+Motor+Driver+30A+peak+(10+seconds)+MD10C) | |
| 37GB555 DC 12V 180RPM Geared Motor High Torque Gear Reducer Motor | [Banggood](https://www.banggood.in/37GB555-DC-12V-180RPM-Geared-Motor-High-Torque-Gear-Reducer-Motor-p-1068573.html?rmmds=myorder&cur_warehouse=CN) |  |
| 37 DC Motor Bracket Metal Gear Motor Fixing Bracket for Robot Smart Car | [Banggood](https://www.banggood.in/37-DC-Motor-Bracket-Metal-Gear-Motor-Fixing-Bracket-for-Robot-Smart-Car-p-1266899.html?rmmds=myorder&cur_warehouse=CN) |  (Optional) |
| 6mm x 7mm Aluminum Flexible Shaft Coupling OD19mm x L25mm CNC Stepper Motor Coupler Connector | [Banggood](https://www.banggood.in/6mm-x-7mm-Aluminum-Flexible-Shaft-Coupling-OD19mm-x-L25mm-CNC-Stepper-Motor-Coupler-Connector-p-994360.html?rmmds=myorder&cur_warehouse=CN) | The motor has a 6mm shaft. On the other side, the Skarsta's crank is a 6mm hex key (allen key). The way allen keys are measured is the distance between opposite flat surfaces, so this key would need a 7mm inner dia connector. |
| 6mm Hex key (at least 10 cm long) | | Alternatively you can cut a piece off the Skarsta's hand crank. |
| 12v 5A Power Adapter | | |
| **Automation** |     |     |
| Arduino UNO + WiFi R3 ATmega328P + ESP8266 Module 32Mb Memory USB-TTL CH340G | [Banggood](https://www.banggood.in/Geekcreit-Mega-+WiFi-R3-Module-ATmega2560+ESP8266-32Mb-Memory-USB-TTL-CH340G-p-1205437.html?cur_warehouse=CN&rmmds=search) |  |
| External Wifi antenna |  |  Optional, if you have a low wifi signal |
| 0.96 Inch OLED I2C IIC 128 x 64 Module | [Banggood](https://www.banggood.in/Geekcreit-0_96-Inch-OLED-I2C-IIC-Communication-Display-128+64-LCD-Module-Geekcreit-for-Arduino-products-that-work-with-official-Arduino-boards-p-1535708.html?cur_warehouse=CN&ID=229&rmmds=search) | Any 4-pin IIC Display should work but a 128 x 64 is preferable. |
| JoyStick Module Shield 2.54mm 5 pin Biaxial Buttons Rocker | [Banggood](https://www.banggood.in/JoyStick-Module-Shield-2_54mm-5-pin-Biaxial-Buttons-Rocker-for-PS2-Joystick-Game-Controller-Sensor-p-1566502.html?cur_warehouse=CN&rmmds=search) | |
| 3.5-5.5V Standard Passive Buzzer Module | [Banggood](https://www.banggood.in/3_5-5_5V-Standard-Passive-Buzzer-Module-p-984074.html?cur_warehouse=CN&rmmds=search0) | You can use a basic buzzer instead of a module. |
| 500 Ohm multiturn variable Trimmer Potentiometer (Trimpot)  |  | Optional, if you want to control (reduce) the buzzer volume. |
| VL53L0X TOF Based LIDAR Laser Distance Sensor  | [Banggood](https://www.banggood.in/ToF-Module-VL53L0X-Time-of-Flight-Laser-Ranging-Sensor-Laser-Distance-Sensor-Module-GROVE-I2C-p-1541298.html?cur_warehouse=CN&rmmds=search) | Optional |
| Ultrasonic IIC Distance Sensor | [Banggood](https://www.banggood.in/Wholesale-Geekcreit-Ultrasonic-Module-HC-SR04-Distance-Measuring-Ranging-Transducers-Sensor-DC-5V-2-450cm-p-40313.html?cur_warehouse=CN&rmmds=search) | Optional |
| **Miscellany** |     |     |
| M3 Bolts  |  | To connect the motor |
| M4 Bolts  |  | To connect cases to the desk |
| M4 Threaded Inserts  |  | To create strong threads in the desk |
| 10 AWG wire for motor power  |  |  |
| 22 AWG hookup wire or Dupont connectors  |  |  |
| 10A Fuse  |  | Optional  |

#### 3D Print Files
The cases can be downloaded and printed:

| **Component** | **Links** | **Notes** |
| :-------- |:---:|:---------|
| Case for motor and driver | TODO |  |
| Case for Arduino | TODO |  |
| Case for Joystick and Screen | TODO |  |
| Case for Ultrasonic Sensor | TODO |  |
| Case for Laser Sensor | TODO | Optional, if you use the sensor and your sensor does not have the case |


#### Pre-assembled Kits
Currently no kits are available to buy.

## Credits & Contributing

#### Todo

- ~~Add circuit diagram (fritzing) to readme~~
- Ultrasound and Laser sensor support for motion limits
- WiFi and Web/LAN interface
- Run motor at variable speed (start slow and accelerate if joystick is kept pushed)

### Why is it called OotBait?
 
OotBait is a stylized variant of उठ बैठ (_Uth-Baith_), the Hindi term for Sit-Stand.

### Built on top of

- [aenniw's repo](https://github.com/aenniw/ARDUINO/tree/master/skarsta)
- [pashiran's instructable](https://www.instructables.com/Motorizing-an-IKEA-SKARSTA-Table/)
- [Lady Ada's (Adafruit) Graphic Libraries](https://github.com/adafruit/Adafruit_SSD1306)
