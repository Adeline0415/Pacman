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
#include "pacman_obj.h"

/* Internal Variables*/
static ALLEGRO_BITMAP* gameTitle = NULL;
static ALLEGRO_BITMAP* movesprite = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
static ALLEGRO_SAMPLE_ID menu2BGM;
static int gameTitleW ;
static int gameTitleH ;
static int off = 0;

// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first. 

//	[HACKATHON 3-1]
//	TODO: Declare variable for button
//	Uncomment and fill the code below
// static ... btnSettings;
static Button btnSettings;

static void init() {

	// [HACKATHON 3-2]
	// TODO: Create button to settings
	//	Uncomment and fill the code below
	btnSettings = button_create(730, 20, 50, 50, "Assets/settings.png", "Assets/settings2.png");
	gameTitle = load_bitmap("Assets/title.png");
	movesprite = load_bitmap("Assets/pacman_move.png");
	gameTitleW = al_get_bitmap_width(gameTitle);
	gameTitleH = al_get_bitmap_height(gameTitle);
	stop_bgm(menuBGM);
	if(music_one)menuBGM = play_bgm(themeMusic, music_volume);
	if(music_two)menu2BGM = play_bgm(theme2Music, music_volume);
	off = 0;
}


static void draw() {

	al_clear_to_color(al_map_rgb(7, 20, 30));
	char score_history_arr[60];
	sprintf(score_history_arr, "MAX SCORE:%d", max_score);
	const float scale = 0.7;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameTitleW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameTitleH;

	//draw title image
	al_draw_scaled_bitmap(
		gameTitle,
		0, 0,
		gameTitleW, gameTitleH,
		offset_w, offset_h,
		gameTitleW * scale, gameTitleH * scale,
		0
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"PRESS \"ENTER\""
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		SCREEN_H - 300,
		ALLEGRO_ALIGN_CENTER,
		score_history_arr
	);
	++off;
	al_draw_scaled_bitmap(movesprite, 16*((off/16)%2) , 0,
		16, 16,
		175, 270,
		60, 60, 0
	);
	al_draw_scaled_bitmap(movesprite, 16 * ((off / 16) % 2), 0,
		16, 16,
		275, 270,
		60, 60, 0
	);
	al_draw_scaled_bitmap(movesprite, 16 * ((off / 16) % 2), 0,
		16, 16,
		375, 270,
		60, 60, 0
	);
	al_draw_scaled_bitmap(movesprite, 16 * ((off / 16) % 2), 0,
		16, 16,
		475, 270,
		60, 60, 0
	);
	al_draw_scaled_bitmap(movesprite, 16 * ((off / 16) % 2), 0,
		16, 16,
		575, 270,
		60, 60, 0
	);

		// [HACKATHON 3-3]
		// TODO: Draw button
		// Uncomment and fill the code below
		drawButton(btnSettings);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btnSettings.hovered = pnt_in_rect( mouse_x, mouse_y, btnSettings.body);
}


//	[HACKATHON 3-8]
//	TODO: When btnSettings clicked, switch to settings scene
//  `game_change_scene` is defined in `game.h`.
//  You can check line 121 `scene_menu.c` to see how to use this function.
//  And find the corresponding function for `scene_setting`
// 	Utilize the member defined in struct `Button`.
//  The logic here is 
//  `if clicked the mouse` && `mouse position is in the area of button`
// 	      `Enter the setting scene`
//	Uncomment and fill the code below

static void on_mouse_down() {
	if (btnSettings.hovered)
		game_change_scene(scene_settings_create());
}


static void destroy() {
	if(music_one)stop_bgm(menuBGM);
	if (music_two)stop_bgm(menu2BGM);
	al_destroy_bitmap(gameTitle);
	//	[HACKATHON 3-10]
	//	TODO: Destroy button images
	//	Uncomment and fill the code below
	
	al_destroy_bitmap(btnSettings.default_img);
	al_destroy_bitmap(btnSettings.hovered_img);
	off = 0;
	
}

static void on_key_down(int keycode) {

	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_main_create());
			break;
		default:
			break;
	}
}

// TODO: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_menu_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
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