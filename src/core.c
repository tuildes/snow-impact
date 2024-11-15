#include "init.h"
#include "screen.h"
#include "bullet.h"
#include "player.h"
#include "levels.h"

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
    Background bg[PARALLAX_SIZE];   // Background do jogo
    ALLEGRO_BITMAP *temp = NULL, 
                   *temp2 = NULL;

    init_all();

    sample_shot = init_sample("assets/sound/5_sound_shoot.opus");
    music = init_music();
    queue = al_create_event_queue(); 
    fontAlt = init_font("assets/font/minecraft.ttf", FONT_SIZE_TITLE);
    font = init_font("assets/font/sydnie.ttf", FONT_SIZE);
    
    // Inicializar sprites principais
    player = create_player(-50.0, (BUFFER_H >> 1));

    init_background(bg);
    shots_init();
    display_init(queue);
    keyboard_init(key, queue);

    init_select_level(&temp, &temp2);
    unsigned char choose = 0;

    timer = init_timer(FRAMERATE, queue);
    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) {
            display_pre_draw();

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
                    // Apenas atualiza o jogo quando nao tiver pausado
                    if (!paused) {
                        update_shots();
                        update_player(&player, key, sample_shot);
                        update_status();
                        update_background(bg);
                    } 

                    draw_background(bg);
                    draw_shots();
                    draw_player(player);
                    draw_status(player, font, debug);
                    if (paused) draw_pause(fontAlt);

                    break;
                default:
                    finished = true;
                    break;
            }

            display_post_draw();
            keyboard_mapping(key);
        }

        keyboard_update(key, event, &finished);
    }

    // Destruir tudo alocado
    display_destroy();
    al_destroy_font(font);
    al_destroy_font(fontAlt);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(sample_shot);
    al_destroy_audio_stream(music);
    al_destroy_bitmap(temp);
    al_destroy_bitmap(temp2);
    destroy_background(bg);
    destroy_player(&player);

    return 0;
}