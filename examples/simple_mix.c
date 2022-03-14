/*
	schoki_gui
	Copyright (C) 2022	Andy Frank Schoknecht

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdbool.h>
#include "def_themes.h"
#include "menu.h"
#include "label.h"
#include "button.h"
#include "entry.h"
#include "sprite.h"

static const SGUI_Theme *TEST_THEME = &SGUI_THEME_DARK;

static const char PATH_FONT[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
static const uint32_t FONT_SIZE = 12;

static const char SPRITE_TEXT[] = "Sprite";
static const char LABEL_TEXT[] = "Label";
static const char BUTTON0_TEXT[] = "i toggle";
static const char BUTTON1_TEXT[] = "i am toggled";
static const char ENTRY0_TEXT[] = "e0";
static const char ENTRY1_TEXT[] = "e1";

static const int32_t MENU_X = 0;
static const int32_t MENU_Y = 0;
static const int32_t MENU_W = 640;
static const int32_t MENU_H = 480;

static const int32_t SPRITE_X = 10;
static const int32_t SPRITE_Y = 10;

static const int32_t LABEL_X = 10;
static const int32_t LABEL_Y = 30;

static const int32_t BUTTON0_X = 10;
static const int32_t BUTTON0_Y = 50;

static const int32_t BUTTON1_X = 70;
static const int32_t BUTTON1_Y = 50;

static const int32_t ENTRY0_X = 10;
static const int32_t ENTRY0_Y = 70;
static const int32_t ENTRY0_W = FONT_SIZE * 16;
static const int32_t ENTRY0_H = FONT_SIZE;

static const int32_t ENTRY1_X = 10 + FONT_SIZE * 16 + 10;
static const int32_t ENTRY1_Y = 70;
static const int32_t ENTRY1_W = FONT_SIZE * 16;
static const int32_t ENTRY1_H = FONT_SIZE;

struct Button0Data
{
	SGUI_Button *btn;
	SGUI_Entry *txt;
};

void button0_click(void *data)
{
	struct Button0Data *parsed_data = (struct Button0Data*) data;

	parsed_data->btn->active = !parsed_data->btn->active;
	parsed_data->txt->active = !parsed_data->txt->active;
}

void button1_click()
{
	printf("yaaay\n");
}

int main( void )
{
	bool active = true;
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *font;
	SDL_Event event;

	SGUI_Menu menu;
	SGUI_Sprite sprite = {.invalid = false};
	SDL_Rect rect_sprite;
	SGUI_Label label;
	SGUI_Button button0;
	SGUI_Button button1;
	SGUI_Entry entry0;
	SGUI_Entry entry1;
	struct Button0Data button0_data;

	// init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
    	printf("SDL could not initialize.");
    	return 1;
    }

    // init ttf
	if (TTF_Init() != 0)
	{
		printf("TTF could not initialize.");
    	return 1;
	}

	// create window and renderer
    window = SDL_CreateWindow(
    	"test",
    	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    	MENU_W, MENU_H,
    	SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    //sdl enable alpha blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // load font
	font = TTF_OpenFont(PATH_FONT, FONT_SIZE);

	if (font == NULL)
	{
		printf("Font not found.\n");
		return 1;
	}

	// make standalone sprite
	sprite = SGUI_Sprite_from_text(renderer, SPRITE_TEXT, font, SGUI_THEME_DARK.label_font_color);

	rect_sprite.x = SPRITE_X;
    rect_sprite.y = SPRITE_Y;
    rect_sprite.w = sprite.surface->w;
	rect_sprite.h = sprite.surface->h;

	// make menu
	menu = SGUI_Menu_new(renderer, font, TEST_THEME);
	SGUI_Label_new(&label, &menu, TEST_THEME);
	SGUI_Button_new(&button0, &menu, TEST_THEME);
	SGUI_Button_new(&button1, &menu, TEST_THEME);
	SGUI_Entry_new(&entry0, &menu, TEST_THEME);
	SGUI_Entry_new(&entry1, &menu, TEST_THEME);

	// make widget text sprites
	strcpy(label.text, LABEL_TEXT);
	SGUI_Label_update_sprite(&label);

	strcpy(button0.text, BUTTON0_TEXT);
	SGUI_Button_update_sprite(&button0);

	strcpy(button1.text, BUTTON1_TEXT);
	SGUI_Button_update_sprite(&button1);

	strcpy(entry0.text, ENTRY0_TEXT);
	SGUI_Entry_update_sprite(&entry0);

	strcpy(entry1.text, ENTRY1_TEXT);
	SGUI_Entry_update_sprite(&entry1);

	// set widget positions
	menu.x = MENU_X;
	menu.y = MENU_Y;
	menu.w = MENU_W;
	menu.h = MENU_H;

	label.x = LABEL_X;
	label.y = LABEL_Y;
	label.w = label.sprite.surface->w;
	label.h = label.sprite.surface->h;

	button0.x = BUTTON0_X;
	button0.y = BUTTON0_Y;
	button0.w = button0.sprite.surface->w;
	button0.h = button0.sprite.surface->h;

	button1.x = BUTTON1_X;
	button1.y = BUTTON1_Y;
	button1.w = button1.sprite.surface->w;
	button1.h = button1.sprite.surface->h;

	entry0.x = ENTRY0_X;
	entry0.y = ENTRY0_Y;
	entry0.w = ENTRY0_W;
	entry0.h = ENTRY0_H;

	entry1.x = ENTRY1_X;
	entry1.y = ENTRY1_Y;
	entry1.w = ENTRY1_W;
	entry1.h = ENTRY1_H;

	// set widget event functions
	button0_data.btn = &button1;
	button0_data.txt = &entry1;

	button0.func_click = button0_click;
	button0.data_click = &button0_data;

	button1.func_click = button1_click;

	// mainloop
    while (active)
    {
    	// handle events
		while (SDL_PollEvent(&event))
		{
			// menu events
			SGUI_Menu_handle_events(&menu, &event);

			// app events
			switch (event.type)
			{
			// window close
			case SDL_QUIT:
				active = false;
                break;
			}
		}

    	// draw sprite
    	SDL_RenderCopy(
			renderer,
			sprite.texture,
			NULL,
			&rect_sprite);

		// draw menu
		SGUI_Menu_draw(&menu);

		// show drawn image
		SDL_RenderPresent(renderer);
    }

    // quit SDL
    SDL_Quit();

    // quit TTF
    TTF_Quit();

    // clear sprites
    SGUI_Sprite_clear(&sprite);
    SGUI_Menu_clear(&menu);

	return 0;
}
