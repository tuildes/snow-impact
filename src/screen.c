#include "screen.h"
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
    al_destroy_bitmap(buffer);
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
    if((mult <= 2.25) && (frames % 20 == 0)) mult += 0.02; 
}

void draw_status(Player player, ALLEGRO_FONT* font, bool debug, 
                 unsigned int actualScreen, Boss boss) {

    #define MARGIN_BORDER 4 
    #define DEBUG_COLOR al_map_rgb(100, 100, 100)

    // Tempo de jogo
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (MARGIN_BORDER), 
                (MARGIN_BORDER), 
                ALLEGRO_ALIGN_LEFT,
                "Time: %.0lfs", floor(player.time));

    // Vidas do jogador
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (MARGIN_BORDER), 
                (MARGIN_BORDER + FONT_SIZE + 2), 
                ALLEGRO_ALIGN_LEFT,
                "Lifes: %1hd", player.lifes);

    // Fala do personagem
    if(actualScreen == 2) {
        if(mult < 1.2) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 
                    (MARGIN_BORDER), 
                    (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                    ALLEGRO_ALIGN_LEFT,
                    "[SHIP]: KLUTZY MAKING ROBOTS? TIME TO DESTROY");
        } else if ((mult > 1.8) && (mult < 2)) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 
                                (MARGIN_BORDER), 
                                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                                ALLEGRO_ALIGN_LEFT,
                                "[SHIP]: KLUTZY IS COMING!");
        } else if (boss.actualHp == 0) {
             al_draw_text(font, al_map_rgb(255, 255, 255), 
                                (MARGIN_BORDER), 
                                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                                ALLEGRO_ALIGN_LEFT,
                                "[KLUTZY]: Clickity click click"
                                " (you got me)");
        }

    // Fala personagem (fase 02)
    } else {
        if(mult < 1.2) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 
                    (MARGIN_BORDER), 
                    (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                    ALLEGRO_ALIGN_LEFT,
                    "[SHIP]: SNOW THUGS? TIME TO SHOOT!");
        } else if ((mult > 1.8) && (mult < 2)) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 
                                (MARGIN_BORDER), 
                                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                                ALLEGRO_ALIGN_LEFT,
                                "[SHIP]: HEBERT IS COMING!");
        } else if (boss.actualHp == 0) {
             al_draw_text(font, al_map_rgb(255, 255, 255), 
                                (MARGIN_BORDER), 
                                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                                ALLEGRO_ALIGN_LEFT,
                                "[HERBERT]: YOU ARE VERY STRONG."
                                "MANAGED TO CAPTURE ME");
        }
    }

    // Textos de depuracao
    if(debug) {
        // Posicao do player e multiplicador
        al_draw_textf(font, DEBUG_COLOR, 
                    (BUFFER_W - MARGIN_BORDER), MARGIN_BORDER, 
                    ALLEGRO_ALIGN_RIGHT,
                    "frames: %ld, mult: %.2f", 
                    frames, mult);
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
            (BUFFER_W >> 1), ((BUFFER_H >> 1) - 5), 
            ALLEGRO_ALIGN_CENTER,
            "SNOW IMPACT PAUSED!");

    al_draw_text(font, al_map_rgb(255, 255, 255), 
            (BUFFER_W >> 1), ((BUFFER_H >> 1) + FONT_SIZE), 
            ALLEGRO_ALIGN_CENTER,
            "Press P or ESC to resume play");
}