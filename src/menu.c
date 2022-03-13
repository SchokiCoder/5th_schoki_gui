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

#include <SDL_events.h>
#include "menu.h"

SGUI_Menu SGUI_Menu_new( SDL_Renderer *renderer, TTF_Font *font )
{
    SGUI_Menu result = {
		.renderer = renderer,
		.font = font,
        .label_count = 0,
        .button_count = 0,
        .entry_count = 0,
        .focused_entry = 0
    };

    return result;
}

void SGUI_Menu_draw( SGUI_Menu *menu )
{
	SDL_Rect draw_target;

	// stop if not visible
	if (menu->visible == false)
		return;

	// draw labels
	for (uint8_t i = 0; i < menu->label_count; i++)
	{
		if (menu->labels[i]->visible)
		{
			draw_target.x = menu->labels[i]->x;
			draw_target.y = menu->labels[i]->y;
			draw_target.w = menu->labels[i]->w;
			draw_target.h = menu->labels[i]->h;

			SDL_RenderCopy(
				menu->renderer,
				menu->labels[i]->sprite.texture,
				NULL,
				&draw_target);
		}
	}

	// draw buttons
	for (uint8_t i = 0; i < menu->button_count; i++)
	{
		if (menu->buttons[i]->visible)
		{
			draw_target.x = menu->buttons[i]->x;
			draw_target.y = menu->buttons[i]->y;
			draw_target.w = menu->buttons[i]->w;
			draw_target.h = menu->buttons[i]->h;

			SDL_RenderCopy(
				menu->renderer,
				menu->buttons[i]->sprite.texture,
				NULL,
				&draw_target);
		}
	}

	// draw entries
	for (uint8_t i = 0; i < menu->entry_count; i++)
	{
		if (menu->entries[i]->visible)
		{
			draw_target.x = menu->entries[i]->x;
			draw_target.y = menu->entries[i]->y;
			draw_target.w = menu->entries[i]->w;
			draw_target.h = menu->entries[i]->h;

			SDL_RenderCopy(
				menu->renderer,
				menu->entries[i]->sprite.texture,
				NULL,
				&draw_target);
		}
	}
}

void SGUI_Menu_handle_events( SGUI_Menu *menu, SDL_Event *event )
{
    SDL_Rect mouse_target;
    SDL_Point mouse;

    // stop if not visible or not active
    if (menu->visible == false || menu->active == false)
    	return;

	// handle current event
    switch (event->type)
    {
    // mouse click
    case SDL_MOUSEBUTTONUP:

    	// get mouse coords
    	SDL_GetMouseState(&mouse.x, &mouse.y);

    	// check buttons
    	for (uint8_t i = 0; i < menu->button_count; i++)
    	{
			// if not visible or not active or no event-function stored, skip
			if (menu->buttons[i]->visible == false ||
				menu->buttons[i]->active == false ||
				menu->buttons[i]->func_click == NULL)
				continue;

			// if mouse hit button
			mouse_target.x = menu->buttons[i]->x;
			mouse_target.y = menu->buttons[i]->y;
			mouse_target.w = menu->buttons[i]->w;
			mouse_target.h = menu->buttons[i]->h;

			if (SDL_PointInRect(&mouse, &mouse_target))
			{
				// execute event-function, stop
				menu->buttons[i]->func_click(menu->buttons[i]->data_click);
				return;
			}
    	}

    	// check entries
		for (uint8_t i = 0; i < menu->entry_count; i++)
    	{
    		// if not visible or not active, skip
			if (menu->entries[i]->visible == false ||
				menu->entries[i]->active == false)
				continue;

			// if mouse hit entry
			mouse_target.x = menu->entries[i]->x;
			mouse_target.y = menu->entries[i]->y;
			mouse_target.w = menu->entries[i]->w;
			mouse_target.h = menu->entries[i]->h;

			if (SDL_PointInRect(&mouse, &mouse_target))
			{
                // mark entry as focused, stop
                menu->focused_entry = i;
                return;
			}
    	}
    	break;

	// keyboard
	case SDL_TEXTINPUT:

        // if focused entry exists
        if (menu->focused_entry < menu->entry_count)
        {
        	// add typed character, update sprite
        	strncat(menu->entries[menu->focused_entry]->text, event->text.text, 1);
        	SGUI_clear_sprite(&menu->entries[menu->focused_entry]->sprite);
        	menu->entries[menu->focused_entry]->sprite = SGUI_sprite_from_text(
        		menu->renderer,
        		menu->entries[menu->focused_entry]->text,
        		menu->font,
        		menu->entries[menu->focused_entry]->font_color);
        }
		break;
    }
}
