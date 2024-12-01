#include "enemie.h"

ALLEGRO_BITMAP *enemy_sprite[6];

Enemy init_enemies() {

    const char *paths[6] = {
        "assets/sprite/enemy/01.png",
        "assets/sprite/enemy/01.png",
        "assets/sprite/enemy/01.png",
        "assets/sprite/enemy/01.png",
        "assets/sprite/enemy/01.png",
        "assets/sprite/enemy/01.png"
    };

    // Inicializar sprites
    for(size_t i = 0; i < 6; i++)  enemy_sprite[i] = init_bitmap(paths[i]);

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
            new->dx = 1.5;
            new->dy = 1.0;
            new->hp = ENEMIE_HP;
            new->delay = 0;
            new->sprite = 0;
            new->width = 30;
            new->height = 28;
            break;
        case 2:
            new->dx = 1.0;
            new->dy = 0.5;
            new->hp = ENEMIE_HP;
            new->delay = 0;
            new->sprite = 1;
            new->width = 30;
            new->height = 28;
            break;
        case 3:
            new->dx = 1.0;
            new->dy = 0.5;
            new->hp = (ENEMIE_HP << 1);
            new->sprite = 2;
            new->width = 30;
            new->height = 28;
            break;
        case 4: // Inimigo: Tank
            new->dx = 0.75;
            new->dy = 0.25;
            new->hp = (ENEMIE_HP + 2);
            new->delay = 0;
            new->sprite = 3;
            new->width = 30;
            new->height = 28;
            break;
        case 5: // Inimigo: Sly
            new->dx = 0.5;
            new->dy = 1.5;
            new->hp = (ENEMIE_HP);
            new->delay = 50;
            new->sprite = 4;
            new->width = 30;
            new->height = 28;
            break;
        case 6: // Inimigo: Scrap
            new->dx = (float)0.1;
            new->dy = (float)(3 + rand() % 2);
            new->hp = (ENEMIE_HP - 2);
            new->delay = 30;
            new->sprite = 5;
            new->width = 30;
            new->height = 28;
            break;
        default:
            break;
    }

    new->x = (BUFFER_W + new->width);
    new->y = (float)(rand() % (int)(BUFFER_H - new->height));
    new->iced = false;
    new->time = 0;
    new->actived = true;
    new->next = NULL;

    temp->next = new;

    return 0;
}

void __destroy_enemie(Enemy *e) {
    Enemy *temp = e->next;

    if(e->next == NULL) return;

    e->next = e->next->next;
    free(temp);
}

void update_enemies(Enemy *enemies, Player *player, Bullet *b) {

    unsigned int EMEMY_FRAMES_DELAY = (unsigned int)(150 / mult);

    // Colocar mais inimigos na tela
    // if(actualScreen == 4) {
    //     // APenas coloca em frames e tempos especificos
    if((mult < 2.0) && ((frames % EMEMY_FRAMES_DELAY) == 0))
        add_enemy(enemies, (4 + (rand() % 3)));
    // }

    Enemy *temp = enemies;
    for(Enemy *enemie = enemies->next; enemie != NULL; enemie = enemie->next) {

        // Verifica a vida do inimigo
        if(enemie->hp <= 0) {
            __destroy_enemie(temp);
            (player->kills)++; 
            enemie = temp;
            continue;
        }

        // Dano ao jogador (contato)
        if( (player->invincibility == 0) &&
            collide (player->x, player->y, 
                    (player->x + PLAYER_W), (player->y + PLAYER_H),
                    enemie->x, enemie->y,
                    (enemie->x + enemie->width), 
                    (enemie->y + enemie->height))) {
            damage_player(player);
            __destroy_enemie(temp);
            enemie = temp;
            continue;
        }

        // Movimentacao do inimigo
        if((enemie->x + (enemie->width / 2)) > (player->x + (PLAYER_W >> 1))) {
            // Entrada com velocidade dobrada
            if((enemie->x + enemie->width) >= BUFFER_W)
                enemie->x -= 8;
            else enemie->x -= (enemie->dx * mult);
        }
        else enemie->x += (enemie->dx * mult);

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
                if(enemie->sprite == 5)
                    add_bullet(enemie->x, enemie->y, b, 3);
                else
                    add_bullet(enemie->x, enemie->y, b, 4);
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
            al_draw_textf(font, al_map_rgb(255, 255, 255), 
                        (enemie->x + (enemie->width / 2)), 
                        (enemie->y + enemie->height), 
                        ALLEGRO_ALIGN_CENTER,
                        "%d", enemie->hp);
    }
}

void destroy_enemies(Enemy *e) {
    for(size_t i = 0; i < 6; i++) al_destroy_bitmap(enemy_sprite[i]);
    while(e->next != NULL) __destroy_enemie(e);
}