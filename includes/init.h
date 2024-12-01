#ifndef __INIT_H__
#define __INIT_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define FRAMERATE 30
#define FONT_SIZE 8

// Função que inicializa todos os componentes do ALLEGRO
void init_all();

// Função que inicializa uma função e da EXIT em caso de erro
void initialize_or_exit(bool fc, const char *n);

// Inicializa o BITMAP e gera um EXIT em caso de erro
ALLEGRO_BITMAP* init_bitmap(const char *local);

// Inicializa a FONTE e gera um EXIT em caso de erro
ALLEGRO_FONT* init_font(const char *local, int fontSize);

// Inicializa um SAMPLE e gera um EXIT em caso de erro
ALLEGRO_SAMPLE* init_sample(const char *local);

// Inicializa a MUSICA e gera um EXIT em caso de erro
ALLEGRO_AUDIO_STREAM* init_music();

// Inicializa o TIMER e gera um EXIT em caso de erro
ALLEGRO_TIMER* init_timer(float framerate, ALLEGRO_EVENT_QUEUE* queue);

#endif // __INIT_H__