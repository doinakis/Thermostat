# Thermostat
Home thermostat using stm nucleo (model: Stm32f401re). Parts needed:
- Stm32f401re nucleo board
- DS18B20 Temperature Sensor module for Arduino
- HC-SR04 Ultrasonic Module Distance for Arduino
- LCD Display 16x2 Module HD44780
- 3 LEDS (red, green and blue)
- 3x 1KΩ resistors for the LEDS
- 1x10KΩ και 1x1KΩ resistors for the LCD contrast
- 1x4.7KΩ for the temperature sensor.  

The 3 leds (red,green and blue) are used to indicate that the temperature exceeds a certain temperature value (red) or that the temperature is below a certain value (blue) or that a fan is on (green).

# Pin connections
- STM NUCLEO PINS  
![nucleo_pins](https://github.com/doinakis/Thermostat/blob/main/photos/nucleo_pins.jpg)
- Display  
![Display](https://github.com/doinakis/Thermostat/blob/main/photos/Display.jpg)
- HC-SR04  
![hcsr04](https://github.com/doinakis/Thermostat/blob/main/photos/HC-SR04.jpg)
- DS18B20  
![ds18B20](https://github.com/doinakis/Thermostat/blob/main/photos/DS18B20.jpg)
- LEDS  
![leds](https://github.com/doinakis/Thermostat/blob/main/photos/RGB.jpg)


# Working State
- Idle state  
![Display](https://github.com/doinakis/Thermostat/blob/main/photos/idle_state.jpg)
- Working state  
![Display](https://github.com/doinakis/Thermostat/blob/main/photos/Working%20state.jpg)
- High temperature  
![Display](https://github.com/doinakis/Thermostat/blob/main/photos/High_Temp.jpg)
- Low temperature  
![Display](https://github.com/doinakis/Thermostat/blob/main/photos/Low_Temp.jpg)
- Show the mean temperature  
![Display](https://github.com/doinakis/Thermostat/blob/main/photos/Mean.jpg)


### Usefull links  
1. [Proximity Sensor Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)  
2. [Temperature Sensor Datasheet](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)  
3. [DWT](https://dzone.com/articles/cycle-counting-on-an-arm-cortex-m-with-dwt)  
4. [Temperature Sensor helping library](https://controllerstech.com/ds18b20-and-stm32/)  
