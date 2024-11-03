#include "screen.h"

long frames = 0;

void draw_status_bar(Player player, ALLEGRO_FONT* font, ALLEGRO_FONT* bold) {

    frames++; // Atualizar o valor dos frames

    // Fundo do status transparente
    al_draw_filled_rectangle(0, Y_STATUS, 
                            X_SCREEN, Y_SCREEN, 
                            al_map_rgba_f((float)0.015, 
                                        (float)0.015, 
                                        (float)0.015, 0.75));

    // Vidas do jogador
    for(unsigned int i = 0; i < player.lifes; i++)
        al_draw_bitmap(player.lifeSpr, (float)(25 + (i * 60)), (Y_STATUS + 30), 0);

    // Nome da fase
    al_draw_textf(bold, al_map_rgb(255, 255, 255), 
                (X_SCREEN - 10), (Y_STATUS + (STATUS_HEIGHT >> 1) - 5), 
                ALLEGRO_ALIGN_RIGHT,
                "Fase 1: resolvendo carangueijos");

    // Texto de depuracao
    al_draw_textf(font, al_map_rgb(50, 50, 50), 
                  (X_SCREEN - 10), (Y_STATUS + 15), 
                  ALLEGRO_ALIGN_RIGHT,
                  "x: %.2f, Y: %.2f, frames: %ld", player.x, player.y, frames);
    // Versao do projeto
    al_draw_text(font, al_map_rgb(50, 50, 50), 
                 (X_SCREEN - 10), (Y_SCREEN - 25), 
                 ALLEGRO_ALIGN_RIGHT,
                 VERSION_PROJECT);
}