#include "enemie.h"

ALLEGRO_BITMAP *enemy_sprite[6];
Enemy enemies[MAX_ENEMIE_IN_SCREEN];

void init_enemies() {

    const char *paths[6] = {
        "assets/sprite/enemy/enemy_01.png",
        "assets/sprite/enemy/enemy_02.png",
        "assets/sprite/enemy/enemy_03.png",
        "assets/sprite/enemy/enemy_04.png",
        "assets/sprite/enemy/enemy_05.png",
        "assets/sprite/enemy/enemy_06.png"
    };

    // Inicializar sprites
    for(size_t i = 0; i < 6; i++)  enemy_sprite[i] = init_bitmap(paths[i]);

    for(size_t i = 0; i < MAX_ENEMIE_IN_SCREEN; i++) {
        enemies[i].actived = false;
        enemies[i].x = 0;
        enemies[i].y = 0;
        enemies[i].dx = 0;
        enemies[i].dy = 0;
        enemies[i].width = 100;
        enemies[i].height = 100;
        enemies[i].sprite = 0;
        enemies[i].delay = 0;
        enemies[i].time = 0;
    }
}

bool add_enemy(int e) {
    // Tenta encontrar um inimigo disponivel
    for(size_t i = 0; i < MAX_ENEMIE_IN_SCREEN; i++) {
        // Se nao estiver disponivel passa
        if(enemies[i].actived) continue;

        switch(e) {
            case 1:
                enemies[i].dx = 1.5;
                enemies[i].dy = 1.0;
                enemies[i].hp = ENEMIE_HP;
                enemies[i].delay = 0;;
                enemies[i].sprite = 0;
                break;
            case 2:
                enemies[i].dx = 1.0;
                enemies[i].dy = 0.5;
                enemies[i].hp = ENEMIE_HP;
                enemies[i].delay = 0;
                enemies[i].sprite = 1;
                break;
            case 3:
                enemies[i].dx = 1.0;
                enemies[i].dy = 0.5;
                enemies[i].hp = (ENEMIE_HP << 1);
                enemies[i].sprite = 2;
                break;
            case 4: // Inimigo: tank
                enemies[i].dx = 0.75;
                enemies[i].dy = 0.25;
                enemies[i].hp = (ENEMIE_HP + 2);
                enemies[i].delay = 0;
                enemies[i].sprite = 3;
                break;
            case 5: // Inimigo: sly
                enemies[i].dx = 0.5;
                enemies[i].dy = 1.5;
                enemies[i].hp = (ENEMIE_HP);
                enemies[i].delay = 50;
                enemies[i].sprite = 4;
                enemies[i].width = 92;
                break;
            case 6: // Inimigo: Scrap
                enemies[i].dx = (float)0.1;
                enemies[i].dy = (float)(3 + rand() % 2);
                enemies[i].hp = (ENEMIE_HP - 2);
                enemies[i].delay = 30;
                enemies[i].sprite = 5;
                enemies[i].width = 80;
                break;
            default:
                break;
        }

        enemies[i].x = (BUFFER_W + enemies[i].width);
        enemies[i].y = (float)(rand() % (BUFFER_H - (int)enemies[i].height));
        enemies[i].iced = false;
        enemies[i].time = 0;
        enemies[i].actived = true;

        return true; // Foi possivel colocar inimigo
    }

    return false; // Sem inimigo disponivel para ser colocado
}

void enemies_update(Player *player) {

    unsigned int EMEMY_FRAMES_DELAY = (unsigned int)(150 / mult);

    // Colocar mais inimigos na tela
    if(actualScreen == 4) {
        if((frames % EMEMY_FRAMES_DELAY) == 0)
            add_enemy(4 + (rand() % 3));
    }

    for(size_t i = 0; i < MAX_ENEMIE_IN_SCREEN; i++) {
        if(!enemies[i].actived) continue;

        // Verifica a vida do inimigo
        if(enemies[i].hp <= 0) { 
            (player->kills)++;
            enemies[i].actived = false; 
        }

        // Dano ao jogador (contato)
        if( (player->invincibility == 0) &&
            collide (player->x, player->y, 
                    (player->x + PLAYER_W), (player->y + PLAYER_H),
                    enemies[i].x, enemies[i].y,
                    (enemies[i].x + enemies[i].width), 
                    (enemies[i].y + enemies[i].height))) {
            (player->lifes)--;
            (player->invincibility) = 60;
            enemies[i].actived = false;
        }

        // Movimentacao do inimigo
        if((enemies[i].x + (enemies[i].width / 2)) > (player->x + (PLAYER_W >> 1))) {
            // Entrada com velocidade dobrada
            if((enemies[i].x + enemies[i].width) >= BUFFER_W)
                enemies[i].x -= 8;
            else enemies[i].x -= (enemies[i].dx * mult);
        }
        else enemies[i].x += (enemies[i].dx * mult);

        // Tipo especial de movimentacao
        if(enemies[i].sprite == 5) { 
            enemies[i].y += (enemies[i].dy * mult);

            if(enemies[i].y <= 0) {
                enemies[i].y = 0;
                enemies[i].dy *= (-1);
            } else if ((enemies[i].y + enemies[i].height) >= BUFFER_H) {
                enemies[i].y = (BUFFER_H - enemies[i].height);
                enemies[i].dy *= (-1);
            }

        } else {
            if((enemies[i].y + (enemies[i].height / 2) - 1) > (player->y + (PLAYER_H >> 1))) 
                enemies[i].y -= (enemies[i].dy * mult);
            else if ((enemies[i].y + (enemies[i].height / 2) + 1) < (player->y + (PLAYER_H >> 1))) 
                enemies[i].y += (enemies[i].dy * mult);
        }

        // Tiro do inimigo
        if(enemies[i].delay != 0) {
            if(enemies[i].time < enemies[i].delay) enemies[i].time++;
            else {
                if(enemies[i].sprite == 5)
                    enemy_shots_add(enemies[i].x, enemies[i].y, 3);
                else
                    enemy_shots_add(enemies[i].x, enemies[i].y, 4);
                enemies[i].time = 0;
            }
        }
    }
}

void enemies_draw(bool debug, ALLEGRO_FONT* font) {
    for(size_t i = 0; i < MAX_ENEMIE_IN_SCREEN; i++) {
        if(!enemies[i].actived) continue;
        al_draw_bitmap(enemy_sprite[(enemies[i].sprite)], 
                enemies[i].x, enemies[i].y, 
                0);
        if(debug) 
            al_draw_textf(font, al_map_rgb(255, 255, 255), 
                        (enemies[i].x + (enemies[i].width / 2)), 
                        (enemies[i].y + enemies[i].height), 
                        ALLEGRO_ALIGN_CENTER,
                        "%d", enemies[i].hp);
    }
}

void enemies_destroy() {
    for(size_t i = 0; i < 6; i++) al_destroy_bitmap(enemy_sprite[i]);
}

void draw_boss_warning(ALLEGRO_FONT* font, const char *boss) {
    if((mult >= 1.8) && ((mult <= 1.95))) {
        al_draw_textf(font, al_map_rgb(255, 255, 255), 
                        0, (BUFFER_H >> 1), 
                        ALLEGRO_ALIGN_LEFT,
                        "Se prepare! %s esta chegando!", boss);
    }
}