#include "player.h"
#include "screen.h"
#include "bullet.h"

Player create_player(float x, float y) {
    Player p;

    p.x = x;
    p.y = y;
    p.invincibility = 0;
    p.lifes = 3;
    p.kills = 0;
    p.time = 0;
    p.delay = BULLET_DELAY;
    // Criar e guardar imagens
    p.sprite = NULL;
    p.sprite = init_bitmap("assets/sprite/player/default.png");

    return p;
}

void destroy_player(Player *p) { al_destroy_bitmap(p->sprite); }

void __movement_player(Player *p, float x, float y) {
    // Fazer a movimentacao
    p->x += (PLAYER_DEFAULT_SPEED * x);
    p->y += (PLAYER_DEFAULT_SPEED * y);

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

void update_player(Player *player, unsigned char *key, Bullet *bplayer) {
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
        if(player->delay >= BULLET_DELAY) {
            add_bullet(player->x, player->y, bplayer, 0);
            player->delay = 0;
        }
    }    

    // Invencibilidade do personagem
    if(player->invincibility > 0) (player->invincibility)--;

    if (player->delay < BULLET_DELAY) player->delay++;
}

void draw_player(Player player) { 
    if (player.lifes == 0) return; // Jogador sem vidas
    if ((player.invincibility) % 10 <= 5) // Frames de invencibilidade

    al_draw_bitmap(player.sprite, player.x, player.y, 0); 
}

void damage_player(Player *player) {
    (player->lifes)--;
    (player->invincibility) = 60;

    // Volta o multiplicador
    // if(mult < 2.0) mult -= (float)0.1;
}

bool collide(float ax1, float ay1, float ax2, float ay2,
             float bx1, float by1, float bx2, float by2) {

    // Possiveis situacoes de nao colisao
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}