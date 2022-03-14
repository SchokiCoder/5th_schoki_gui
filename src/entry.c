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

#include "theme.h"
#include "menu.h"
#include "entry.h"

void SGUI_Entry_new( SGUI_Entry *entry, SGUI_Menu *menu, const SGUI_Theme *theme )
{
	entry->menu = menu;
	entry->sprite = SGUI_Sprite_new();
	entry->text[0] = '\0';
	entry->visible = true;
	entry->active = true;
	entry->font_color = theme->entry_font_color;
	entry->bg_color = theme->entry_bg_color;
	entry->border_color = theme->entry_border_color;
	entry->disabled_color = theme->entry_disabled_color;

	menu->entries[menu->entry_count] = entry;
	menu->entry_count++;
}

void SGUI_Entry_update_sprite( SGUI_Entry *entry )
{
	SGUI_Sprite_clear(&entry->sprite);
	entry->sprite = SGUI_Sprite_from_text(
		entry->menu->renderer,
		entry->text,
		entry->menu->font,
		entry->font_color);
}

void SGUI_Entry_draw( SGUI_Entry *entry )
{
	SDL_Rect draw_target = {
		.x = entry->x,
		.y = entry->y,
		.w = entry->w,
		.h = entry->h
	};

	// draw bg
	SDL_SetRenderDrawColor(
		entry->menu->renderer,
		entry->bg_color.r,
		entry->bg_color.g,
		entry->bg_color.b,
		entry->bg_color.a);
	SDL_RenderFillRect(entry->menu->renderer, &draw_target);

	// draw border
	SDL_SetRenderDrawColor(
		entry->menu->renderer,
		entry->border_color.r,
		entry->border_color.g,
		entry->border_color.b,
		entry->border_color.a);
	SDL_RenderDrawRect(entry->menu->renderer, &draw_target);

	// draw text
	SDL_RenderCopy(
		entry->menu->renderer,
		entry->sprite.texture,
		NULL,
		&draw_target);

	// if disabled, draw disabled shade
	if (entry->active == false)
	{
		SDL_SetRenderDrawColor(
			entry->menu->renderer,
			entry->disabled_color.r,
			entry->disabled_color.g,
			entry->disabled_color.b,
			entry->disabled_color.a);
		SDL_RenderFillRect(entry->menu->renderer, &draw_target);
	}
}
