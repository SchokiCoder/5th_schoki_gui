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

#ifndef SGUI_BUTTON_H
#define SGUI_BUTTON_H

#include <SM_types.h>
#include <SM_string.h>
#include "SGUI_sprite.h"

typedef struct SGUI_Theme SGUI_Theme;
typedef struct SGUI_Menu SGUI_Menu;

#define SGUI_BUTTON_TEXT_INIT_SIZE 32

typedef struct SGUI_ButtonStyle {
	SDL_Color font_color;
	SDL_Color bg_color;
	SDL_Color border_color;
	SDL_Color disabled_color;
} SGUI_ButtonStyle;

typedef struct SGUI_Button {
	SGUI_Menu *menu;
	TTF_Font *font;
	bool visible;
	bool active;
	SM_String text;
	SGUI_Sprite sprite;

	SDL_Rect rect;
	SGUI_ButtonStyle style;

	void (*func_click)(void *);
	void *data_click;
} SGUI_Button;

void SGUI_Button_new(SGUI_Button * button, SGUI_Menu * menu, TTF_Font * font,
		     const SGUI_ButtonStyle style);

void SGUI_Button_update_sprite(SGUI_Button * button);

void SGUI_Button_draw(SGUI_Button * button);

void SGUI_Button_resize(SGUI_Button * button);

#endif				/* SGUI_BUTTON_H */
