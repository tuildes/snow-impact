#include "init.h"
#include "keyboard.h"
#include "screen.h"
#include "player.h"
#include "bullet.h"
#include "levels.h"
#include "enemie.h"

int main(void) {

    /* Variaveis do projeto */
    ALLEGRO_TIMER* timer;               // Timer do jogo (FRAMEREATE)
    ALLEGRO_EVENT_QUEUE* queue;         // Fila de ações do jogo
    ALLEGRO_EVENT event;                // Evento atual
    unsigned char key[ALLEGRO_KEY_MAX]; // Teclado e inputs
    //              choose = 0;         // Opcao de MENU INICIAL
    unsigned int actualScreen = 4;      // Tela do jogo (menu como padrao)
    bool finished = false,              // Status da execucao do jogo
         paused = false,                // Status de pause do jogo
         debug  = false;                // Status de debug do jogo
    // ALLEGRO_SAMPLE* sample_shot;        // Sons
    // ALLEGRO_AUDIO_STREAM* music;        // Musica de fundo
    ALLEGRO_FONT *font;                 // Fonte do jogo
    Player player;                      // Jogador
    Enemy enemies;
    Bullet bulletsPlayer,               // Tiros do jogador
           bulletsEnemy;                // Tiros dos inimigos
    Background bg[PARALLAX_SIZE];
    ALLEGRO_BITMAP* crtFilter;          // Filtro de CRT

    /* Inicializaoes do projeto */
    init_all();
    queue           = al_create_event_queue(); 
    timer           = init_timer(FRAMERATE, queue);
    init_keyboard(key, queue);
    init_display(queue);
    player          = create_player(50, (BUFFER_H >> 1));
    font            = init_font("assets/font/average.ttf", FONT_SIZE);
    bulletsPlayer   = init_bullets();
    enemies         = init_enemies();
    bulletsEnemy    = init_bullets(); 
    crtFilter       = init_bitmap("assets/background/crtFilter.png");
    init_background(bg);

    /* Snow Impact propriamento dito */
    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) {
            pre_draw_display();
            keyboard_options(key, &paused, &debug);

            switch(actualScreen) {
                // Tela de inicio
                case 0: {
                    // draw_select_level(font, fontAlt, bg, temp, choose);
                    // update_select_level(key, &finished, choose, &player, bg);
                    break;
                }

                // Level 01 do jogo
                case 2:   
                    break;

                // Level 02 do jogo
                case 4:
                    // Apenas atualiza o jogo quando nao tiver pausado
                    if(!paused) {
                        update_bullets(&bulletsPlayer, false, &player, &enemies);
                        update_bullets(&bulletsEnemy, true, &player, &enemies);
                        update_player(&player, key, &bulletsPlayer);
                        update_background(bg);
                        update_enemies(&enemies, &player, &bulletsEnemy);
                        update_status();
                    }

                    draw_background(bg);
                    draw_bullets(&bulletsPlayer);
                    draw_bullets(&bulletsEnemy);
                    draw_player(player);
                    draw_enemies(&enemies, debug, font);
                    draw_status(player, font, debug);
                    if (paused) draw_pause(font);

                    break;
                default:
                    finished = true;
                    break;
            }

            al_draw_bitmap(crtFilter, 0, 0, 0); // Filtro
            post_draw_display();
            keyboard_mapping(key);
        }

        update_keyboard(key, event, &finished);
    }

    /* Desalocar tudo e destruir para finalizar o jogo */
    destroy_display();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    al_destroy_bitmap(crtFilter);
    destroy_background(bg);
    destroy_player(&player);
    destroy_bullets(&bulletsPlayer);
    destroy_enemies(&enemies);
    destroy_sprites_bullets();
    destroy_bullets(&bulletsEnemy);

    return 0;
}