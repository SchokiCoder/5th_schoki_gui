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

#ifndef SGUI_LABEL_H
#define SGUI_LABEL_H

#include <SM_types.h>
#include <SM_string.h>
#include "SGUI_sprite.h"

typedef struct SGUI_Theme SGUI_Theme;
typedef struct SGUI_Menu SGUI_Menu;

#define SGUI_LABEL_TEXT_INIT_SIZE 32

typedef struct SGUI_LabelStyle {
	SDL_Color font_color;
	SDL_Color bg_color;
	SDL_Color border_color;
} SGUI_LabelStyle;

typedef struct SGUI_Label {
	SGUI_Menu *menu;
	TTF_Font *font;
	bool visible;
	SM_String text;
	SGUI_Sprite sprite;

	SDL_Rect rect;
	SGUI_LabelStyle style;
} SGUI_Label;

void SGUI_Label_new(SGUI_Label * label,
		    SGUI_Menu * menu,
		    TTF_Font * font, const SGUI_LabelStyle style);

void SGUI_Label_update_sprite(SGUI_Label * label);

void SGUI_Label_draw(SGUI_Label * label);

void SGUI_Label_resize(SGUI_Label * label);

#endif				/* SGUI_LABEL_H */
