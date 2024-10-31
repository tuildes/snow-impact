#include "player.h"

Player create_player(float x, float y) {
    Player p;
    p.x = x;
    p.y = y;
    p.speed = PLAYER_DEFAULT_SPEED;

    // Criar e guardar imagens
    p.sprite[0] = init_bitmap("assets/sprite/player_idle.png");
    init_test(p.sprite[0], "sprite de jogador");

    return p;
}

void destroy_player(Player p) {
    for(size_t i = 0; i < PLAYER_SPRITES_NUM; i++)
        al_destroy_bitmap(p.sprite[i]);
}

void draw_player(Player p) {
    al_draw_bitmap(p.sprite[0], p.x, p.y, 0);
}

void movement_player(Player *p, float x, float y) {
    #define LEFT_COLLISION 0
    #define RIGHT_COLISSION (X_SCREEN - 25)
    #define UP_COLLISION 0
    #define DOWN_COLLISION (Y_SCREEN - 57)

    // Fazer a movimentacao
    p->x += (p->speed * x);
    p->y += (p->speed * y);

    // Arrumar colissoes de parede
    if(p->x <= LEFT_COLLISION) p->x = LEFT_COLLISION; // Colisao da parede esquerda
    if(p->x >= RIGHT_COLISSION) p->x = RIGHT_COLISSION;
    if(p->y <= UP_COLLISION) p->y = UP_COLLISION;
    if(p->y >= DOWN_COLLISION) p->y = DOWN_COLLISION;

}
