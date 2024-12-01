#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "init.h"

// Variaveis de ambiente
#define PLAYER_DEFAULT_SPEED 2

// Sprites do jogador
#define PLAYER_W 12
#define PLAYER_H 28

typedef struct {
    float x, y;
    unsigned int lifes:2,
                 delay;
    long invincibility;
    double time;
    unsigned int kills;
    ALLEGRO_BITMAP *sprite;
} Player;

// Inicializa o PLAYER e gera um EXIT em caso de erro
Player create_player(float x, float y);

// Atualiza as variaveis do jogador e sua movimentacao
void update_player(Player *player, unsigned char *key);

// Desenha o jogador na tela
void draw_player(Player player);

// Destroi e desaloca o jogador
void destroy_player(Player *p);

// Atualiza o jogador em caso de dano
void damage_player(Player *player);

// Funcao generica de colisao
bool collide(float ax1, float ay1, float ax2, float ay2,
             float bx1, float by1, float bx2, float by2);

#endif // __PLAYER_H__