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

#ifndef SGUI_ENTRY_H
#define SGUI_ENTRY_H

#include <stdbool.h>
#include <stdint.h>
#include "sprite.h"

typedef struct SGUI_Theme SGUI_Theme;
typedef struct SGUI_Menu SGUI_Menu;

#define SGUI_ENTRY_MAX_TEXT_LEN 64

typedef struct SGUI_Entry
{
	SGUI_Menu *menu;

	bool visible;
	bool active;
	char text[SGUI_ENTRY_MAX_TEXT_LEN];
	SGUI_Sprite sprite;

	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	SDL_Color font_color;
	SDL_Color bg_color;
	SDL_Color border_color;
} SGUI_Entry ;

void SGUI_Entry_new( SGUI_Entry*, SGUI_Menu*, const SGUI_Theme* );

void SGUI_Entry_draw( SGUI_Entry* );

#endif /* SGUI_ENTRY_H */
