#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

int main() {

	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY *Gamewindow = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *Event_Queue = NULL;
	ALLEGRO_TIMER *Timer = NULL;
	ALLEGRO_BITMAP *Square = NULL;
	ALLEGRO_BITMAP *Bouncer = NULL;
	ALLEGRO_BITMAP *Logo = NULL;
	
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	int Screen_Width = disp_data.width;
	int Screen_Height = disp_data.height;

	

	float Square_X = 20;
	float Square_Y = 395;

	float Bouncer_X = 800;
	float Bouncer_Y = 500;

	float Bouncer_Dx = -4.0, Bouncer_Dy = 4.0;

	bool Key[4] = { false, false, false, false };

	bool Re_Draw = true;
	bool Do_Exit = false;
	
	Logo = al_load_bitmap("Prism.png");

	Timer = al_create_timer(0.01);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	Gamewindow = al_create_display(Screen_Width, Screen_Height);
	//Gamewindow = al_create_display(1900, 900); //640 480   1900 900
	
	Event_Queue = al_create_event_queue();

	Square = al_create_bitmap(15, 110);
	al_set_target_bitmap(Square);
	al_clear_to_color(al_map_rgb(500, 0, 0));

	Bouncer = al_create_bitmap(15, 15);
	al_set_target_bitmap(Bouncer);
	al_clear_to_color(al_map_rgb(50, 510, 50));


	al_set_target_bitmap(al_get_backbuffer(Gamewindow));

	al_register_event_source(Event_Queue, al_get_display_event_source(Gamewindow));
	al_register_event_source(Event_Queue, al_get_timer_event_source(Timer));
	al_register_event_source(Event_Queue, al_get_keyboard_event_source());

	al_convert_mask_to_alpha(Logo, al_map_rgb(255, 255, 255));
	for (int i = 0; i < 50; i++) {
		al_draw_tinted_bitmap(Logo, al_map_rgba_f(0.01*i, 0.01*i, 0.01*i, 0.5), (Screen_Width / 2) - 250, (Screen_Height / 2) - 250, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		Sleep(100);
	}
	for (int i = 100; i > 0; i--) {
		al_draw_tinted_bitmap(Logo, al_map_rgba_f(0.01*i, 0.01*i, 0.01*i, 0.5), (Screen_Width / 2)- 250, (Screen_Height / 2)-250, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		Sleep(100);
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_rest(1);
	
	
	//al_rest(1);
	al_start_timer(Timer);
	while (!Do_Exit)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(Event_Queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			cout << Bouncer_Dx << ", " << Bouncer_Dy << endl;

			if (Bouncer_X < 0 || Bouncer_X > Screen_Width - 15) {
				Bouncer_Dx = -Bouncer_Dx;
			}
			if (Bouncer_Y < 0 || Bouncer_Y > Screen_Height - 15) {
				Bouncer_Dy = -Bouncer_Dy;
			}

			if (Bouncer_X < 0) {

				if (Bouncer_Dx > 1 && Bouncer_Dx < 10) {
					Bouncer_Dx = Bouncer_Dx;
				}
				else {
					Bouncer_Dx = Bouncer_Dx;
				}
				if (Bouncer_Dy > 1 && Bouncer_Dy < 10) {
					Bouncer_Dy = Bouncer_Dy;
				}
				else {
					Bouncer_Dy = Bouncer_Dy;
				}
			}
			Bouncer_X += Bouncer_Dx;
			Bouncer_Y += Bouncer_Dy;
			///////////////////////////////////////////////////////////////////////
			if (Key[0] && Square_Y >= 0) {
				Square_Y -= 4.0;
			}
			if (Key[1] && Square_Y <= Screen_Height - 110) {
				Square_Y += 4.0;
			}
			///////////////////////////////////////////////////////////////////////
			
			Re_Draw = true;
		}



		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				///////////////////////////////////////////////////////////////////////
			case ALLEGRO_KEY_W:
				Key[0] = true;
				break;
			case ALLEGRO_KEY_S:
				Key[1] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
				///////////////////////////////////////////////////////////////////////
			case ALLEGRO_KEY_W:
				Key[0] = false;
				break;
			case ALLEGRO_KEY_S:
				Key[1] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				Do_Exit = true;
				break;
			}
		}


		if (Re_Draw && al_is_event_queue_empty(Event_Queue)) {
			Re_Draw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(Square, Square_X, Square_Y, 0);

			al_draw_bitmap(Bouncer, Bouncer_X, Bouncer_Y, 0);

			al_flip_display();
		}
	}

	al_destroy_bitmap(Square);
	al_destroy_bitmap(Bouncer);
	al_destroy_timer(Timer);
	al_destroy_display(Gamewindow);
	al_destroy_event_queue(Event_Queue);

	return 0;
}
