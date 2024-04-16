#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

extern game_main_Score;

static Button exit_image;
static ALLEGRO_SAMPLE_ID winBGM;
static void init(void)
{
	exit_image = button_create(650, 630, 100, 100, "Assets/exit.png", "Assets/exit_2.png");
	winBGM = play_bgm(winMusic, music_volume);
}

static void draw() {

	al_clear_to_color(al_map_rgb(30, 30, 30));

	const float scale = 0.7;
	static char score_win_arr[20];
	sprintf(score_win_arr, "YOUR SCORE IS:%d", game_main_Score);
	al_draw_text(
		menuFont,
		al_map_rgb(200, 200, 30),
		SCREEN_W / 2,
		150,
		ALLEGRO_ALIGN_CENTER,
		"YOU WIN!"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(200, 200, 30),
		SCREEN_W / 2,
		250,
		ALLEGRO_ALIGN_CENTER,
		score_win_arr
	);
	al_draw_text(menuFont,
		al_map_rgb(151, 173, 172),
		702.5, 735,
		ALLEGRO_ALIGN_CENTER,
		"EXIT");
	drawButton(exit_image);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f)
{
	exit_image.hovered = pnt_in_rect(mouse_x, mouse_y, exit_image.body);
}

static void on_mouse_down() {
	if (exit_image.hovered)
		game_change_scene(scene_menu_create());
}

static void destroy() {
	stop_bgm(winBGM);
	//	[HACKATHON 3-10]
	//	TODO: Destroy button images
	//	Uncomment and fill the code below
}

Scene scene_win_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_move = &on_mouse_move;
	// [HACKATHON 3-9]
	// 
	// : Register on_mouse_down.
	// Uncomment the code below.

	scene.on_mouse_down = &on_mouse_down;

	// -------------------------------------



	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Menu scene created");
	return scene;
}