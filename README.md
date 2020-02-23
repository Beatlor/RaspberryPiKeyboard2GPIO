# RaspberryPiKeyboard2GPIO

Raspberry PI or Linux Keyboard decoder and map the output to GPIO

This project reads the keyboard input from a USB connected Keyboard
and decode the output to the GPIO. This signals can be used to simulate
a keyboard matrix with 74HC4067 or similar IC. More details will follow.

To compile use the wiringPi library
gcc key2apple.cpp -o key2apple -lwiringPi

