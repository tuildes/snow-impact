#include "levels.h"

unsigned int actualScreen;

void init_background(Background *b) {

    b[0].image = init_bitmap("assets/background/menu-1.png");
    b[0].velX = 0.5;

    b[1].image = init_bitmap("assets/background/menu-2.png");
    b[1].velX = 1.5;

    b[2].image = init_bitmap("assets/background/menu-3.png");
    b[2].velX = 3;

    for(size_t i = 0; i < PARALLAX_SIZE; i++) {
        b[i].height = BUFFER_H;
        b[i].width = BUFFER_W;
        b[i].x = BUFFER_W;
        b[i].y = 0;
        b[i].velY = 0;
    }
}

void update_background(Background *b) {
    for(size_t i = 0; i < PARALLAX_SIZE; i++) {
        b[i].x -= (b[i].velX * (mult * 2));
        if((b[i].x + (float)b[i].width) <= 0) b[i].x = BUFFER_W;
    }
}

void draw_background(Background *b) {
    // Background
    for(size_t i = 0; i < PARALLAX_SIZE; i++) {
        al_draw_bitmap(b[i].image, b[i].x, b[i].y, 0);
        al_draw_bitmap(b[i].image, 
                       (b[i].x + (float)b[i].width), b[i].y, 
                       ALLEGRO_FLIP_HORIZONTAL);
        al_draw_bitmap(b[i].image, 
                       (b[i].x - (float)b[i].width), b[i].y, 
                       ALLEGRO_FLIP_HORIZONTAL);
    }
}

void destroy_background(Background *b) {
    for(size_t i = 0; i < PARALLAX_SIZE; i++)
        al_destroy_bitmap(b[i].image);
}

void init_select_level(ALLEGRO_BITMAP **temp, ALLEGRO_BITMAP **temp2) {
    actualScreen = 0;
    *temp = init_bitmap("assets/title.png");
    *temp2 = init_bitmap("assets/start.png");
}

void update_select_level(unsigned char *key, bool *finished, 
                        unsigned char choose,
                        Player *player,
                        Background *background) {
    if(!key[ALLEGRO_KEY_SPACE]) return;

    switch (choose){
        case 0:
            switch_level(2, player, background);
            break;
        case 1:
            switch_level(4, player, background);
            break;
        case 2:
            *finished = true;
            break;
        default:
            break;
    }
}

void draw_select_level( ALLEGRO_FONT* font, 
                        ALLEGRO_FONT* bold,
                        Background *b, 
                        ALLEGRO_BITMAP *title,
                        unsigned char choose) {
    #define MARGIN_BORDER 10
    unsigned char actual;

    // Background
    update_background(b);
    draw_background(b);

    al_draw_filled_rectangle(0, 0, 
                        BUFFER_W, BUFFER_H, 
                        al_map_rgba_f((float)0.015, 
                                    (float)0.015, 
                                    (float)0.015, 0.5));
        
    // Titulo do jogo
    al_draw_bitmap(title, ((BUFFER_W >> 1) - 200), 50, 0);

    // Botao de level 01
    if (choose == 0) actual = 255;
    else actual = 150;
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) - 30), 
                ALLEGRO_ALIGN_CENTER,
                "LEVEL 1");

    // Botao de level 02
    if (choose == 1) actual = 255;
    else actual = 150;
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), (BUFFER_H >> 1), 
                ALLEGRO_ALIGN_CENTER,
                "LEVEL 2");

    // Botao de sair
    if (choose == 2) actual = 255;
    else actual = 150;
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 30), 
                ALLEGRO_ALIGN_CENTER,
                "SAIR");

    // Textos de tutorial
    al_draw_text(bold, al_map_rgb(100, 255, 255), 
            (BUFFER_W >> 1), ((BUFFER_H >> 1) + 70), 
            ALLEGRO_ALIGN_CENTER,
            "Tutorial de teclas");
    al_draw_text(font, al_map_rgb(50, 150, 200), 
            (BUFFER_W >> 1), ((BUFFER_H >> 1) + 90), 
            ALLEGRO_ALIGN_CENTER,
            "SETAS - movimentacao");
    al_draw_text(font, al_map_rgb(50, 150, 200), 
            (BUFFER_W >> 1), ((BUFFER_H >> 1) + 105), 
            ALLEGRO_ALIGN_CENTER,
            "ESPACO - selecionar e atirar");
    al_draw_text(font, al_map_rgb(50, 150, 200), 
            (BUFFER_W >> 1), ((BUFFER_H >> 1) + 120), 
            ALLEGRO_ALIGN_CENTER,
            "P ou ESC - pausar");
    al_draw_text(font, al_map_rgb(50, 150, 200), 
            (BUFFER_W >> 1), ((BUFFER_H >> 1) + 135), 
            ALLEGRO_ALIGN_CENTER,
            "D - informacoes de debug");

    // Creditos
    al_draw_text(bold, al_map_rgb(255, 255, 255), 
                (MARGIN_BORDER), 
                (BUFFER_H - MARGIN_BORDER - FONT_SIZE_TITLE), 
                ALLEGRO_ALIGN_LEFT,
                "Feito por tuildes");

    // Versao do projeto
    al_draw_text(bold, al_map_rgb(255, 255, 255), 
                (BUFFER_W - MARGIN_BORDER), 
                (BUFFER_H - MARGIN_BORDER - FONT_SIZE_TITLE), 
                ALLEGRO_ALIGN_RIGHT,
                VERSION_PROJECT);
}

void init_level_one(Player *player, Background *b) {
    destroy_background(b); // Desalocar memoria

    // Trocar background
    b[0].image = init_bitmap("assets/background/menu-1.png");
    b[1].image = init_bitmap("assets/background/menu-2.png");
    b[2].image = init_bitmap("assets/background/menu-3.png");

    // Setar posicao do jogador
    player->x = 50;
    player->y = (BUFFER_H >> 1);
    player->lifes = 3;
}

void init_level_two(Player *player, Background *b) {
    destroy_background(b); // Desalocar memoria

    // Trocar background
    b[0].image = init_bitmap("assets/background/level2-1.png");
    b[1].image = init_bitmap("assets/background/level2-2.png");
    b[2].image = init_bitmap("assets/background/level2-3.png");

    // Setar posicao do jogador
    player->x = 50;
    player->y = (BUFFER_H >> 1);
    player->lifes = 3;
}

void switch_level(unsigned int l, Player *player, Background *b) {
    if(l == actualScreen) return; // Evitar trocas desnecessarias

    // Loading screen

    switch(l) {
        case 2: 
            init_level_one(player, b);
            break;
        case 4:
            init_level_two(player, b);
            break;
        default:
            break;
    }

    actualScreen = l;
}