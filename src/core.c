#include "init.h"
#include "screen.h"
#include "bullet.h"
#include "player.h"

#include "keyboard.h"

int main(void) {   

    init_all();

    al_reserve_samples(128);
    ALLEGRO_SAMPLE* sample_shot = al_load_sample("assets/sound/5_sound_shoot.opus");
    init_test(sample_shot, "som dos tiros");

    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("assets/sound/0_music.opus", 2, 2048);
    init_test(music, "musica de fundo");
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(music, ((float) 0.01)); // Volume da musica
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FRAMERATE); // Tempo de atualizacao - FPS (Frames por segundo)
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); 
    ALLEGRO_FONT* font = al_load_ttf_font("assets/font/25_Sydnie.ttf", FONT_SIZE, ALLEGRO_ALIGN_LEFT); //NOW WE CAN CHOOSE SIZE

    // Eventos e teclados
    ALLEGRO_EVENT event; // Eento atual
    unsigned char key[ALLEGRO_KEY_MAX]; // Teclas
    memset(key, 0, sizeof(key));
    
    // Inicializar sprites principais
    Player player = create_player(50.0, 50.0);

    shots_init();

    display_init();

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

                display_pre_draw();

                al_clear_to_color(al_map_rgb(0, 0, 0));

                if(key[ALLEGRO_KEY_D]) debug = (!debug);
                if(key[ALLEGRO_KEY_P]) paused = (!paused);

                // Apenas atualiza o jogo quando nao tiver pausado
                if (!paused) {
                    update_player(&player, key, sample_shot);
                    shots_update();
                    update_status(player, font);
                } 

                draw_player(player);

                // Jogo pausado, desenha tela de pause
                if (paused) draw_pause(font);

                display_post_draw();

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

    // Destruir tudo alocado
    display_destroy();
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(sample_shot);
    al_destroy_audio_stream(music);
    destroy_player(&player);

    return 0;
}