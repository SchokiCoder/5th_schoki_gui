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
#include "menu.h"
#include "label.h"
#include "button.h"
#include "sprite.h"

static const char SPRITE_TEXT[] = "Sprite";
static const char LABEL_TEXT[] = "Label";
static const char BUTTON_TEXT[] = "Button";
static const char BUTTON_CLICK_TEXT[] = "yaaay";

static const int32_t SPRITE_X = 10;
static const int32_t SPRITE_Y = 10;

static const int32_t LABEL_X = 10;
static const int32_t LABEL_Y = 30;

static const int32_t BUTTON_X = 10;
static const int32_t BUTTON_Y = 50;

static const char PATH_FONT[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
static const uint32_t FONT_SIZE = 12;
static const SDL_Color FONT_COLOR = {
	.r = 0,
	.g = 0,
	.b = 0,
	.a = 255
};

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
    	640, 480,
    	SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    // load font
	font = TTF_OpenFont(PATH_FONT, FONT_SIZE);

	if (font == NULL)
	{
		printf("Font not found.\n");
		return 1;
	}

    // make sprite
	sprite = SGUI_sprite_from_text(renderer, SPRITE_TEXT, font, FONT_COLOR);

	rect_sprite.x = SPRITE_X;
    rect_sprite.y = SPRITE_Y;
    rect_sprite.w = sprite.surface->w;
	rect_sprite.h = sprite.surface->h;

	// make menu
	menu = SGUI_Menu_new();
	label = SGUI_Label_new();
	button = SGUI_Button_new();

	label.sprite = SGUI_sprite_from_text(renderer, LABEL_TEXT, font, FONT_COLOR);
	button.sprite = SGUI_sprite_from_text(renderer, BUTTON_TEXT, font, FONT_COLOR);

	label.visible = true;
	button.visible = true;
	button.active = true;

	label.x = LABEL_X;
	label.y = LABEL_Y;
	label.w = label.sprite.surface->w;
	label.h = label.sprite.surface->h;

	button.x = BUTTON_X;
	button.y = BUTTON_Y;
	button.w = button.sprite.surface->w;
	button.h = button.sprite.surface->h;

	menu.visible = true;
	menu.active = true;

	menu.labels[0] = &label;
	menu.label_count++;

	menu.buttons[0] = &button;
	menu.button_count++;

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

		// draw background
    	SDL_SetRenderDrawColor(renderer, 155, 219, 245, 255);
    	SDL_RenderClear(renderer);

    	// draw sprite
    	SDL_RenderCopy(
			renderer,
			sprite.texture,
			NULL,
			&rect_sprite);

		// draw menu
		SGUI_Menu_draw(&menu, renderer);

		// show drawn image
		SDL_RenderPresent(renderer);
    }

    // quit SDL
    SDL_Quit();

    // quit TTF
    TTF_Quit();

    // clear sprites
    SGUI_clear_sprite(&sprite);

	return 0;
}
