#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>

void init_test(bool b, const char *n);

ALLEGRO_BITMAP* init_bitmap(const char *local);

void init_all();

#endif // __AUXILIAR_H__