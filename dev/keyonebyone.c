#include <iostream>
#include <stdio.h>
#include <wiringPi.h>

/*
   3V3  (1) (2)  5V
 GPIO2  (3) (4)  5V
 GPIO3  (5) (6)  GND
 GPIO4  (7) (8)  GPIO14
   GND  (9) (10) GPIO15
GPIO17 (11) (12) GPIO18
GPIO27 (13) (14) GND
GPIO22 (15) (16) GPIO23
   3V3 (17) (18) GPIO24
GPIO10 (19) (20) GND
 GPIO9 (21) (22) GPIO25
GPIO11 (23) (24) GPIO8
   GND (25) (26) GPIO7
 GPIO0 (27) (28) GPIO1
 GPIO5 (29) (30) GND
 GPIO6 (31) (32) GPIO12
GPIO13 (33) (34) GND
GPIO19 (35) (36) GPIO16
GPIO26 (37) (38) GPIO20
   GND (39) (40) GPIO21
*/


//
// 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0
// 0 0 1 2 0 1 2 3|4 5 A A E L H R
// b Y Y Y X X X X|X X C O R C S C
//
//
  
const int keycode [] = {  0b0000000000000000  //a
			};

void printbin(int number, int num_digits) {
    int digit;
    for(digit = num_digits - 1; digit >= 0; digit--) {
        printf("%c", number & (1 << digit) ? '1' : '0');
    }
}

int main() {
    char c;

    if (wiringPiSetup () == -1)
    return 1 ;

    pinMode (0, OUTPUT) ;         // aka BCM_GPIO pin 17

    // Set the terminal to raw mode
    system("stty raw");

    while(1) {
        c = getchar(); 
        // terminate when "." is pressed
        if(c == '.') {
            system("stty cooked");
            exit(0);
        }  
	//std::cout << c << " was pressed.\r"<< std::endl;
        std::cout << "ASCII Value of " << c << " is " << int(c) << "  ";
        printbin (int(c),8); 
        std::cout << "\n\r";
        /*
	digitalWrite (0, 1) ;       // On
        delay (500) ;               // mS
        digitalWrite (0, 0) ;       // Off
        delay (500) ;
	*/
    }
}
