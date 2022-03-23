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

#include "SGUI_theme.h"
#include "SGUI_menu.h"
#include "SGUI_entry.h"

void SGUI_Entry_new( SGUI_Entry *entry, SGUI_Menu *menu, const SGUI_Theme *theme )
{
	entry->menu = menu;

	for (uint_fast8_t i = 0; i < SGUI_ENTRY_MAX_SHOWN_TEXT; i++)
		entry->sprites[i] = SGUI_Sprite_new();

	entry->text = SM_String_new(SGUI_ENTRY_TEXT_INIT_SIZE);
	entry->visible = true;
	entry->active = true;
	entry->font_color = theme->entry_font_color;
	entry->bg_color = theme->entry_bg_color;
	entry->border_color = theme->entry_border_color;
	entry->disabled_color = theme->entry_disabled_color;

	menu->entries[menu->entry_count] = entry;
	menu->entry_count++;
}

void SGUI_Entry_update_sprite( SGUI_Entry *entry, size_t pos )
{
	// stop if sprite doesn't exist
	if (pos > (SGUI_ENTRY_MAX_SHOWN_TEXT - 1))
		return;

	char letter[2] = {
		[0] = entry->text.str[pos],
		[1] = '\0'
	};

	// clear
	SGUI_Sprite_clear(&entry->sprites[pos]);

	// generate sprite of that letter
	entry->sprites[pos] = SGUI_Sprite_from_text(
		entry->menu->renderer,
		letter,
		entry->menu->font,
		entry->font_color);
}

void SGUI_Entry_update_sprites( SGUI_Entry *entry )
{
	for (size_t i = 0; i < entry->text.len; i++)
	{
		SGUI_Entry_update_sprite(entry, i);
	}
}

void SGUI_Entry_draw( SGUI_Entry *entry )
{
	SDL_Rect draw_target;
    uint32_t text_width = 0;

	// draw bg
	SDL_SetRenderDrawColor(
		entry->menu->renderer,
		entry->bg_color.r,
		entry->bg_color.g,
		entry->bg_color.b,
		entry->bg_color.a);
	SDL_RenderFillRect(entry->menu->renderer, &entry->rect);

	// draw border
	SDL_SetRenderDrawColor(
		entry->menu->renderer,
		entry->border_color.r,
		entry->border_color.g,
		entry->border_color.b,
		entry->border_color.a);
	SDL_RenderDrawRect(entry->menu->renderer, &entry->rect);

	// draw text
	for (size_t i = 0; i < entry->text.len; i++)
	{
		// if text exceeds entry width, stop
		if (text_width > (uint32_t) entry->rect.w)
			break;

		// draw
		draw_target.x = entry->rect.x + text_width;
		draw_target.y = entry->rect.y;
		draw_target.w = entry->sprites[i].surface->w;
		draw_target.h = entry->sprites[i].surface->h;

		SDL_RenderCopy(
			entry->menu->renderer,
			entry->sprites[i].texture,
			NULL,
			&draw_target);

		text_width += draw_target.w;
	}

	// if disabled, draw disabled shade
	if (entry->active == false)
	{
		SDL_SetRenderDrawColor(
			entry->menu->renderer,
			entry->disabled_color.r,
			entry->disabled_color.g,
			entry->disabled_color.b,
			entry->disabled_color.a);
		SDL_RenderFillRect(entry->menu->renderer, &entry->rect);
	}
}

void SGUI_Entry_clear_sprites( SGUI_Entry *entry )
{
	for (size_t i = 0; i < entry->text.len; i++)
	{
		SGUI_Sprite_clear(&entry->sprites[i]);
	}
}
