#include "bullet.h"

ALLEGRO_BITMAP *bullet_sprite[5];
Bullet shots[SHOTS_MAX];
unsigned int newBullet;
unsigned int delay;
Special special;

void shots_init() {

    const char *paths[] = {
        "assets/sprite/bullet/player_normal.png",
        "assets/sprite/bullet/player_explosion.png",
        "assets/sprite/bullet/player_ice.png",
        "assets/sprite/bullet/enemy_snowball_01.png",
        "assets/sprite/bullet/enemy_snowball_02.png"
    };

    for(size_t i = 0; i < 5; i++)
        bullet_sprite[i] = init_bitmap(paths[i]);
    
    newBullet = 0;
    delay = 0;

    for(size_t i = 0; i < SHOTS_MAX; i++) {
        shots[i].used = false;
        shots[i].dx = BULLET_SPEED;
        shots[i].dy = 0;
        shots[i].enemy = false;
        shots[i].x = 0;
        shots[i].y = 0;
    }

    // Inicializar poderes
    special.actived = false;
    special.get = false;
    special.dx = 4;
    special.height = 30;
    special.width = 30;
}

bool shots_add(float x, float y, ALLEGRO_SAMPLE* sample_shot) {
    al_play_sample(sample_shot, (float)0.3, 0, (float)1.5, 
                   ALLEGRO_PLAYMODE_ONCE, NULL);
    
    // Colocar o tiro na nave
    shots[newBullet].x = (x + (PLAYER_W >> 1) - (BULLET_W >> 1));
    shots[newBullet].y = (y + (PLAYER_H >> 1) - (BULLET_H >> 1));
    shots[newBullet].dx = (BULLET_SPEED);

    if(special.get) shots[newBullet].sprite = (special.sprite + 1);
    else shots[newBullet].sprite = 0;

    shots[newBullet].used = true;
    shots[newBullet].enemy = false;

    newBullet++;
    if (newBullet >= 128) newBullet = 0;

    return true;
}

void enemy_shots_add(float x, float y, size_t sprite) {
    // Colocar o tiro na nave
    shots[newBullet].x = (x + (ENEMY_BULLET_W >> 1));
    shots[newBullet].y = (y + (ENEMY_BULLET_H >> 1));

    shots[newBullet].sprite = sprite;

    shots[newBullet].used = true;
    shots[newBullet].enemy = true;
    shots[newBullet].dx = (-BULLET_SPEED);

    newBullet++;
    if (newBullet >= 128) newBullet = 0;
}

void update_shots(Player *player) {
    for(size_t i = 0; i < SHOTS_MAX; i++) {
        if(!shots[i].used) continue; // Se nao usado, nao renderiza
        
        // Arrumar posicao do tiro
        shots[i].x += shots[i].dx;
        shots[i].y += shots[i].dy;

        // Verifica se eh de aliado ou inimigo
        if(shots[i].enemy) {
            // Se chegar ao fim da tela (some)
            if(shots[i].x <= (-ENEMY_BULLET_W)) { 
                shots[i].used = false; 
                continue;
            }

            if((player->invincibility == 0) && 
                collide(shots[i].x, shots[i].y, 
                        (shots[i].x + ENEMY_BULLET_W), (shots[i].y + ENEMY_BULLET_H),
                        player->x, player->y, 
                        (player->x + PLAYER_W), (player->y + PLAYER_H))) {
                (player->lifes)--;
                shots[i].used = false;
                (player->invincibility) = 60;
            }

        } else {
            // Se chegar ao fim da tela (some)
            if(shots[i].x >= BUFFER_W) { 
                shots[i].used = false; 
                continue;
            }

            // Colisao com inimigos
            for(size_t j = 0; j < MAX_ENEMIE_IN_SCREEN; j++) {
                if(!enemies[j].actived) continue;

                if(collide( shots[i].x, shots[i].y, 
                            (shots[i].x + BULLET_W), (shots[i].y + BULLET_H),
                            enemies[j].x, enemies[j].y,
                            (enemies[j].x + enemies[j].width), 
                            (enemies[j].y + enemies[j].height))) {
                    
                    if (shots[i].sprite == 1)
                        enemies[j].hp -= (PLAYER_DAMAGE << 1);
                    else if ((!enemies[j].iced) && (shots[i].sprite == 2)) {
                        enemies[j].iced = true;
                        enemies[j].dx /= 2;
                        enemies[j].dy /= 2;
                        enemies[j].delay *= 2;
                        enemies[j].hp -= (PLAYER_DAMAGE);
                    }
                    else
                        enemies[j].hp -= (PLAYER_DAMAGE);
                    shots[i].used = false;
                }  
            }
        }
    }
}

void draw_shots() {
    for(size_t i = 0; i < SHOTS_MAX; i++) {
        if(!shots[i].used) continue; // Se nao usado, nao renderiza
        al_draw_bitmap(bullet_sprite[shots[i].sprite], shots[i].x, shots[i].y, 0);
    }
}

void update_special(Player player) {

    // Especial no mapa
    if(special.actived) {
        special.x -= special.dx;
        if((special.x + special.width) <= 0) special.actived = false;

        if(collide( special.x, special.y, 
                    (special.x + special.width), (special.y + special.height),
                    player.x, player.y,
                    (player.x + PLAYER_W), (player.y + PLAYER_H))) {
            special.get = true;
            special.actived = false;
        }

        return;
    }

    // Especial coletado
    if(special.get) {
        special.time -= (float)(1.0 / FRAMERATE);

        if(special.time <= 0) special.get = false;

        return;
    }

    // Especial para ser colocado no mapa

    if((frames % SPECIAL_DELAY) != 0) return;

    special.actived = true;
    special.get = false;

    special.x = (BUFFER_W);
    special.y = (float)(20 + (rand() % (BUFFER_H - 20)));

    if((rand() % 2) == 0) { // Explosivo
        special.sprite = 0;
        special.time = 2.0;
    }
    else {
        special.sprite = 1;
        special.time = 3.0;
    }

    special.sprite = (unsigned char)((unsigned char)rand() % 2);
}

void draw_special() {
    if(!special.actived) return;
    al_draw_bitmap(bullet_sprite[(special.sprite + 1)], special.x, special.y, 0);
}

void destroy_shots() {
    for(size_t i = 0; i < 5; i++) al_destroy_bitmap(bullet_sprite[i]);
}