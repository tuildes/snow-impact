#include "levels.h"
#include "boss.h"
#include "bullet.h"

void init_select_level(unsigned int *actualScreen);
void init_stats_level(Background *b);
void init_level_one(Player *player, Background *b, Boss *boss, 
                    Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                    Enemy *enemies);
void init_level_two(Player *player, Background *b, Boss *boss, 
                    Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                    Enemy *enemies);

void init_background(Background *b) {

    b[0].image = init_bitmap("assets/background/menu-1.png");
    b[0].velX = 0.1;

    b[1].image = init_bitmap("assets/background/menu-2.png");
    b[1].velX = 0.5;

    b[2].image = init_bitmap("assets/background/menu-3.png");
    b[2].velX = 0.15;

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
    for(size_t i = 0; i < PARALLAX_SIZE; i++) al_destroy_bitmap(b[i].image);
}

void init_select_level(unsigned int *actualScreen) {
    *actualScreen = 0;
}

void update_select_level(unsigned char *key, bool *finished, 
                        unsigned char choose,
                        Player *player,
                        Background *background,
                        unsigned int *actualScreen,
                        Boss *boss, 
                        Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                        Enemy *enemies) {
                            
    if(!key[ALLEGRO_KEY_SPACE]) return;

    switch (choose){
        case 0:
            switch_level(1, player, background, actualScreen, boss, bulletsPlayer, bulletsEnemy, enemies);
            break;
        case 1:
            switch_level(3, player, background, actualScreen, boss, bulletsPlayer, bulletsEnemy, enemies);
            break;
        case 2:
            *finished = true;
            break;
        default:
            break;
    }
}

void draw_select_level( ALLEGRO_FONT* font, ALLEGRO_FONT* title,
                        Background *b, 
                        unsigned char choose) {
    #define MARGIN_BORDER 5
    unsigned char actual;

    // Background
    update_background(b);
    draw_background(b);

    al_draw_filled_rectangle(0, 0, 
                        BUFFER_W, BUFFER_H, 
                        al_map_rgba_f((float)0.015, 
                                    (float)0.015, 
                                    (float)0.015, 0.25));

    al_draw_text(title, al_map_rgb(255, 200, 255), 
                (BUFFER_W >> 1), 30, 
                ALLEGRO_ALIGN_CENTER,
                "SNOW IMPACT");
    al_draw_text(font, al_map_rgb(255, 235, 255), 
                (BUFFER_W >> 1), (57), 
                ALLEGRO_ALIGN_CENTER,
                "INSPIRADO EM SPACE IMPACT E CLUB PENGUIN");

    // Botao de level 01
    if (choose == 0) actual = 255;
    else actual = 50;
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) - 10), 
                ALLEGRO_ALIGN_CENTER,
                "LEVEL 1");
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), (BUFFER_H >> 1), 
                ALLEGRO_ALIGN_CENTER,
                "PROCURANDO CARANGUEIJOS");

    // Botao de level 02
    if (choose == 1) actual = 255;
    else actual = 50;
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 15), 
                ALLEGRO_ALIGN_CENTER,
                "LEVEL 2");
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 25), 
                ALLEGRO_ALIGN_CENTER,
                "CAPTURANDO HERBERT");

    // Botao de sair
    if (choose == 2) actual = 255;
    else actual = 50;
    al_draw_text(font, al_map_rgb(actual, actual, actual), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 40), 
                ALLEGRO_ALIGN_CENTER,
                "SAIR");

    // Creditos
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                (MARGIN_BORDER), 
                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                ALLEGRO_ALIGN_LEFT,
                "Feito por tuildes");
}

void destroy_select_level(Background *b) {
    destroy_background(b); // Desalocar memoria
}

void init_level_one(Player *player, Background *b, Boss *boss, 
                    Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                    Enemy *enemies) {

    // Trocar background
    b[0].image = init_bitmap("assets/background/level1-1.png");
    b[0].velX = 0.25;

    b[1].image = init_bitmap("assets/background/level1-2.png");
    b[1].velX = 0.5;

    b[2].image = init_bitmap("assets/background/level1-3.png");
    b[2].velX = 1;

    // Inicializar variaveis
    *boss           = init_boss(1);
    *bulletsPlayer  = init_bullets();
    *bulletsEnemy   = init_bullets(); 
    *enemies        = init_enemies();

    // Setar posicao do jogador
    player->x = 50;
    player->y = (BUFFER_H >> 1);
    player->lifes = 3;

    mult = 1.0;
}

