#include <stdio.h>
#include <linux/input.h>

int main (int argc, char *argv[])
{
  struct input_event ev;
  FILE *kbd = fopen("/dev/input/by-id/event0", "r");
  while (fread(&ev, sizeof(ev), 1, kbd) == 1)
  {
    if (ev.type == EV_KEY && (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT))
    {
      switch (ev.value)
      {
        case 0: printf("Shift released\n"); break;
        case 1: printf("Shift pressed\n"); break;
        case 2: printf("Shift repeated\n"); break;
        default: break;
      }
    }
    // similarly for KEY_LEFTCTRL, KEY_RIGHTCTRL, etc.
  }
  fclose(kbd);
  return 0;
}
