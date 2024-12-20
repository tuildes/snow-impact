#ifndef __INIT_H__
#define __INIT_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "env.h"

#define FONT_SIZE 5
#define BUFFER_W 320
#define BUFFER_H 180

// Função que inicializa todos os componentes do ALLEGRO
void init_all();

// Função que inicializa uma função e da EXIT em caso de erro
void initialize_or_exit(bool fc, const char *n);

// Inicializa o BITMAP e gera um EXIT em caso de erro
ALLEGRO_BITMAP* init_bitmap(const char *local);

// Inicializa a FONTE e gera um EXIT em caso de erro
ALLEGRO_FONT* init_font(const char *local, int fontSize);

// Inicializa o TIMER e gera um EXIT em caso de erro
ALLEGRO_TIMER* init_timer(float framerate, ALLEGRO_EVENT_QUEUE* queue);

#endif // __INIT_H__