#include "init.h"
#include "screen.h"
#include "bullet.h"
#include "player.h"
#include "levels.h"
#include "enemie.h"
#include "boss.h"

#include "keyboard.h"

int main(void) {   

    ALLEGRO_TIMER* timer;               // Timer do jogo (FRAMEREATE)
    ALLEGRO_EVENT_QUEUE* queue;         // Fila de ações do jogo
    ALLEGRO_EVENT event;                // Evento atual
    unsigned char key[ALLEGRO_KEY_MAX]; // Teclado e inputs
    bool finished = false,              // Status da execucao do jogo
         paused = false,                // Status de pause do jogo
         debug  = false;                // Status de debug do jogo

    ALLEGRO_SAMPLE* sample_shot;    // Sons
    ALLEGRO_AUDIO_STREAM* music;    // Musica de fundo
    ALLEGRO_FONT *fontAlt, *font;   // Fontes
    Player player;                  // Jogador
    Boss boss;                      // Chefao de cada fase
    Background bg[PARALLAX_SIZE];   // Background do jogo
    ALLEGRO_BITMAP *temp = NULL, 
                   *temp2 = NULL;
    unsigned char choose = 0;

    init_all();

    sample_shot = init_sample("assets/sound/5_sound_shoot.opus");
    music = init_music();
    queue = al_create_event_queue(); 
    fontAlt = init_font("assets/font/minecraft.ttf", FONT_SIZE_TITLE);
    font = init_font("assets/font/sydnie.ttf", FONT_SIZE);
    player = create_player(-50.0, (BUFFER_H >> 1));

    boss = init_boss(0);

    init_background(bg);
    init_bullets();
    init_enemies();
    init_display(queue);
    init_keyboard(key, queue);

    init_select_level(&temp, &temp2);
    timer = init_timer(FRAMERATE, queue);

    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) {
            pre_draw_display();
            keyboard_options(key, &paused, &debug, &choose);

            switch(actualScreen) {
                // Tela de inicio
                case 0: {
                    draw_select_level(font, fontAlt, bg, temp, choose);
                    update_select_level(key, &finished, choose, &player, bg);
                    break;
                }

                // Level 01 do jogo
                case 2:   
                    break;

                // Level 02 do jogo
                case 4:
                    // Apenas atualiza o jogo quando nao tiver pausado
                    if (!paused) {
                        update_bullets(&player, &boss);
                        update_player(&player, key, sample_shot);
                        update_enemies(&player, sample_shot);
                        update_status();
                        update_background(bg);
                        update_special_bullets(player);
                        update_boss(&boss);
                    } 

                    draw_background(bg);
                    draw_enemies(debug, font);
                    draw_bullets();
                    draw_player(player);
                    draw_boss(boss);
                    draw_special();
                    draw_status(player, font, debug);
                    if (paused) draw_pause(fontAlt);

                    break;
                default:
                    finished = true;
                    break;
            }

            post_draw_display();
            keyboard_mapping(key);
        }

        update_keyboard(key, event, &finished);
    }

    // Destruir tudo alocado
    al_destroy_font(font);
    al_destroy_font(fontAlt);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(sample_shot);
    al_destroy_audio_stream(music);
    al_destroy_bitmap(temp);
    al_destroy_bitmap(temp2);

    destroy_display();
    destroy_background(bg);
    destroy_player(&player);
    destroy_bullets();
    destroy_enemies();

    return 0;
}