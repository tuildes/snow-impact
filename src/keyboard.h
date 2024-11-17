#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "init.h"
#include "levels.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2

#define KEYBOARD_DELAY 5

extern unsigned int keyboardDelay;

void init_keyboard(unsigned char *key, ALLEGRO_EVENT_QUEUE* queue);

void update_keyboard(unsigned char *key, ALLEGRO_EVENT event, bool *finished);

void keyboard_mapping(unsigned char *key);

void keyboard_options(unsigned char *key, bool *pause, bool *debug,
                      unsigned char *choose);

#endif // __KEYBOARD_H__