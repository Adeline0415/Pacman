// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "share.h"
#include <string.h>
#include "utility.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "scene_menu.h"
#include "pacman_obj.h"
static Button exit_image;
static Button charactor_blue;
static Button charactor_yellow;
static Button charactor_pink;
static ALLEGRO_SAMPLE_ID menuBGM;
static ALLEGRO_SAMPLE_ID menu2BGM;
static ALLEGRO_BITMAP* one_ghost = NULL;
static ALLEGRO_BITMAP* one_pacman1 = NULL;
static ALLEGRO_BITMAP* one_pacman2 = NULL;
static ALLEGRO_BITMAP* one_pacman3 = NULL;
bool music_one = true;
bool music_two = false;
int x_stay = 400;
bool tap_in_volume = false;
bool charactor_one = true;
bool charactor_two = false;
bool charactor_three = false;

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.
extern ALLEGRO_SAMPLE_ID fireBGM;
/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static void init(void)
{
	exit_image = button_create(650, 630, 100, 100, "Assets/exit.png", "Assets/exit_2.png");
	one_ghost = load_bitmap("Assets/one_blue_ghost.png");
	one_pacman1 = load_bitmap("Assets/pacman_yellow.png");
	one_pacman2 = load_bitmap("Assets/pacman_blue.png");
	one_pacman3 = load_bitmap("Assets/pacman_pink.png");
	charactor_yellow= button_create(195, 580, 60, 60, "Assets/pacman_yellow_0.png", "Assets/pacman_yellow.png");
	charactor_pink = button_create(385, 580, 60, 60, "Assets/pacman_pink_0.png", "Assets/pacman_pink.png");
	charactor_blue = button_create(575, 580, 60, 60, "Assets/pacman_blue_0.png", "Assets/pacman_blue.png");
	tap_in_volume = false;
	stop_bgm(fireBGM);
	fireBGM = play_bgm(fireMusic, music_volume);
}
static void volume_control(void)
{
	if (mouse_x <= SCREEN_W-170 && mouse_x >= 170 && mouse_y <= 180 && mouse_y >= 165) {
		al_draw_filled_rectangle(170, 165, mouse_x, 180, al_map_rgb(151, 173, 172));
		al_draw_scaled_bitmap(one_ghost,0,0,16,16, mouse_x-5, 160, 30,30,0);
		tap_in_volume = true;
		x_stay = mouse_x;
	}
	if (tap_in_volume) {
		music_volume = (float)(x_stay - 170) / (630 - 170);
		effect_volume = (float)(x_stay - 170) / (630 - 170);
	}
}

static void music_select(void)
{
	if (mouse_x <= 300 && mouse_x >= 100 && mouse_y <= 395 && mouse_y >= 345)
	{
		al_draw_text(menuFont,
			al_map_rgb(177, 221, 223),
			200, 370,
			ALLEGRO_ALIGN_CENTER,
			"MUSIC ONE");
		music_two = false;
		music_one = true;
	}
	if (mouse_x <= SCREEN_W - 100 && mouse_x >= SCREEN_W - 300 && mouse_y <= 395 && mouse_y >= 345)
	{
		al_draw_text(menuFont,
			al_map_rgb(177, 221, 223),
			SCREEN_W - 200, 370,
			ALLEGRO_ALIGN_CENTER,
			"MUSIC TWO");
		music_one = false;
		music_two = true;
	}
}

static void draw(void ){
	al_clear_to_color(al_map_rgb(50, 50, 50));
	drawButton(exit_image);
	drawButton(charactor_yellow);
	drawButton(charactor_pink);
	drawButton(charactor_blue);
	al_draw_text(menuFont,
		al_map_rgb(200, 200, 200),
		SCREEN_W/2, 100,
		ALLEGRO_ALIGN_CENTER,
		"VOLUM CONTROL");
	al_draw_text(menuFont,
		al_map_rgb(200, 200, 200),
		SCREEN_W/2, 300,
		ALLEGRO_ALIGN_CENTER,
		"MUSIC SELECT");
	al_draw_text(menuFont,
		al_map_rgb(200, 200, 200),
		SCREEN_W / 2, 500,
		ALLEGRO_ALIGN_CENTER,
		"CHARACTOR SELECT");
	al_draw_text(menuFont,
		al_map_rgb(151, 173, 172),
		200, 370,
		ALLEGRO_ALIGN_CENTER,
		"MUSIC ONE");
	al_draw_text(menuFont,
		al_map_rgb(151, 173, 172),
		SCREEN_W-200, 370,
		ALLEGRO_ALIGN_CENTER,
		"MUSIC TWO");
	al_draw_text(menuFont,
		al_map_rgb(151, 173, 172),
		702.5, 735,
		ALLEGRO_ALIGN_CENTER,
		"EXIT");
	al_draw_filled_rectangle(170, 165,SCREEN_W-170, 180, al_map_rgb(0, 24, 44));
	volume_control();
	music_select();
	al_draw_filled_rectangle(170, 165, x_stay, 180, al_map_rgb(151, 173, 172));
	al_draw_scaled_bitmap(one_ghost,0,0,16,16, x_stay-5, 160, 30,30,0);
	if(charactor_one) al_draw_scaled_bitmap(one_pacman1, 0, 0, 16, 16, 195, 580, 60, 60, 0);
	if(charactor_two) al_draw_scaled_bitmap(one_pacman2, 0, 0, 16, 16, 575, 580, 60, 60, 0);
	if(charactor_three) al_draw_scaled_bitmap(one_pacman3, 0, 0, 16, 16, 385, 580, 60, 60, 0);
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) 
{
	exit_image.hovered = pnt_in_rect(mouse_x, mouse_y, exit_image.body);
	charactor_yellow.hovered = pnt_in_rect(mouse_x, mouse_y, charactor_yellow.body);
	charactor_blue.hovered = pnt_in_rect(mouse_x, mouse_y, charactor_blue.body);
	charactor_pink.hovered = pnt_in_rect(mouse_x, mouse_y, charactor_pink.body);
}
static void on_mouse_down() {
	if (exit_image.hovered)
		game_change_scene(scene_menu_create());
	if (charactor_yellow.hovered)
	{
		charactor_two = false;
		charactor_three = false;
		charactor_one = true;
	}
	if(charactor_blue.hovered)
	{
		charactor_one = false;
		charactor_three = false;
		charactor_two = true;
	}
	if (charactor_pink.hovered)
	{
		charactor_one = false;
		charactor_two = false;
		charactor_three = true;
	}
}

static void destroy(void)
{
	stop_bgm(fireBGM);
}
// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.initialize = &init;
	scene.name = "Settings";
	scene.draw = &draw;
	scene.destroy = &destroy;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_move = &on_mouse_move;
	game_log("Settings scene created");
	return scene;
}

