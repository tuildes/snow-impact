#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "init.h"
// #include "levels.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2

#define KEYBOARD_DELAY 5

// Inicializa o teclado e coloca na fila
void init_keyboard(unsigned char *key, ALLEGRO_EVENT_QUEUE* queue);

// Atualiza o teclado e faz acoes no jogo a parti dele
void update_keyboard(unsigned char *key, ALLEGRO_EVENT event, bool *finished);

// Mapeamento de teclas clicadas
void keyboard_mapping(unsigned char *key);

void keyboard_options(unsigned char *key, bool *pause, bool *debug, 
                      unsigned int actualScreen, unsigned char *choose,
                      float *textY);

#endif // __KEYBOARD_H__