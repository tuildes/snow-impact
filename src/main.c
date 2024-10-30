#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define X_SCREEN 600
#define Y_SCREEN 450

// https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace-%E2%80%93-Basic-game-structure

int main(void) {

    al_init(); // Display inicial do allego
    al_install_keyboard(); // Instalacao e uso do teclado
    al_init_font_addon(); //WE NEED TO INIT FONT FIRST!
    al_init_ttf_addon(); //THEN WE NEED TO INIT TTF FONTS

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 5.0); // Tempo de atualizacao - FPS (Frames por segundo)
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); 

    al_init_font_addon(); //WE NEED TO INIT FONT FIRST!
    al_init_ttf_addon(); //THEN WE NEED TO INIT TTF FONTS
    ALLEGRO_FONT* font = al_load_ttf_font("assets/font/25_Sydnie.ttf", 25, ALLEGRO_ALIGN_LEFT); //NOW WE CAN CHOOSE SIZE

    // ALLEGRO_FONT* font = al_create_builtin_font(); // Fonte do sistema
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN); // Tamanho da janela

    // Frequencia de dados e uma frequencia de tela

    // Inicializar sprite
    if(!al_init_image_addon()) {
        printf("couldn't initialize image addon\n");
        return 1;
    }

    ALLEGRO_BITMAP* player = al_load_bitmap("assets/sprite/player_idle.png");
    if(!player) {
        printf("couldn't load player\n");
        return 1;
    }

    al_set_display_icon(disp, player);

    // Registrar fonte de eventos (teclado, tela e tempo de atualizacao)
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer); // Inicio do timer do jogo

    while(true) { // Loop de jogo
        al_wait_for_event(queue, &event);

        if (event.type == 30) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // for(int j = 1; j <= i; j++)
            al_draw_bitmap(player, 0, 0, 0);

            al_draw_text(font, al_map_rgb(255, 255, 255), (X_SCREEN >> 1), (Y_SCREEN >> 1), ALLEGRO_ALIGN_CENTRE, "Press ENTER to Continue!");
            al_flip_display(); // Flipar para nova tela
        }

        // Clicar para sair
        else if(event.type == 42) break; 
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(player);

    return 0;
}