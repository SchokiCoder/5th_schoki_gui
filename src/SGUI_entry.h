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
#include <SM_types.h>
#include <SM_string.h>
#include "SGUI_sprite.h"

typedef struct SGUI_Theme SGUI_Theme;
typedef struct SGUI_Menu SGUI_Menu;

#define SGUI_ENTRY_TEXT_INIT_SIZE 32

typedef struct SGUI_EntryStyle
{
	SDL_Color font_color;
    SDL_Color bg_color;
    SDL_Color border_color;
    SDL_Color disabled_color;
} SGUI_EntryStyle ;

typedef struct SGUI_Entry
{
	SGUI_Menu *menu;
	TTF_Font *font;
	bool visible;
	bool active;
	SM_String text;
	SGUI_Sprite *sprites;

	SDL_Rect rect;
	SGUI_EntryStyle style;
} SGUI_Entry ;

void SGUI_Entry_new( SGUI_Entry *entry, SGUI_Menu *menu, TTF_Font *font, const SGUI_EntryStyle style );

void SGUI_Entry_update_sprite( SGUI_Entry *entry, size_t pos );

void SGUI_Entry_update_sprites( SGUI_Entry *entry );

void SGUI_Entry_append( SGUI_Entry *entry, SM_String *appendage );

void SGUI_Entry_draw( SGUI_Entry *entry );

void SGUI_Entry_clear_sprites( SGUI_Entry *entry );

void SGUI_Entry_resize( SGUI_Entry *entry );

#endif /* SGUI_ENTRY_H */
