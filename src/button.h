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

#ifndef SGUI_BUTTON_H
#define SGUI_BUTTON_H

#include <stdint.h>
#include <SM/string.h>
#include "sprite.h"

typedef struct SGUI_Theme SGUI_Theme;
typedef struct SGUI_Menu SGUI_Menu;

#define SGUI_BUTTON_TEXT_INIT_SIZE 32

typedef struct SGUI_Button
{
	SGUI_Menu *menu;
	bool visible;
	bool active;
	SM_String text;
	SGUI_Sprite sprite;

	SDL_Rect rect;
	SDL_Color font_color;
	SDL_Color bg_color;
	SDL_Color border_color;
	SDL_Color disabled_color;

	void (*func_click) (void*);
	void *data_click;
} SGUI_Button ;

void SGUI_Button_new( SGUI_Button*, SGUI_Menu*, const SGUI_Theme* );

void SGUI_Button_update_sprite( SGUI_Button* );

void SGUI_Button_draw( SGUI_Button* );

#endif /* SGUI_BUTTON_H */
