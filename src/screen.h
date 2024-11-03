#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "player.h"

#define X_SCREEN 960 // Largura da janela
#define Y_SCREEN 540 // Altura da janela

#define FRAMERATE 30.0 // Framerate do jogo
#define FONT_SIZE 12
#define FONT_SIZE_BOLD (FONT_SIZE + (4 * DISP_SCALE))

#define BUFFER_W 640
#define BUFFER_H 360
#define BUFFER_STATUS_H 60

#define DISP_SCALE  2                       // Escala da janela pelo buffer
#define DISP_W      (BUFFER_W * DISP_SCALE) // Largura da janela
#define DISP_H      (BUFFER_H * DISP_SCALE) // Altura da janela

#define DISP_STATUS_H (DISP_H - (BUFFER_STATUS_H * DISP_SCALE))
#define VERSION_PROJECT "Versao 0.1"

extern long frames; // Variavel global de frames
extern ALLEGRO_DISPLAY *disp;
extern ALLEGRO_BITMAP *buffer, *icon;

void display_init();
void display_destroy();

void display_pre_draw();
void display_post_draw();

void draw_status_bar(Player player, ALLEGRO_FONT* font);

#endif // __SCREEN_H__