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
#include "button.h"

void SGUI_Button_new( SGUI_Button *button, SGUI_Menu *menu, const SGUI_Theme *theme )
{
	button->menu = menu;
	button->sprite.invalid = false;
	button->visible = true;
	button->active = true;
	button->font_color = theme->button_font_color;
	button->bg_color = theme->button_bg_color;
	button->border_color = theme->button_border_color;
	button->func_click = NULL;
	button->data_click = NULL;

	menu->buttons[menu->button_count] = button;
	menu->button_count++;
}

void SGUI_Button_draw( SGUI_Button *button )
{
	SDL_Rect draw_target = {
		.x = button->x,
		.y = button->y,
		.w = button->w,
		.h = button->h
	};

	// draw bg
	SDL_SetRenderDrawColor(
		button->menu->renderer,
		button->bg_color.r,
		button->bg_color.g,
		button->bg_color.b,
		button->bg_color.a);
	SDL_RenderFillRect(button->menu->renderer, &draw_target);

	// draw border
	SDL_SetRenderDrawColor(
		button->menu->renderer,
		button->border_color.r,
		button->border_color.g,
		button->border_color.b,
		button->border_color.a);
	SDL_RenderDrawRect(button->menu->renderer, &draw_target);

	// draw text
	SDL_RenderCopy(
		button->menu->renderer,
		button->sprite.texture,
		NULL,
		&draw_target);
}
