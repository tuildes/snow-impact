#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define X_SCREEN 960 // 16 * 60
#define Y_SCREEN 540 // 9 * 60

#define KEY_SEEN     1
#define KEY_RELEASED 2

// https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace-%E2%80%93-Basic-game-structure
void init_test(bool b, const char *n) {
    if(b) return;

    printf("Não foi possivel inicializar %s.\n", n);
    exit(1);
}

ALLEGRO_BITMAP* init_bitmap(const char *local) {

    ALLEGRO_BITMAP* bm = al_load_bitmap(local);

    if (!bm) {
        printf("Não foi possível inicializar imagem: (%s)\n", local);
        exit(1);
    }

    return bm;
}

int main(void) {   

    init_test(al_init(), "Allegro"); // Inicializacao do allegro
    init_test(al_install_keyboard(), "teclado");
    init_test(al_init_font_addon(), "addon de font");
    init_test(al_init_ttf_addon(), "addon de ttf");
    init_test(al_init_image_addon(), "addon de imagens");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 15.0); // Tempo de atualizacao - FPS (Frames por segundo)
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); 
    ALLEGRO_FONT* font = al_load_ttf_font("assets/font/25_Sydnie.ttf", 25, ALLEGRO_ALIGN_LEFT); //NOW WE CAN CHOOSE SIZE
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN); // Tamanho da janelas
    
    // Inicializar sprites principais
    ALLEGRO_BITMAP* player = init_bitmap("assets/sprite/player_idle.png");
    ALLEGRO_BITMAP* icon = init_bitmap("assets/favicon.png");

    // Variaveis de ambiente
    ALLEGRO_EVENT event; // Eento atual
    unsigned char key[ALLEGRO_KEY_MAX]; // Teclas
    bool finished = false; // Diz se a execucao finalizou

    // Setar o nome e icone da janela
    al_set_display_icon(disp, icon);
    al_set_window_title(disp, "Snow Impact");

    // Registrar fonte de eventos (teclado, tela e tempo de atualizacao)
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Inicializar variaveis de execucao
    al_start_timer(timer); // Inicio do timer do jogo

    float x = 0, y = 0;
    float speed = 10;

    while(!finished) { // Loop de jogo
        al_wait_for_event(queue, &event);

        switch(event.type) {

            // Atualizacao de FRAME
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_UP])
                    y -= speed;
                if(key[ALLEGRO_KEY_DOWN])
                    y += speed;
                if(key[ALLEGRO_KEY_LEFT])
                    x -= speed;
                if(key[ALLEGRO_KEY_RIGHT])
                    x += speed;

                al_clear_to_color(al_map_rgb(0, 0, 0));
                // for(int j = 1; j <= i; j++)
                al_draw_bitmap(player, x, y, 0);

                al_draw_text(font, al_map_rgb(255, 255, 255), (X_SCREEN >> 1), (Y_SCREEN >> 1), ALLEGRO_ALIGN_CENTRE, "Press ENTER to Continue!");
                al_flip_display(); // Flipar para nova tela

                if(key[ALLEGRO_KEY_ESCAPE])
                    finished = true;

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
    
    al_destroy_bitmap(player);
    al_destroy_bitmap(icon);

    return 0;
}