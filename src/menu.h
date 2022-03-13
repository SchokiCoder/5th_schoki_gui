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

#ifndef SGUI_MENU_H
#define SGUI_MENU_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

typedef struct SGUI_Theme SGUI_Theme;
typedef struct SGUI_Label SGUI_Label;
typedef struct SGUI_Button SGUI_Button;
typedef struct SGUI_Entry SGUI_Entry;

#define SGUI_MENU_MAX_WIDGETS 16 /* per type */

typedef struct SGUI_Menu
{
	SDL_Renderer *renderer;
	TTF_Font *font;

	bool visible;
	bool active;

	uint8_t label_count;
	SGUI_Label *labels[SGUI_MENU_MAX_WIDGETS];

	uint8_t button_count;
	SGUI_Button *buttons[SGUI_MENU_MAX_WIDGETS];

	uint8_t focused_entry;
	uint8_t entry_count;
	SGUI_Entry *entries[SGUI_MENU_MAX_WIDGETS];

	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	SDL_Color bg_color;
} SGUI_Menu ;

SGUI_Menu SGUI_Menu_new( SDL_Renderer*, TTF_Font*, const SGUI_Theme* );

void SGUI_Menu_draw( SGUI_Menu* );

void SGUI_Menu_handle_events( SGUI_Menu*, SDL_Event* );

void SGUI_Menu_clear( SGUI_Menu* );

#endif /* SGUI_MENU_H */
