#include "init.h"
#include "keyboard.h"
#include "screen.h"
#include "player.h"

int main(void) {

    /* Variaveis do projeto */
    ALLEGRO_TIMER* timer;               // Timer do jogo (FRAMEREATE)
    ALLEGRO_EVENT_QUEUE* queue;         // Fila de ações do jogo
    ALLEGRO_EVENT event;                // Evento atual
    unsigned char key[ALLEGRO_KEY_MAX]; // Teclado e inputs
    //              choose = 0;           // Opcao de MENU INICIAL
    bool finished = false;              // Status da execucao do jogo
    //     paused = false,                // Status de pause do jogo
    //     debug  = false;                // Status de debug do jogo
    // ALLEGRO_SAMPLE* sample_shot;        // Sons
    // ALLEGRO_AUDIO_STREAM* music;        // Musica de fundo
    // ALLEGRO_FONT *font;                 // Fonte do jogo
    Player player;                      // Jogador

    /* Inicializaoes do projeto */
    init_all();
    queue = al_create_event_queue(); 
    timer = init_timer(FRAMERATE, queue);
    player = create_player(50, (BUFFER_H >> 1));
    init_display(queue);
    init_keyboard(key, queue);

    /* Snow Impact propriamento dito */
    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER) {
            pre_draw_display();
            // keyboard_options(key, &paused, &debug, &choose);

            update_player(&player, key);
            draw_player(player);

            // switch(actualScreen) {
            //     // Tela de inicio
            //     case 0: {
            //         draw_select_level(font, fontAlt, bg, temp, choose);
            //         update_select_level(key, &finished, choose, &player, bg);
            //         break;
            //     }

            //     // Level 01 do jogo
            //     case 2:   
            //         break;

            //     // Level 02 do jogo
            //     case 4:
            //         // Apenas atualiza o jogo quando nao tiver pausado
            //         if (!paused) {
            //             update_bullets(&player, &boss);
            //             update_player(&player, key, sample_shot);
            //             update_enemies(&player, sample_shot);
            //             update_status();
            //             update_background(bg);
            //             update_special_bullets(player);
            //             update_boss(&boss);
            //         } 

            //         draw_background(bg);
            //         draw_enemies(debug, font);
            //         draw_bullets();
            //         draw_player(player);
            //         draw_boss(boss);
            //         draw_special();
            //         draw_status(player, font, debug);
            //         if (paused) draw_pause(fontAlt);

            //         break;
            //     default:
            //         finished = true;
            //         break;
            // }

            post_draw_display();
            keyboard_mapping(key);
        }

        update_keyboard(key, event, &finished);
    }

    // Destruir tudo alocado
    // al_destroy_font(font);
    // al_destroy_font(fontAlt);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    // al_destroy_sample(sample_shot);
    // al_destroy_audio_stream(music);

    destroy_display();
    // destroy_background(bg);
    // destroy_player(&player);
    // destroy_bullets();
    // destroy_enemies();

    return 0;
}