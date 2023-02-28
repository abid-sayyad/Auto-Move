# Auto-Move

https://user-images.githubusercontent.com/49099853/140011986-89487f6f-3bc4-42c4-88eb-9333cc8d791c.mp4

## Inspiration
The phrase "_ungliyon pe nachana_" which literally translates to "_making someone dance on your commands_" made me inquisitive enough to make this bot
## What it does
It is capable of autonomous movements but primarily, it maneuvers with respect to the **gestures of the user's hands**. It comprehends the direction the user wants the bot to move in and moves accordingly.
## How we built it
This built was made with Arduino IDE (C++), ADXL335 Accelerometer, 433MHz RF transceivers, L293D Motor driver, Ultrasonic sensors, Small wireless camera, Breadboard, Chassis, 12V motors,  Jumper wires, and lots of fun.

the initial stage was interfacing the accelerometer with the Arduino board, then the further parts were if-else statements governed by the data from ultrasonic sensors and the accelerometer.

then came the data transmission and receiving part which was easy just needed some encryption and decryption with the help of HT12 D and HT12 E decoders and encoders ICs respectively.
## Challenges we ran into
*establishing a stable connection between the transmitter and receiver

*reading the error-free accelerometer readings

*adding the obstacle avoidance feature.

## Accomplishments that we're proud of
This bot was used to transport basic household loads around the household and around the locality, and also is my first hack!
## What we learned
I learned about embedded systems, mode about using codes for interacting with ICs, and with some thinking each and everything is achievable. 

## What's next for jagiya-bot
This bot is currently undergoing some drastic changes for itself, where this will accommodate the following: 
1) GPS navigation
2) Robotic Arm
3) Sanitisation sprays
4) Solar source of power
5) AI vision
6) Voice Recognisiton  
