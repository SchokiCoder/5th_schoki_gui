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

static const char PATH_FONT[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
static const uint32_t FONT_SIZE = 12;

static const char SPRITE_TEXT[] = "Sprite";
static const char LABEL_TEXT[] = "Label";
static const char BUTTON_TEXT[] = "Button";
static const char BUTTON_CLICK_TEXT[] = "yaaay";
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

static const int32_t BUTTON_X = 10;
static const int32_t BUTTON_Y = 50;

static const int32_t ENTRY0_X = 10;
static const int32_t ENTRY0_Y = 70;
static const int32_t ENTRY0_W = FONT_SIZE * 16;
static const int32_t ENTRY0_H = FONT_SIZE;

static const int32_t ENTRY1_X = 10 + FONT_SIZE * 16 + 10;
static const int32_t ENTRY1_Y = 70;
static const int32_t ENTRY1_W = FONT_SIZE * 16;
static const int32_t ENTRY1_H = FONT_SIZE;

void button_click(void *data)
{
	char *str = (char*) data;

	printf("%s\n", str);
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
	SGUI_Button button;
	SGUI_Entry entry0;
	SGUI_Entry entry1;

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

	sprite = SGUI_Sprite_from_text(renderer, SPRITE_TEXT, font, SGUI_THEME_DARK.label_font_color);

	rect_sprite.x = SPRITE_X;
    rect_sprite.y = SPRITE_Y;
    rect_sprite.w = sprite.surface->w;
	rect_sprite.h = sprite.surface->h;

	// make menu
	menu = SGUI_Menu_new(renderer, font, &SGUI_THEME_DARK);
	SGUI_Label_new(&label, &menu, &SGUI_THEME_DARK);
	SGUI_Button_new(&button, &menu, &SGUI_THEME_DARK);
	SGUI_Entry_new(&entry0, &menu, &SGUI_THEME_DARK);
	SGUI_Entry_new(&entry1, &menu, &SGUI_THEME_DARK);

	label.sprite = SGUI_Sprite_from_text(renderer, LABEL_TEXT, font, SGUI_THEME_DARK.label_font_color);
	button.sprite = SGUI_Sprite_from_text(renderer, BUTTON_TEXT, font, SGUI_THEME_DARK.button_font_color);

	strcpy(entry0.text, ENTRY0_TEXT);
	strcpy(entry1.text, ENTRY1_TEXT);

	entry0.sprite = SGUI_Sprite_from_text(renderer, entry0.text, font, SGUI_THEME_DARK.entry_font_color);
	entry1.sprite = SGUI_Sprite_from_text(renderer, entry1.text, font, SGUI_THEME_DARK.entry_font_color);

	menu.x = MENU_X;
	menu.y = MENU_Y;
	menu.w = MENU_W;
	menu.h = MENU_H;

	label.x = LABEL_X;
	label.y = LABEL_Y;
	label.w = label.sprite.surface->w;
	label.h = label.sprite.surface->h;

	button.x = BUTTON_X;
	button.y = BUTTON_Y;
	button.w = button.sprite.surface->w;
	button.h = button.sprite.surface->h;

	entry0.x = ENTRY0_X;
	entry0.y = ENTRY0_Y;
	entry0.w = ENTRY0_W;
	entry0.h = ENTRY0_H;

	entry1.x = ENTRY1_X;
	entry1.y = ENTRY1_Y;
	entry1.w = ENTRY1_W;
	entry1.h = ENTRY1_H;

	menu.visible = true;
	menu.active = true;

	button.func_click = button_click;
	button.data_click = (char*) BUTTON_CLICK_TEXT;

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
