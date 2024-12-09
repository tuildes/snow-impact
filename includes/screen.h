#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "init.h"
#include "player.h"
                      // Escala da janela pelo buffer
#define DISP_W      (BUFFER_W * DISP_SCALE) // Largura da janela
#define DISP_H      (BUFFER_H * DISP_SCALE) // Altura da janela

extern long frames; // Variavel global de frames
extern float mult;

extern ALLEGRO_DISPLAY *disp;               // DIsplay e tela do jogo
extern ALLEGRO_BITMAP *buffer, *icon;       // Buffer e icone do jogo

// Inicializa o DISPLAY e gera um EXIT em caso de erro
void init_display(ALLEGRO_EVENT_QUEUE* queue);

// Destroi o display no final do jogo
void destroy_display();

// Cuida das renderizados antes e depois do desenho
void pre_draw_display();
void post_draw_display();

void update_status();
void draw_status(Player player, ALLEGRO_FONT* font, bool debug, 
                 unsigned int actualScreen, Boss boss);
void draw_pause(ALLEGRO_FONT* font);

#endif // __SCREEN_H__