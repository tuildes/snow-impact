#include "bullet.h"

ALLEGRO_BITMAP *bullet_sprite[5];
Special special;

Bullet init_bullets() {

    // Pathfiles dos sprites dos tiros
    const char *paths[] = {
        // Tiros do proprio jogador
        "assets/sprite/player/shot.png",
        "assets/sprite/player/explosion.png",
        "assets/sprite/player/ice.png",

        // Tiros do inimigo
        "assets/sprite/enemy/snowball.png",
    };

    // Inicializar os bitmaps dos tiros
    for(size_t i = 0; i < 4; i++) bullet_sprite[i] = init_bitmap(paths[i]);
    
    Bullet bullets;
    bullets.next = NULL;

    return bullets;
}

void add_bullet(float x, float y, Bullet *bullets, size_t sprite) {

    // Tocar som de tiro

    Bullet *new;
    if((new = (Bullet *) malloc(sizeof(Bullet))) == NULL) return;

    new->next   = NULL;
    new->sprite = sprite;
    new->dy = 0;

    if(sprite < 3) { // Jogador
        new->dx = (BULLET_SPEED);
        new->x  = (x + (PLAYER_W >> 1) - (BULLET_W >> 2));
        new->y  = (y + (PLAYER_H >> 1) - (BULLET_H >> 1));
    } else { // Inimigo
        new->dx = -(BULLET_SPEED - 1);
        new->x  = (x  - (ENEMY_BULLET_W >> 2));
        new->y  = (y  - (ENEMY_BULLET_H >> 1));
    }

    // Colocar na lista
    Bullet *temp = bullets;
    while(temp->next != NULL) temp = temp->next;
    temp->next = new;
}

void destroy_bullet(Bullet *b) {
    Bullet *temp = b->next;

    if(b->next == NULL) return;

    b->next = b->next->next;
    
    free(temp);
}

void update_bullets(Bullet *bplayer, bool enemy, Player *player, 
                    Enemy *enemies, Boss *boss) {

    for(Bullet *temp = bplayer; temp->next != NULL; temp = temp->next) {
        // Arrumar posicao do tiro
        temp->next->x += temp->next->dx;
        temp->next->y += temp->next->dy;

        // Tiro do inimigo
        if(enemy) {
            if(temp->next->x >= BUFFER_W) {
                destroy_bullet(temp);
                if(temp->next == NULL) break;
                continue;
            }

            if((player->invincibility == 0) && 
                collide (temp->next->x, temp->next->y, 
                        (temp->next->x + ENEMY_BULLET_W), (temp->next->y + ENEMY_BULLET_H),
                        player->x, player->y, 
                        (player->x + PLAYER_W), (player->y + PLAYER_H))) {
                    damage_player(player);
                    destroy_bullet(temp);
                    if(temp->next == NULL) break;
                    continue;
            }

        // Tiro do jogador
        } else {
            if (temp->next->x <= 0) {
                destroy_bullet(temp);
                if(temp->next == NULL) break;
                continue;
            }

            if(boss->active && (boss->actualHp > 0)) {
                if(collide( temp->next->x, temp->next->y, 
                            (temp->next->x + BULLET_W), (temp->next->y + BULLET_H),
                            boss->x, boss->y,
                            (boss->x + boss->width), 
                            (boss->y + boss->height))) {
                    if (temp->next->sprite)
                        boss->actualHp -= (PLAYER_DAMAGE << 1);
                    else
                        boss->actualHp -= PLAYER_DAMAGE;
                    destroy_bullet(temp);
                    if(temp->next == NULL) break;
                    continue;
                }
            }

            for(Enemy *enemie = enemies->next; enemie != NULL; enemie = enemie->next) {
                if(enemie->sprite == 8) continue;

                if(collide( temp->next->x, temp->next->y, 
                            (temp->next->x + BULLET_W), (temp->next->y + BULLET_H),
                            enemie->x, enemie->y,
                            (enemie->x + enemie->width), 
                            (enemie->y + enemie->height))) {
                    
                    if (temp->next->sprite == 1)
                        enemie->hp -= (PLAYER_DAMAGE << 1);
                    else if ((!enemie->iced) && (temp->next->sprite == 2)) {
                        enemie->iced = true;
                        enemie->dx /= 2;
                        enemie->dy /= 2;
                        enemie->delay *= 2;
                        enemie->hp -= (PLAYER_DAMAGE);
                    }
                    else enemie->hp -= (PLAYER_DAMAGE);

                    destroy_bullet(temp);
                    if(temp->next == NULL) return;            
                }  
            }
        }
    }
}

void draw_bullets(Bullet *bplayer) {
    for(Bullet *temp = bplayer; temp->next != NULL; temp = temp->next)
        al_draw_bitmap(bullet_sprite[temp->next->sprite], 
                        temp->next->x, temp->next->y, 0);
}
void destroy_bullets(Bullet *bplayer) {
    while(bplayer->next != NULL) destroy_bullet(bplayer);
}

void destroy_sprites_bullets() {
    for(size_t i = 0; i < 4; i++) al_destroy_bitmap(bullet_sprite[i]);
}

// void update_special_bullets(Player player) {

//     // Especial no mapa
//     if(special.actived) {
//         special.x -= special.dx;
//         if((special.x + special.width) <= 0) special.actived = false;

//         if(collide( special.x, special.y, 
//                     (special.x + special.width), (special.y + special.height),
//                     player.x, player.y,
//                     (player.x + PLAYER_W), (player.y + PLAYER_H))) {
//             special.get = true;
//             special.actived = false;
//         }

//         return;
//     }

//     // Especial coletado
//     if(special.get) {
//         special.time -= (float)(1.0 / FRAMERATE);

//         if(special.time <= 0) special.get = false;

//         return;
//     }

//     // Especial para ser colocado no mapa

//     if((frames % SPECIAL_DELAY) != 0) return;

//     special.actived = true;
//     special.get = false;

//     special.x = (BUFFER_W);
//     special.y = (float)(20 + (rand() % (BUFFER_H - 20)));

//     if((rand() % 2) == 0) { // Explosivo
//         special.sprite = 0;
//         special.time = 2.0;
//     }
//     else {
//         special.sprite = 1;
//         special.time = 3.0;
//     }

//     special.sprite = (unsigned char)((unsigned char)rand() % 2);
// }

// void draw_special() {
//     if(!special.actived) return;
//     al_draw_filled_rectangle(special.x, special.y, 
//                             (special.x + special.width),
//                             (special.y + special.height),
//                             al_map_rgb(0, 0, 255));
// }