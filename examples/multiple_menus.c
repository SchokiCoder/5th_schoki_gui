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

#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <SM_string.h>
#include <SGUI_def_themes.h>
#include <SGUI_menu.h>
#include <SGUI_label.h>
#include <SGUI_button.h>

static const SGUI_Theme *TEST_THEME = &SGUI_THEME_DARK;
static const char PATH_FONT[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
static const uint32_t FONT_SIZE = 12;

static const uint32_t WINDOW_W = 640;
static const uint32_t WINDOW_H = 480;

static const SGUI_MenuStyle MENU1_STYLE = {
	.bg_color = {
		.r = 10,
		.g = 55,
		.b = 10,
		.a = 255
	}
};

static const SGUI_MenuStyle MENU2_STYLE = {
	.bg_color = {
		.r = 10,
		.g = 10,
		.b = 55,
		.a = 255
	}
};

static const SDL_Rect MENU1_RECT = {
	.x = 0,
	.y = 0,
	.w = WINDOW_W,
	.h = WINDOW_H
};

static const char LABEL1_TEXT[] = "Menu 1";
static const SDL_Rect LABEL1_RECT = {
	.x = 20,
	.y = 20,
	.w = 0,
	.h = FONT_SIZE + 2
};

static const char BTN_GOTO1_TEXT[] = "goto Menu 2";
static const SDL_Rect BTN_GOTO1_RECT = {
	.x = 20,
	.y = 20 + (FONT_SIZE * 2) + 2,
	.w = 0,
	.h = FONT_SIZE + 2
};

static const char BTN_PRINT1_TEXT[] = "Print";
static const SDL_Rect BTN_PRINT1_RECT = {
	.x = 20,
	.y = 20 + (FONT_SIZE * 4) + 2,
	.w = 0,
	.h = FONT_SIZE + 2
};

static const SDL_Rect MENU2_RECT = {
	.x = 0,
	.y = 0,
	.w = WINDOW_W,
	.h = WINDOW_H
};

static const char LABEL2_TEXT[] = "Menu 2";
static const SDL_Rect LABEL2_RECT = {
	.x = 20,
	.y = 20,
	.w = 0,
	.h = FONT_SIZE + 2
};

static const char BTN_GOTO2_TEXT[] = "goto Menu 1";
static const SDL_Rect BTN_GOTO2_RECT = {
	.x = 20,
	.y = 20 + (FONT_SIZE * 2) + 2,
	.w = 0,
	.h = FONT_SIZE + 2
};

static const char BTN_PRINT2_TEXT[] = "Print";
static const SDL_Rect BTN_PRINT2_RECT = {
	.x = 20,
	.y = 20 + (FONT_SIZE * 4) + 2,
	.w = 0,
	.h = FONT_SIZE + 2
};

typedef struct BtnGotoData
{
	SGUI_Menu *menu1;
	SGUI_Menu *menu2;
} BtnGotoData ;

void btn_goto1_click( void *data_ptr )
{
	BtnGotoData *data = (BtnGotoData*) data_ptr;

	data->menu1->visible = false;
	data->menu2->visible = true;
}

void btn_goto2_click( void *data_ptr )
{
	BtnGotoData *data = (BtnGotoData*) data_ptr;

	data->menu1->visible = true;
	data->menu2->visible = false;
}

void btn_print1_click()
{
	printf("Menu 1 - print\n");
}

void btn_print2_click()
{
	printf("Menu 2 - print\n");
}

int main()
{
	bool active = true;
	SM_String temp;
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	SDL_Event event;

	SGUI_Menu menu1;
	SGUI_Label label1;
	SGUI_Button btn_goto1;
	SGUI_Button btn_print1;

	SGUI_Menu menu2;
	SGUI_Label label2;
	SGUI_Button btn_goto2;
	SGUI_Button btn_print2;

	BtnGotoData btngoto_data = {
		.menu1 = &menu1,
		.menu2 = &menu2
	};

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
    	WINDOW_W, WINDOW_H,
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

	// create menus
	menu1 = SGUI_Menu_new(renderer, TEST_THEME->menu);
	SGUI_Label_new(&label1, &menu1, font, TEST_THEME->label);
	SGUI_Button_new(&btn_goto1, &menu1, font, TEST_THEME->button);
	SGUI_Button_new(&btn_print1, &menu1, font, TEST_THEME->button);

	menu2 = SGUI_Menu_new(renderer, TEST_THEME->menu);
	SGUI_Label_new(&label2, &menu2, font, TEST_THEME->label);
	SGUI_Button_new(&btn_goto2, &menu2, font, TEST_THEME->button);
	SGUI_Button_new(&btn_print2, &menu2, font, TEST_THEME->button);

	// define menus
	menu1.rect = MENU1_RECT;
	menu1.style = MENU1_STYLE;

	temp = SM_String_contain(LABEL1_TEXT);
	SM_String_copy(&label1.text, &temp);
	SGUI_Label_update_sprite(&label1);
	label1.rect = LABEL1_RECT;
	label1.rect.w = label1.sprite.surface->w;

	temp = SM_String_contain(BTN_GOTO1_TEXT);
	SM_String_copy(&btn_goto1.text, &temp);
	SGUI_Button_update_sprite(&btn_goto1);
	btn_goto1.rect = BTN_GOTO1_RECT;
	btn_goto1.rect.w = btn_goto1.sprite.surface->w;

	temp = SM_String_contain(BTN_PRINT1_TEXT);
	SM_String_copy(&btn_print1.text, &temp);
	SGUI_Button_update_sprite(&btn_print1);
	btn_print1.rect = BTN_PRINT1_RECT;
	btn_print1.rect.w = btn_print1.sprite.surface->w;

	menu2.rect = MENU2_RECT;
	menu2.style = MENU2_STYLE;
	menu2.visible = false;

	temp = SM_String_contain(LABEL2_TEXT);
	SM_String_copy(&label2.text, &temp);
	SGUI_Label_update_sprite(&label2);
	label2.rect = LABEL2_RECT;
	label2.rect.w = label2.sprite.surface->w;

	temp = SM_String_contain(BTN_GOTO2_TEXT);
	SM_String_copy(&btn_goto2.text, &temp);
	SGUI_Button_update_sprite(&btn_goto2);
	btn_goto2.rect = BTN_GOTO2_RECT;
	btn_goto2.rect.w = btn_goto2.sprite.surface->w;

	temp = SM_String_contain(BTN_PRINT2_TEXT);
	SM_String_copy(&btn_print2.text, &temp);
	SGUI_Button_update_sprite(&btn_print2);
	btn_print2.rect = BTN_PRINT2_RECT;
	btn_print2.rect.w = btn_print2.sprite.surface->w;

	btn_goto1.func_click = btn_goto1_click;
	btn_goto1.data_click = &btngoto_data;

	btn_goto2.func_click = btn_goto2_click;
	btn_goto2.data_click = &btngoto_data;

	btn_print1.func_click = btn_print1_click;
	btn_print2.func_click = btn_print2_click;

	// mainloop
	while (active)
	{
		// handle events
		while (SDL_PollEvent(&event))
		{
			// menu events
			if (menu1.visible)
				SGUI_Menu_handle_events(&menu1, &event);
			else
				SGUI_Menu_handle_events(&menu2, &event);

			// app events
			switch (event.type)
			{
			// window close
			case SDL_QUIT:
				active = false;
                break;
			}
		}

		// draw menu
		SGUI_Menu_draw(&menu1);
		SGUI_Menu_draw(&menu2);

		// show drawn image
		SDL_RenderPresent(renderer);
	}

	// quit SDL
    SDL_Quit();

    // quit TTF
    TTF_Quit();

    // clear menus
    SGUI_Menu_clear(&menu1);
    SGUI_Menu_clear(&menu2);

	return 0;
}
