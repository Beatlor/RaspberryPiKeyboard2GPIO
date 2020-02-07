#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include "/usr/include/linux/input-event-codes.h"
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


/*
 ev.time: time of the event (struct timeval type)
 ev.type: EV_KEY
 ev.code: KEY_*, key identifier; see complete list in /usr/include/linux/input.h
 ev.value: 0 if key release, 1 if key press, 2 if autorepeat keypress
*/


static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

bool SHIFTL,SHIFTR,CTRLL,ALTL,ALTGR,CAPSLOCK,F12;
int key_code;

int main(void)
{
    wiringPiSetup ();

    pinMode (0, OUTPUT); digitalWrite (0, LOW);
    pinMode (1, OUTPUT); digitalWrite (1, LOW);
    pinMode (2, OUTPUT); digitalWrite (2, LOW);
    pinMode (3, OUTPUT); digitalWrite (3, LOW);
    pinMode (4, OUTPUT); digitalWrite (4, LOW);
    pinMode (5, OUTPUT); digitalWrite (5, LOW);
    pinMode (6, OUTPUT); digitalWrite (6, LOW);
    pinMode (7, OUTPUT); digitalWrite (7, LOW);
    pinMode (8, OUTPUT); digitalWrite (8, LOW);
    pinMode (9, OUTPUT); digitalWrite (9, LOW);
    pinMode (10, OUTPUT); digitalWrite (10, LOW);
    pinMode (11, OUTPUT); digitalWrite (11, LOW);
    pinMode (12, OUTPUT); digitalWrite (12, LOW);
    pinMode (13, OUTPUT); digitalWrite (13, LOW);
    
    const char *dev = "/dev/input/event0";
    struct input_event ev;
    ssize_t n;
    int fd;
    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }
    while (1) {
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
        key_code = (int)ev.code;
	  if (ev.value == 1) {
            switch (key_code) {
	      case 42:  { SHIFTL=true;    digitalWrite (0, HIGH); } break;
	      case 54:  { SHIFTR=true;    digitalWrite (1, HIGH); } break;
              case 29:  { CTRLL=true;     digitalWrite (2, HIGH); } break;
              case 56:  { ALTL=true;      digitalWrite (3, HIGH); } break;
              case 100: { ALTGR=true;     digitalWrite (4, HIGH); } break;
              case 58:  { CAPSLOCK=true;  digitalWrite (5, HIGH); } break;
              case 88:  {  F12=true;      digitalWrite (6, HIGH); } break;
              default: { printf("   %s 0x%04x (%d)", evval[ev.value], (int)ev.code, (int)ev.code);
              printf (" - %d %d %d %d %d %d %d\n",SHIFTL,SHIFTR,CTRLL,ALTL,ALTGR,CAPSLOCK,F12);
              }
 	   }
	 }



         //printf ("0 %d %d %d %d %d %d %d\n",SHIFTL,SHIFTR,CTRLL,ALTL,ALTGR,CAPSLOCK,F12);
	 if (ev.value == 0) {
            switch (key_code) {
	      case 42: { SHIFTL=false;   digitalWrite (0, LOW); } break;
	      case 54: { SHIFTR=false;   digitalWrite (1, LOW); } break;
              case 29: { CTRLL=false;    digitalWrite (2, LOW); } break;
              case 56: { ALTL=false;     digitalWrite (3, LOW); } break;
              case 100:{ ALTGR=false;    digitalWrite (4, LOW); } break;
              case 58: { CAPSLOCK=false; digitalWrite (5, LOW); } break;
              case 88: { F12=false;      digitalWrite (6, LOW); } break;
            }
          }    
        }
    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}
