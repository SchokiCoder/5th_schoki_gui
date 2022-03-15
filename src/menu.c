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
#include "theme.h"
#include "label.h"
#include "button.h"
#include "entry.h"
#include "menu.h"

SGUI_Menu SGUI_Menu_new( SDL_Renderer *renderer, TTF_Font *font, const SGUI_Theme *theme )
{
    SGUI_Menu result = {
		.renderer = renderer,
		.font = font,
        .label_count = 0,
        .button_count = 0,
        .entry_count = 0,
        .focused_entry = 0,
        .visible = true,
        .active = true,
        .bg_color = theme->menu_bg_color
    };

    return result;
}

void SGUI_Menu_draw( SGUI_Menu *menu )
{
	// stop if not visible
	if (menu->visible == false)
		return;

	// draw bg
	SDL_SetRenderDrawColor(
		menu->renderer,
		menu->bg_color.r,
		menu->bg_color.g,
		menu->bg_color.b,
		menu->bg_color.a);
	SDL_RenderFillRect(menu->renderer, &menu->rect);

	// draw labels
	for (uint8_t i = 0; i < menu->label_count; i++)
	{
		if (menu->labels[i]->visible)
		{
            SGUI_Label_draw(menu->labels[i]);
		}
	}

	// draw buttons
	for (uint8_t i = 0; i < menu->button_count; i++)
	{
		if (menu->buttons[i]->visible)
		{
			SGUI_Button_draw(menu->buttons[i]);
		}
	}

	// draw entries
	for (uint8_t i = 0; i < menu->entry_count; i++)
	{
		if (menu->entries[i]->visible)
		{
			SGUI_Entry_draw(menu->entries[i]);
		}
	}
}

void SGUI_Menu_handle_events( SGUI_Menu *menu, SDL_Event *event )
{
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
			if (SDL_PointInRect(&mouse, &menu->buttons[i]->rect))
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
			if (SDL_PointInRect(&mouse, &menu->entries[i]->rect))
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
        	SGUI_Entry_update_sprite(
        		menu->entries[menu->focused_entry],
        		strlen(menu->entries[menu->focused_entry]->text) - 1);
        }
		break;

	case SDL_KEYDOWN:

		// backspace
		if (event->key.keysym.sym == SDLK_BACKSPACE)
		{
			for (uint8_t i = 0; i < SGUI_ENTRY_MAX_TEXT_LEN; i++)
			{
                if (menu->entries[menu->focused_entry]->text[i] == '\0')
                {
                	menu->entries[menu->focused_entry]->text[i - 1] = '\0';
                	break;
                }
			}
		}

		break;
	}
}

void SGUI_Menu_clear( SGUI_Menu *menu )
{
    for (uint8_t i = 0; i < menu->label_count; i++)
    {
    	SGUI_Sprite_clear(&menu->labels[i]->sprite);
    }

    for (uint8_t i = 0; i < menu->button_count; i++)
    {
    	SGUI_Sprite_clear(&menu->buttons[i]->sprite);
    }

    for (uint8_t i = 0; i < menu->entry_count; i++)
    {
    	SGUI_Entry_clear_sprites(menu->entries[i]);
    }
}
