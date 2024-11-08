#include "keyboard.h"

unsigned int keyboardDelay;

void keyboard_init(unsigned char *key, ALLEGRO_EVENT_QUEUE* queue) {
    keyboardDelay = KEYBOARD_DELAY;
    memset(key, 0, (sizeof(unsigned char) * ALLEGRO_KEY_MAX));
    al_register_event_source(queue, al_get_keyboard_event_source());
}

void keyboard_update(unsigned char *key, ALLEGRO_EVENT event, bool *finished) {
    switch(event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            *finished = true;
            break;
    }
}

void keyboard_options(unsigned char *key, bool *pause, bool *debug) {
    if(keyboardDelay < KEYBOARD_DELAY) { 
        keyboardDelay++;
        return;
    }

    keyboardDelay = 0;

    if(key[ALLEGRO_KEY_P]) *pause = (!(*pause));
    else if (key[ALLEGRO_KEY_D]) *debug = (!(*debug));
}

void keyboard_mapping(unsigned char *key) {
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++) 
        key[i] &= KEY_SEEN;
}