void init_level_two(Player *player, Background *b, Boss *boss, 
                    Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                    Enemy *enemies) {
    
    // Trocar background
    b[0].image = init_bitmap("assets/background/level2-1.png");
    b[0].velX = 0.25;

    b[1].image = init_bitmap("assets/background/level2-2.png");
    b[1].velX = 0.5;

    b[2].image = init_bitmap("assets/background/level2-3.png");
    b[2].velX = 1;

    // Inicializar variaveis
    *boss           = init_boss(0);
    *bulletsPlayer  = init_bullets();
    *bulletsEnemy   = init_bullets(); 
    *enemies        = init_enemies();

    // Setar posicao do jogador
    player->x = 50;
    player->y = (BUFFER_H >> 1);
    player->lifes = 3;

    mult = 1.0;
}

void destroy_level_two(Background *b, Boss *boss, 
                       Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                       Enemy *enemies) {

    destroy_background(b);
    destroy_bullets(bulletsPlayer);
    destroy_bullets(bulletsEnemy);
    destroy_enemies(enemies);
    destroy_boss(boss);
}

void switch_level(unsigned int l, Player *player, Background *b, 
                  unsigned int *actualScreen, 
                  Boss *boss, 
                  Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                  Enemy *enemies) {
    if(l == *actualScreen) return; // Evitar trocas desnecessarias

    // Destruir tela anterior
    destroy_actual_level(*actualScreen, b, boss, 
                         bulletsPlayer, bulletsEnemy, enemies);

    // Carregar a proxima tela
    switch(l) {
        case 2: 
            init_level_one(player, b, boss, 
                           bulletsPlayer, bulletsEnemy, enemies);
            break;
        case 4:
            init_level_two(player, b, boss, 
                           bulletsPlayer, bulletsEnemy, enemies);
            break;
        case 6:
            init_stats_level(b);
        default:
            break;
    }

    *actualScreen = l;
}

// Destruir tela anterior
void destroy_actual_level(unsigned int actualScreen, Background *b,
                          Boss *boss, 
                          Bullet *bulletsPlayer, Bullet *bulletsEnemy,
                          Enemy *enemies) {

    switch(actualScreen) {
        case 0: 
            destroy_select_level(b);
            break;
        case 2:
        case 4:
            destroy_level_two(b, boss, bulletsPlayer, bulletsEnemy, enemies);
        default:
            break;
    }

}

int draw_history_level(size_t max, float *y, 
                        const char *texts[], 
                        ALLEGRO_FONT *font) {

    for(size_t i = 0; i < max; i++)
        al_draw_text(font, al_map_rgb(255, 255, ((i < 2) ? 255 : 0)), 
                    (BUFFER_W >> 1), 
                    (BUFFER_H - (*y) + ((FONT_SIZE << 1) * i)), 
                    ALLEGRO_ALIGN_CENTER,
                    texts[i]);

    (*y) += 0.5;

    if((BUFFER_H - (*y) + ((FONT_SIZE << 1) * max)) < 0) {
        (*y) = 0;
        return 1;
    }
    return 0;
}

void init_stats_level(Background *b) {
    // Trocar background
    b[0].image = init_bitmap("assets/background/stats-1.png");
    b[0].velX = 0.1;

    b[1].image = init_bitmap("assets/background/stats-2.png");
    b[1].velX = 0.2;

    b[2].image = init_bitmap("assets/background/stats-3.png");
    b[2].velX = 0.3;
}

void draw_stats_level(ALLEGRO_FONT* font, ALLEGRO_FONT* title, 
                      Background *b, Player player) {
    #define MARGIN_BORDER 5

    // Background
    update_background(b);
    draw_background(b);

    al_draw_filled_rectangle(0, 0, 
                        BUFFER_W, BUFFER_H, 
                        al_map_rgba_f((float)0.015, 
                                    (float)0.015, 
                                    (float)0.015, 0.25));

    al_draw_text(title, al_map_rgb(255, 200, 255), 
                (BUFFER_W >> 1), 30, 
                ALLEGRO_ALIGN_CENTER,
                "SNOW IMPACT");
    al_draw_text(font, al_map_rgb(255, 235, 255), 
                (BUFFER_W >> 1), (57), 
                ALLEGRO_ALIGN_CENTER,
                "INSPIRADO EM SPACE IMPACT E CLUB PENGUIN");

    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (BUFFER_W >> 1), (BUFFER_H >> 1), 
                ALLEGRO_ALIGN_CENTER,
                "Tempo: %.0lfs", floor(player.time));
    
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 10), 
                ALLEGRO_ALIGN_CENTER,
                "Inimigos derrotados: %d (+ 2 chefes)", player.kills);

    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 20), 
                ALLEGRO_ALIGN_CENTER,
                "Tiros dados: %d", player.bullets);

    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (BUFFER_W >> 1), ((BUFFER_H >> 1) + 30), 
                ALLEGRO_ALIGN_CENTER,
                "Pontos: %d", (5000 - (int)(player.time) + (5 * player.kills)));

    // Creditos
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                (MARGIN_BORDER), 
                (BUFFER_H - MARGIN_BORDER - FONT_SIZE), 
                ALLEGRO_ALIGN_LEFT,
                "Feito por tuildes");
}