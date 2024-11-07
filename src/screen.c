#include "screen.h"
#include "levels.h"

long frames = 0;
ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *buffer, *icon;
bool debug = false;
bool paused = false;

void display_init() {

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    // Tamanho da janela
    disp = al_create_display(DISP_W, DISP_H);
    init_test(disp, "display");

    // Buffer do jogo
    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    init_test(buffer, "bitmap: buffer");

    // Setar o nome e icone da janela
    icon = init_bitmap("assets/favicon.png");
    init_test(icon, "bitmap: icone da janela");
    al_set_display_icon(disp, icon);
    al_set_window_title(disp, "Snow Impact");
}

void display_destroy() {
    al_destroy_bitmap(icon);
    al_destroy_display(disp);
}

void display_pre_draw() { al_set_target_bitmap(buffer); }

void display_post_draw() {
    al_set_target_backbuffer(disp); // Onde vai ser "desenhado"
    al_draw_scaled_bitmap(buffer, 
                          0, 0, BUFFER_W, BUFFER_H, 
                          0, 0, DISP_W, DISP_H, 0); // Ampliar o buffer
    al_flip_display(); // Desenhar na tela
}

void update_status(Player player, ALLEGRO_FONT* font) {

    #define MARGIN_BORDER 10 
    frames++; // Atualizar o valor dos frames

    // Nome da fase
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (MARGIN_BORDER), 
                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                ALLEGRO_ALIGN_LEFT,
                LEVEL_01_INTRODUCTION_TEXT);

    // Textos de depuracao
    if(debug) {
        // Frames e posicao do player
        al_draw_textf(font, al_map_rgb(150, 150, 150), 
                    (BUFFER_W - MARGIN_BORDER), MARGIN_BORDER, 
                    ALLEGRO_ALIGN_RIGHT,
                    "x: %.2f, Y: %.2f, frames: %ld", player.x, player.y, frames);
        
        // Versao do projeto
        al_draw_text(font, al_map_rgb(150, 150, 150), 
                    (BUFFER_W - MARGIN_BORDER), (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                    ALLEGRO_ALIGN_RIGHT,
                    VERSION_PROJECT);
    }
}

void draw_pause(ALLEGRO_FONT* font) {
    // Fundo preto
    al_draw_filled_rectangle(0, 0, 
                        BUFFER_W, BUFFER_H, 
                        al_map_rgba_f((float)0.015, 
                                    (float)0.015, 
                                    (float)0.015, 0.75));

    // Texto
    al_draw_text(font, al_map_rgb(255, 255, 255), 
            (BUFFER_W >> 1), (BUFFER_H >> 1), 
            ALLEGRO_ALIGN_CENTER,
            "SNOW IMPACT PAUSADO!");

    al_draw_text(font, al_map_rgb(255, 255, 255), 
        (BUFFER_W >> 1), ((BUFFER_H >> 1) + FONT_SIZE), 
        ALLEGRO_ALIGN_CENTER,
        "Clique P para retomar partida");
}