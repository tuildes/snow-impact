#include "keyboard.h"

unsigned int keyboardDelay;

void init_keyboard(unsigned char *key, ALLEGRO_EVENT_QUEUE* queue) {
    keyboardDelay = KEYBOARD_DELAY;
    memset(key, 0, (sizeof(unsigned char) * ALLEGRO_KEY_MAX));
    al_register_event_source(queue, al_get_keyboard_event_source());
}

void update_keyboard(unsigned char *key, ALLEGRO_EVENT event, bool *finished) {
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

void keyboard_options(unsigned char *key, bool *pause, bool *debug, 
                      unsigned int actualScreen, unsigned char *choose) {
    if(keyboardDelay < KEYBOARD_DELAY) { 
        keyboardDelay++;
        return;
    }

    switch(actualScreen) {
        case 0:
            if((*choose != 0) && key[ALLEGRO_KEY_UP]) {
                keyboardDelay = 0;
                (*choose)--;
            }
            else if((*choose != 2) && key[ALLEGRO_KEY_DOWN]) {
                keyboardDelay = 0;
                (*choose)++;
            } 
            break;
        case 2:
        case 4:

            if(key[ALLEGRO_KEY_P] || (key[ALLEGRO_KEY_ESCAPE])) {
                keyboardDelay = 0;
                *pause = (!(*pause));
            }
            else if ((key[ALLEGRO_KEY_D])) {
                keyboardDelay = 0;
                *debug = (!(*debug));
            }
    
            break;
        default:
            printf("Tela nao encontrada!\n");
            break;
    }
}

void keyboard_mapping(unsigned char *key) {
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++) key[i] &= KEY_SEEN;
}