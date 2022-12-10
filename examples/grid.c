/*
 * schoki_gui
 * Copyright (C) 2022  Andy Frank Schoknecht
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not see
 * <https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html>.
 */

#include "SGUI_def_themes.h"
#include "SGUI_menu.h"
#include "SGUI_label.h"
#include "SGUI_button.h"
#include "SGUI_entry.h"
#include "SGUI_sprite.h"

static const SGUI_Theme *TEST_THEME = &SGUI_THEME_DARK;
static const char PATH_FONT[] =
    "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
static const u32 FONT_SIZE = 12;

static const int32_t MENU_X = 0;
static const int32_t MENU_Y = 0;
static const int32_t MENU_W = 640;
static const int32_t MENU_H = 480;

static const u32 USER_COUNT = 3;
static const char USERS[][10] = {
	"Otis",
	"Barney",
	"Adrian",
};

int main(void)
{
	bool active = true;
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *font;
	SDL_Event event;

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL could not initialize.");
		return 1;
	}
	// init ttf
	if (TTF_Init() != 0) {
		printf("TTF could not initialize.");
		return 1;
	}
	// create window and renderer
	window = SDL_CreateWindow("test",
				  SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED, MENU_W, MENU_H,
				  SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//sdl enable alpha blending
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// load font
	font = TTF_OpenFont(PATH_FONT, FONT_SIZE);

	if (font == NULL) {
		printf("Font not found.\n");
		return 1;
	}

	SGUI_Menu mnu_users;
	SGUI_Label lbl_title;
	char temp[4] = "";
	SGUI_Label lbl_userid[USER_COUNT];
	SGUI_Entry txt_name[USER_COUNT];
	SGUI_Button btn_delete[USER_COUNT];

	// make widgets
	mnu_users = SGUI_Menu_new(renderer, TEST_THEME->menu);
	SGUI_Label_new(&lbl_title, &mnu_users, font, TEST_THEME->label);

	// set menu positions
	mnu_users.rect.x = MENU_X;
	mnu_users.rect.y = MENU_Y;
	mnu_users.rect.w = MENU_W;
	mnu_users.rect.h = MENU_H;

	// set title label
	SM_String_copy_cstr(&lbl_title.text, "Users");
	SGUI_Label_update_sprite(&lbl_title);

	lbl_title.rect.x = 0;
	lbl_title.rect.y = 0;
	SGUI_Label_resize(&lbl_title);

	for (usize i = 0; i < USER_COUNT; i++) {
		// make table widgets
		SGUI_Label_new(&lbl_userid[i], &mnu_users, font,
			       TEST_THEME->label);
		SGUI_Entry_new(&txt_name[i], &mnu_users, font,
			       TEST_THEME->entry);
		SGUI_Button_new(&btn_delete[i], &mnu_users, font,
				TEST_THEME->button);

		// make table text sprites
		sprintf(temp, "%lu", i);
		SM_String_copy_cstr(&lbl_userid[i].text, temp);
		SGUI_Label_update_sprite(&lbl_userid[i]);

		SM_String_copy_cstr(&txt_name[i].text, USERS[i]);
		SGUI_Entry_update_sprites(&txt_name[i]);

		SM_String_copy_cstr(&btn_delete[i].text, "Delete");
		SGUI_Button_update_sprite(&btn_delete[i]);

		// set table widgets position
		lbl_userid[i].rect.x = i;
		lbl_userid[i].rect.y = 2;
		SGUI_Label_resize(&lbl_userid[i]);

		txt_name[i].rect.x = i;
		txt_name[i].rect.y = 3;
		txt_name[i].rect.w = FONT_SIZE * 10;
		txt_name[i].rect.h = FONT_SIZE;

		btn_delete[i].rect.x = i;
		btn_delete[i].rect.y = 4;
		SGUI_Button_resize(&btn_delete[i]);
	}

	// make grid
	SGUI_Menu_grid(&mnu_users);

	// mainloop
	while (active) {
		// handle events
		while (SDL_PollEvent(&event)) {
			// menu events
			SGUI_Menu_handle_event(&mnu_users, &event);

			// app events
			switch (event.type) {
				// window close
			case SDL_QUIT:
				active = false;
				break;
			}
		}

		// draw menu
		SGUI_Menu_draw(&mnu_users);

		// show drawn image
		SDL_RenderPresent(renderer);
	}

	// quit SDL
	SDL_Quit();

	// quit TTF
	TTF_Quit();

	return 0;
}
