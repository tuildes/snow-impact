#include "enemy.h"
#include "bullet.h"

ALLEGRO_BITMAP *enemy_sprite[9];

Enemy init_enemies() {

    const char *paths[9] = {
        "assets/sprite/enemy/enemy_01.png",
        "assets/sprite/enemy/enemy_02.png",
        "assets/sprite/enemy/enemy_03.png",
        "assets/sprite/enemy/enemy_04.png",
        "assets/sprite/enemy/enemy_05.png",
        "assets/sprite/enemy/enemy_06.png",
        "assets/sprite/enemy/enemy_07.png",
        "assets/sprite/boss/herbert_mini_klutzy.png",
        "assets/sprite/boss/herbert_snowballed.png"
    };

    // Inicializar sprites
    for(size_t i = 0; i < 9; i++)  enemy_sprite[i] = init_bitmap(paths[i]);

    Enemy e;
    e.next = NULL;

    return e;
}

bool add_enemy(Enemy *enemies, int e) {

    // Encontrar posicao na lista para inserir
    Enemy *temp = enemies;
    while(temp->next != NULL) temp = temp->next;

    Enemy *new;
    if((new = (Enemy *)malloc(sizeof(Enemy))) == NULL) return 1;

    switch(e) {
        case 1:
            new->dx = 1;
            new->dy = 1.0;
            new->hp = ENEMY_HP;
            new->delay = 0;
            new->sprite = 0;
            new->width = 30;
            new->height = 28;
            break;
        case 2:
            new->dx = 0.25;
            new->dy = 0.5;
            new->hp = ENEMY_HP;
            new->delay = ENEMY_DELAY;
            new->sprite = 1;
            new->width = 30;
            new->height = 30;
            break;
        case 3:
            new->dx = 1.0;
            new->dy = 0.5;
            new->hp = ENEMY_HP;
            new->delay = (ENEMY_DELAY << 1);
            new->sprite = 2;
            new->width = 30;
            new->height = 24;
            break;
        case 4: // Inimigo: Tank
            new->dx = 1;
            new->dy = 0.25;
            new->hp = ENEMY_HP;
            new->delay = 0;
            new->sprite = 3;
            new->width = 30;
            new->height = 28;
            break;
        case 5: // Inimigo: Sly
            new->dx = 0.5;
            new->dy = 0.25;
            new->hp = ENEMY_HP;
            new->delay = ENEMY_DELAY;
            new->sprite = 4;
            new->width = 30;
            new->height = 28;
            break;
        case 6: // Inimigo: Scrap
            new->dx = 0.1;
            new->dy = (2 + rand() % 2);
            new->hp = (ENEMY_HP - 2);
            new->delay = (ENEMY_DELAY >> 1);
            new->sprite = 5;
            new->width = 30;
            new->height = 28;
            break;
        case 7: // Inimigo: Puffle
            new->dx = 5;
            new->dy = 0;
            new->hp = (ENEMY_HP);
            new->delay = 0;
            new->sprite = 6;
            new->width = 20;
            new->height = 18;
            break;
        case 8: // Inimigo: Klutzy
            new->dx = 2.5;
            new->dy = 0.1;
            new->hp = (ENEMY_HP >> 1);
            new->delay = 0;
            new->sprite = 7;
            new->width = 30;
            new->height = 30;
            break;
        case 9:
            new->dx = 2;
            new->dy = 0;
            new->hp = 1; // Nao importa a vida, ele eh indestrutivel
            new->delay = 0;
            new->sprite = 8;
            new->width = 58;
            new->height = 65;
            break;
        default:
            break;
    }

    new->x = (BUFFER_W + new->width);
    new->y = (float)(rand() % (int)(BUFFER_H - new->height));
    new->iced = false;
    new->time = 0;
    new->next = NULL;
    temp->next = new;

    return 0;
}

void __destroy_enemy(Enemy *e) {
    Enemy *temp = e->next;

    if(e->next == NULL) return;

    e->next = e->next->next;
    free(temp);
}

