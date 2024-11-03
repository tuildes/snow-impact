#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "player.h"

#define X_SCREEN 960 // Largura da janela
#define Y_SCREEN 540 // Altura da janela

#define STATUS_HEIGHT 100
#define Y_STATUS (Y_SCREEN - STATUS_HEIGHT) // Status onde se mostra a vida do jogador

#define VERSION_PROJECT "Versao 0.1"

extern long frames; // Variavel global de frames

void draw_status_bar(Player player, ALLEGRO_FONT* font, ALLEGRO_FONT* bold);

#endif // __SCREEN_H__