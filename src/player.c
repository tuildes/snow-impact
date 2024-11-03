#include "player.h"
#include "screen.h"

Player create_player(float x, float y) {
    Player p;
    p.x = x;
    p.y = y;
    p.speed = PLAYER_DEFAULT_SPEED;
    p.lifes = 3;

    p.sprite = NULL;
    p.lifeSpr = NULL;

    // Criar e guardar imagens
    p.sprite = al_load_bitmap("assets/sprite/player/default.png");
    p.lifeSpr = al_load_bitmap("assets/sprite/hp.png");

    init_test(p.sprite, "sprite de jogador");
    init_test(p.lifeSpr, "sprite de hp");

    return p;
}

void destroy_player(Player *p) {
    al_destroy_bitmap(p->sprite);
    al_destroy_bitmap(p->lifeSpr);
}

void draw_player(Player p) {
    al_draw_bitmap(p.sprite, p.x, p.y, 0);
}

void movement_player(Player *p, float x, float y) {
    #define PLAYER_MARGIN 5
    #define LEFT_COLLISION (0 + PLAYER_MARGIN)
    #define RIGHT_COLISSION (X_SCREEN - 25 - PLAYER_MARGIN)
    #define UP_COLLISION (0 + PLAYER_MARGIN)
    #define DOWN_COLLISION (Y_STATUS - 57 - PLAYER_MARGIN)

    // Fazer a movimentacao
    p->x += (p->speed * x);
    p->y += (p->speed * y);

    // Arrumar colissoes de parede
    if(p->x <= LEFT_COLLISION) p->x = LEFT_COLLISION; // Colisao da parede esquerda
    if(p->x >= RIGHT_COLISSION) p->x = RIGHT_COLISSION;
    if(p->y <= UP_COLLISION) p->y = UP_COLLISION;
    if(p->y >= DOWN_COLLISION) p->y = DOWN_COLLISION;
}
