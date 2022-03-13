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
#include "label.h"

void SGUI_Label_new( SGUI_Label *label, SGUI_Menu *menu, const SGUI_Theme *theme )
{
	label->menu = menu;
	label->sprite.invalid = false;
	label->visible = true;
	label->font_color = theme->label_font_color;
	label->bg_color = theme->label_bg_color;
	label->border_color = theme->label_border_color;

	menu->labels[menu->label_count] = label;
	menu->label_count++;
}

void SGUI_Label_draw( SGUI_Label *label )
{
	SDL_Rect draw_target = {
		.x = label->x,
		.y = label->y,
		.w = label->w,
		.h = label->h
	};

	// draw bg
	SDL_SetRenderDrawColor(
		label->menu->renderer,
		label->bg_color.r,
		label->bg_color.g,
		label->bg_color.b,
		label->bg_color.a);
	SDL_RenderFillRect(label->menu->renderer, &draw_target);

	// draw border
	SDL_SetRenderDrawColor(
		label->menu->renderer,
		label->border_color.r,
		label->border_color.g,
		label->border_color.b,
		label->border_color.a);
	SDL_RenderDrawRect(label->menu->renderer, &draw_target);

	// draw text
	SDL_RenderCopy(
		label->menu->renderer,
		label->sprite.texture,
		NULL,
		&draw_target);
}
