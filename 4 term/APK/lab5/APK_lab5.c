#include <stdio.h>
#include <stdlib.h>

#include <dos.h>

#define SEC 1000
#define SUCCESS 0xFA
#define KEYBOARD_INTERRUPT 0x09
#define KEYBOARD_LIGHTS_CODE 0xED

#define NONE 0x00
#define SCROLL_LOCK 0x01
#define NUM_LOCK 0x02
#define CAPS_LOCK 0x04

typedef unsigned char byte;

int command_succeeded = 0;

void interrupt (*old_handler)(void);

void interrupt new_handler(void) {
  byte scan_code = inp(0x60);
  printf("%X\n", scan_code);

  command_succeeded = (scan_code == SUCCESS);

  old_handler();
}

void set_mask(byte mask) {
  int i = 0;

  while (!command_succeeded) {
    // Wait until buffer is empty
    while ((inp(0x64) & 0x02));
    outp(0x60, KEYBOARD_LIGHTS_CODE);

    // Wait until buffer is empty
    while ((inp(0x64) & 0x02));
    outp(0x60, mask);

    if (++i == 3) {
      fputs("Failed to set mask 3 times in a row\n", stderr);
      setvect(KEYBOARD_INTERRUPT, old_handler);
      exit(EXIT_FAILURE);
    }
  }
  command_succeeded = 0;
}

int main(void) {
  old_handler = getvect(KEYBOARD_INTERRUPT);
  setvect(KEYBOARD_INTERRUPT, new_handler);

  set_mask(SCROLL_LOCK);
  delay(SEC);
  set_mask(NUM_LOCK);
  delay(SEC);
  set_mask(CAPS_LOCK);
  delay(SEC);
  set_mask(NONE);
  delay(SEC);
  set_mask(SCROLL_LOCK | NUM_LOCK | CAPS_LOCK);
  delay(SEC);
  set_mask(NONE);

  setvect(KEYBOARD_INTERRUPT, old_handler);
  return EXIT_SUCCESS;
}
