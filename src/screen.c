#include "screen.h"
// #include "levels.h"
#include <math.h>

long frames;
float mult;

ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *buffer, *icon;

void init_display(ALLEGRO_EVENT_QUEUE* queue) {

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    // Tamanho da janela
    disp = al_create_display(DISP_W, DISP_H);
    initialize_or_exit(disp, "display");

    // Buffer do jogo
    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    initialize_or_exit(buffer, "bitmap: buffer");

    // Setar o nome e icone da janela
    icon = init_bitmap("assets/favicon.png");
    al_set_display_icon(disp, icon);
    al_set_window_title(disp, "Snow Impact");

    al_register_event_source(queue, al_get_display_event_source(disp));

    frames = 0;
    mult = 1.0;
}

void destroy_display() {
    al_destroy_bitmap(icon);
    al_destroy_display(disp);
}

void pre_draw_display() { 
    al_set_target_bitmap(buffer); 
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void post_draw_display() {
    al_set_target_backbuffer(disp); // Onde vai ser "desenhado"
    al_draw_scaled_bitmap(buffer, 
                          0, 0, BUFFER_W, BUFFER_H, 
                          0, 0, DISP_W, DISP_H, 0); // Ampliar o buffer
    al_flip_display(); // Desenhar na tela
}

void update_status() {
    frames++; // Atualizar o valor dos frames

    // A cada X frames atualiza a velocidade do jogo
    if((mult <= 2.25) && (frames % 20 == 0)) mult += 0.01; 
}

// void draw_status(Player player, ALLEGRO_FONT* font, bool debug) {

//     #define MARGIN_BORDER 10 
//     #define DEBUG_COLOR al_map_rgb(200, 200, 200)

//     // Vida
//     al_draw_textf(font, al_map_rgb(255, 255, 255), 
//                 (MARGIN_BORDER), 
//                 (MARGIN_BORDER), 
//                 ALLEGRO_ALIGN_LEFT,
//                 "Vidas: %1hd", player.lifes);

//     // Pontos
//     al_draw_textf(font, al_map_rgb(255, 255, 255), 
//                 (MARGIN_BORDER), 
//                 (MARGIN_BORDER + FONT_SIZE), 
//                 ALLEGRO_ALIGN_LEFT,
//                 "Tempo: %.0lfs", floor(player.time));

//     // Nome da fase
//     al_draw_textf(font, al_map_rgb(255, 255, 255), 
//                 (MARGIN_BORDER), 
//                 (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
//                 ALLEGRO_ALIGN_LEFT,
//                 "teste");

//     // Textos de depuracao
//     if(debug) {
//         // Frames e posicao do player
//         al_draw_textf(font, DEBUG_COLOR, 
//                     (BUFFER_W - MARGIN_BORDER), MARGIN_BORDER, 
//                     ALLEGRO_ALIGN_RIGHT,
//                     "x: %.0f, Y: %.0f, frames: %06ld, mult: %.2f", player.x, player.y, frames, mult);
//     }
// }

// void draw_pause(ALLEGRO_FONT* font) {
//     // Fundo preto
//     al_draw_filled_rectangle(0, 0, 
//                         BUFFER_W, BUFFER_H, 
//                         al_map_rgba_f((float)0.015, 
//                                     (float)0.015, 
//                                     (float)0.015, 0.75));

//     // Texto
//     al_draw_text(font, al_map_rgb(255, 255, 255), 
//             (BUFFER_W >> 1), ((BUFFER_H >> 1) - 20), 
//             ALLEGRO_ALIGN_CENTER,
//             "SNOW IMPACT PAUSADO!");

//     al_draw_text(font, al_map_rgb(255, 255, 255), 
//         (BUFFER_W >> 1), ((BUFFER_H >> 1) + FONT_SIZE_TITLE - 20), 
//         ALLEGRO_ALIGN_CENTER,
//         "Clique P ou ESC para retomar partida");
// }