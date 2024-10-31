#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "auxiliar.h"
#include "player.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2

int main(void) {   

    init_all();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); // Tempo de atualizacao - FPS (Frames por segundo)
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); 
    ALLEGRO_FONT* font = al_load_ttf_font("assets/font/25_Sydnie.ttf", 15, ALLEGRO_ALIGN_LEFT); //NOW WE CAN CHOOSE SIZE
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN); // Tamanho da janelas
    
    // Inicializar sprites principais
    Player player = create_player(50.0, 50.0);
    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("assets/sound/0_music.opus", 2, 2048);
    init_test(music, "musica de fundo");
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(music, ((float) 0.01)); // Volume da musica
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());

    // Setar o nome e icone da janela
    ALLEGRO_BITMAP* icon = init_bitmap("assets/favicon.png");
    init_test(icon, "icone da janela");
    al_set_display_icon(disp, icon);
    al_set_window_title(disp, "Snow Impact");

    // Variaveis de ambiente
    ALLEGRO_EVENT event; // Eento atual
    unsigned char key[ALLEGRO_KEY_MAX]; // Teclas
    memset(key, 0, sizeof(key));

    // Registrar fonte de eventos (teclado, tela e tempo de atualizacao)
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool finished = false; // Diz se a execucao finalizou

    al_start_timer(timer); // Inicio do timer do jogo
    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        switch(event.type) {

            // Atualizacao de FRAME
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));

                if(key[ALLEGRO_KEY_UP])
                    movement_player(&player, 0.0, -1.0);
                if(key[ALLEGRO_KEY_RIGHT])
                    movement_player(&player, 1.0, 0.0);
                if(key[ALLEGRO_KEY_DOWN])
                    movement_player(&player, 0.0, 1.0);
                if(key[ALLEGRO_KEY_LEFT])
                    movement_player(&player, -1.0, 0.0);

                draw_player(player);
                al_draw_textf(font, al_map_rgb(120, 120, 120), 0, 0, 0, "x: %.2f, Y: %.2f", player.x, player.y);

                al_flip_display(); // Flipar para nova tela
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                finished = true;
                break;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    al_destroy_audio_stream(music);
    destroy_player(player);
    al_destroy_bitmap(icon);

    return 0;
}