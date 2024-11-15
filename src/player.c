#include "player.h"
#include "screen.h"
#include "bullet.h"

Player create_player(float x, float y) {
    Player p;
    p.x = x;
    p.y = y;
    p.speed = PLAYER_DEFAULT_SPEED;
    p.lifes = 3;
    p.time = 0;

    p.sprite = NULL;

    // Criar e guardar imagens
    p.sprite = init_bitmap("assets/sprite/player/default.png");

    return p;
}

void destroy_player(Player *p) {
    al_destroy_bitmap(p->sprite);
}

void __movement_player(Player *p, float x, float y) {
    // Fazer a movimentacao
    p->x += (p->speed * x);
    p->y += (p->speed * y);

    const float left_colission  = 0, 
                right_colission = (BUFFER_W - PLAYER_W),
                up_collision    = 0, 
                down_collision  = (BUFFER_H - PLAYER_H);

    // Arrumar colissoes de parede
    // Impedir o jogador de passar para fora da tela
    if(p->x <= left_colission) p->x = left_colission; // Colisao da parede esquerda
    if(p->x >= right_colission) p->x = right_colission;
    if(p->y <= up_collision) p->y = up_collision;
    if(p->y >= down_collision) p->y = down_collision;
}

void update_player(Player *player, unsigned char *key, ALLEGRO_SAMPLE* sample_shot) {
    if (player->lifes == 0) return; // Jogador sem vidas

    // Atualizar o tempo de jogo
    player->time += (1.0 / FRAMERATE);

    // Movimentacao do jogador
    if(key[ALLEGRO_KEY_UP])
        __movement_player(player, 0.0, -1.0);
    if(key[ALLEGRO_KEY_RIGHT])
        __movement_player(player, 1.0, 0.0);
    if(key[ALLEGRO_KEY_DOWN])
        __movement_player(player, 0.0, 1.0);
    if(key[ALLEGRO_KEY_LEFT])
        __movement_player(player, -1.0, 0.0);
    if(key[ALLEGRO_KEY_SPACE]) {
        if(delay >= BULLET_DELAY) {
            shots_add(player->x, player->y, sample_shot);
            delay = 0;
        }
    }    

    if (delay < BULLET_DELAY) delay++;
}

void draw_player(Player player) { al_draw_bitmap(player.sprite, player.x, player.y, 0); }