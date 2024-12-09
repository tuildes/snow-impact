#include "boss.h"
#include "bullet.h"
#include "player.h"

Boss init_boss(unsigned int type) {
    Boss b;

    // Paths
    const char *paths[] = {
        // Herbert
        "assets/sprite/boss/boss_02_default.png",
        "assets/sprite/boss/boss_02_bullet.png",
        "assets/sprite/boss/boss_02_damaged.png",

        // Klutzy
        "assets/sprite/boss/boss_01_default.png",
        "assets/sprite/boss/boss_01_damaged.png",
        "assets/sprite/boss/boss_01_damaged.png"
    };

    b.active = false;

    // Herbert
    if(!type) {
        b.hp = (20 * ENEMY_HP);
        b.width = 108;
        b.height = 140;
        b.dy = 1.0;
        b.dx = 1.0;
        b.delay = BOSS_DELAY;

        for(size_t i = 0; i < 3; i++) b.sprite[i] = init_bitmap(paths[i]);

    // Klutzy
    } else {
        b.hp = (15 * ENEMY_HP);
        b.width = 55;
        b.height = 55;
        b.delay = BOSS_DELAY - 20;
        b.dy = 2;
        b.dx = 2;

        if(rand() % 2) b.dy = -b.dy;
        if(rand() % 2) b.dx = -b.dx;

        for(size_t i = 0; i < 3; i++) b.sprite[i] = init_bitmap(paths[(i + 3)]);
    }

    b.x = BUFFER_W;
    b.y = ((BUFFER_H - b.height) / 2);
    b.actualHp = b.hp;

    return b;
}

void update_boss(Boss *boss, Bullet *b, Enemy *enemies, Player *player, 
                 bool level) {
    if((mult >= 2.0) && (!boss->active)) boss->active = true; 
    if(!boss->active) return;
    if(boss->actualHp <= 0) return;  // Chefe morto

    // Dano ao jogador (contato)
    if( (player->invincibility == 0) &&
        collide (player->x, player->y, 
                (player->x + PLAYER_W), (player->y + PLAYER_H),
                boss->x, boss->y,
                (boss->x + boss->width), 
                (boss->y + boss->height)))
        damage_player(player);

    // Depende do boss
    if(level) {
        boss->x += boss->dx;
        boss->y += boss->dy;

        // Colisao na esquerda
        if(boss->x <= 0) {
            boss->x = 0;
            boss->dx = -boss->dx;
        }

        // Colisao em cima
        if(boss->y <= 0) {
            boss->y = 0;
            boss->dy = -boss->dy;
        }

        // Colisao na direita
        if(boss->x >= (BUFFER_W - boss->width)) {
            boss->x = (BUFFER_W - boss->width);
            boss->dx = -boss->dx; 
        }

        // Colisa em baixo
        if(boss->y >= (BUFFER_H - boss->height)) {
            boss->y = (BUFFER_H - boss->height);
            boss->dy = (boss->dy * -1);
        }

        if((frames % boss->delay) == 0) {
            if((unsigned int)(boss->actualHp * 2) < boss->hp)
            add_bullet(BUFFER_W, (BUFFER_H - (player->y) + (PLAYER_H >> 1)), 
                       b, 4);
            add_bullet(BUFFER_W, (
                       (player->y) + (PLAYER_H >> 1) - ENEMY_BULLET_H), b, 4);
        }

    } else {
        if(boss->x >= (BUFFER_W - boss->width - 10)) (boss->x) -= 20;

        // Ataques
        if((frames % boss->delay) == 0) {

            const int attack = (rand() % 4);

            // Ataque de criar inimigos na tela
            switch(attack) {

                // Dupla de puffles
                case 0:
                    add_enemy(enemies, 8);
                    add_enemy(enemies, 8);
                    break;

                // Colocar um tank a direcao do jogador
                case 1:
                    add_enemy(enemies, 4);
                    break;

                case 2:
                    add_enemy(enemies, 9);
                    break;

                // Onda de neve
                default: {
                    const int withoutBullet = (rand() % 9);

                    for(float y = 0; y < 10; y ++) {
                        if ((y != withoutBullet) && (y != (withoutBullet + 1)))
                            add_bullet(BUFFER_W, (10 + (ENEMY_BULLET_H * 3 * y)), b, 3);
                    }
                    break;
                }
            }
        }
    }    

}

void draw_boss(Boss boss) {
    if(!boss.active) return;        // Chefe nao ativo 
    if(boss.actualHp <= 0) return;  // Chefe morto

    size_t spriteBoss;

    // Sprite atual do chefe
    if(boss.actualHp >= (boss.hp * 0.75)) spriteBoss = 0;
    else if(boss.actualHp >= (boss.hp * 0.35)) spriteBoss = 1;
    else spriteBoss = 2;

    // Sprite pela vida
    al_draw_bitmap(boss.sprite[spriteBoss], 
                   boss.x, boss.y, 
                   ALLEGRO_FLIP_HORIZONTAL);

    // Vida do chefe
    al_draw_filled_rectangle((BUFFER_W - (boss.actualHp * 2) - 5), 
                            (BUFFER_H - 10), 
                            (BUFFER_W - 5), 
                            (BUFFER_H - 5), 
                            al_map_rgba(255, 255, 255, 0));
}

void destroy_boss(Boss *boss) {
    boss->active = false;

    if(boss->sprite[0] != NULL)
        for(size_t i = 0; i < 3; i++) al_destroy_bitmap(boss->sprite[i]);
}

int check_boss_death(Boss boss, float *fade, ALLEGRO_FONT* font, 
                      const char *victoryText, Player *p) {
    if((!boss.active) || (boss.actualHp > 0)) return 0;

    // Fundo de fade (para transicao)
    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, 
                            al_map_rgba_f(0, 0, 0, (*fade)));
    // Texto de trocando de fase
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                (BUFFER_W >> 1), (BUFFER_H >> 1), 
                ALLEGRO_ALIGN_CENTER,
                "%s", victoryText);

    if(*fade < 1.0) {
        (*fade) += 0.005;
        p->invincibility = 91;
    }
    else return 1; // Declarar que eh para fazer a transicao de fases
    return 0;
}