void update_enemies(Enemy *enemies, Player *player, Bullet *b, 
                    unsigned int actualScreen) {

    unsigned int EMEMY_FRAMES_DELAY = (unsigned int)(ENEMY_SPAWN / mult);

    // Colocar mais inimigos na tela
    if((mult < 2.0) && ((frames % EMEMY_FRAMES_DELAY) == 0)) {
        if((actualScreen == 2)) add_enemy(enemies, (1 + (rand() % 3)));
        else add_enemy(enemies, (4 + (rand() % 4)));
    }

    Enemy *temp = enemies;
    for(Enemy *enemie = enemies->next; enemie != NULL; enemie = enemie->next) {

        // Verifica a vida do inimigo
        if(enemie->hp <= 0) {
            __destroy_enemy(temp);
            (player->kills)++; 
            enemie = temp;
            continue;
        }

        if(enemie->sprite == 6) {
            if((enemie->x + enemie->width) <= 0) {
                __destroy_enemy(temp); 
                enemie = temp;
                continue;
            }
        }

        // Dano ao jogador (contato)
        if( (player->invincibility == 0) &&
            collide (player->x, player->y, 
                    (player->x + PLAYER_W), (player->y + PLAYER_H),
                    enemie->x, enemie->y,
                    (enemie->x + enemie->width), 
                    (enemie->y + enemie->height))) {
            damage_player(player);
            __destroy_enemy(temp);
            enemie = temp;
            continue;
        }

        // Movimentacao do inimigo
        if(enemie->sprite < 6) {
            if((enemie->x + (enemie->width / 2)) > (player->x + (PLAYER_W >> 1))) {
                // Entrada com velocidade dobrada
                if((enemie->x + enemie->width) >= BUFFER_W)
                    enemie->x -= 8;
                else enemie->x -= (enemie->dx * mult);
            }
            else enemie->x += (enemie->dx * mult);
        } else {
            enemie->x -= (enemie->dx * mult);
        }

        // Tipo especial de movimentacao
        if(enemie->sprite == 5) { 
            enemie->y += (enemie->dy * mult);

            if(enemie->y <= 0) {
                enemie->y = 0;
                enemie->dy *= (-1);
            } else if ((enemie->y + enemie->height) >= BUFFER_H) {
                enemie->y = (BUFFER_H - enemie->height);
                enemie->dy *= (-1);
            }

        } else {
            if((enemie->y + (enemie->height / 2) - 1) > (player->y + (PLAYER_H >> 1))) 
                enemie->y -= (enemie->dy * mult);
            else if ((enemie->y + (enemie->height / 2) + 1) < (player->y + (PLAYER_H >> 1))) 
                enemie->y += (enemie->dy * mult);
        }

        // Tiro do inimigo
        if(enemie->delay != 0) {
            if(enemie->time < enemie->delay) enemie->time++;
            else {
                add_bullet(enemie->x, (enemie->y + (enemie->height / 2)), b, 3);
                enemie->time = 0;
            }
        }

        temp = enemie;
    }
}

void draw_enemies(Enemy *enemies, bool debug, ALLEGRO_FONT* font) {
    for(Enemy *enemie = enemies->next; enemie != NULL; enemie = enemie->next) {
        al_draw_bitmap(enemy_sprite[(enemie->sprite)], 
                enemie->x, enemie->y, 
                0);
        if(debug)
            al_draw_textf(font, al_map_rgb(255, 255, 0), 
                        (enemie->x + (enemie->width / 2)), 
                        (enemie->y + enemie->height + 5), 
                        ALLEGRO_ALIGN_CENTER,
                        "%d", enemie->hp);
    }
}

void destroy_enemies(Enemy *e) {
    for(size_t i = 0; i < 9; i++) al_destroy_bitmap(enemy_sprite[i]);
    while(e->next != NULL) __destroy_enemy(e);
}