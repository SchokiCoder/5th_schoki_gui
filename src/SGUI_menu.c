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
#include <SM_string.h>
#include "SGUI_theme.h"
#include "SGUI_label.h"
#include "SGUI_button.h"
#include "SGUI_entry.h"
#include "SGUI_menu.h"

SGUI_Menu SGUI_Menu_new( SDL_Renderer *renderer, const SGUI_MenuStyle style )
{
    SGUI_Menu result = {
		.renderer = renderer,
        .label_count = 0,
        .button_count = 0,
        .entry_count = 0,
        .focused_entry = NULL,
        .visible = true,
        .active = true,
        .style = style
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
		menu->style.bg_color.r,
		menu->style.bg_color.g,
		menu->style.bg_color.b,
		menu->style.bg_color.a);
	SDL_RenderFillRect(menu->renderer, &menu->rect);

	// draw labels
	for (u8 i = 0; i < menu->label_count; i++)
	{
		if (menu->labels[i]->visible)
		{
            SGUI_Label_draw(menu->labels[i]);
		}
	}

	// draw buttons
	for (u8 i = 0; i < menu->button_count; i++)
	{
		if (menu->buttons[i]->visible)
		{
			SGUI_Button_draw(menu->buttons[i]);
		}
	}

	// draw entries
	for (u8 i = 0; i < menu->entry_count; i++)
	{
		if (menu->entries[i]->visible)
		{
			SGUI_Entry_draw(menu->entries[i]);
		}
	}
}

void SGUI_Menu_handle_event( SGUI_Menu *menu, SDL_Event *event )
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
    	for (u8 i = 0; i < menu->button_count; i++)
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
		for (u8 i = 0; i < menu->entry_count; i++)
    	{
    		// if not visible or not active, skip
			if (menu->entries[i]->visible == false ||
				menu->entries[i]->active == false)
				continue;

			// if mouse hit entry
			if (SDL_PointInRect(&mouse, &menu->entries[i]->rect))
			{
                // mark entry as focused, stop
                menu->focused_entry = menu->entries[i];
                return;
			}
    	}
    	break;

	// keyboard
	case SDL_TEXTINPUT:

        // if menu has a focused entry
        if (menu->focused_entry != NULL)
        {
        	// add new characters
        	SM_String new = SM_String_contain(event->text.text);
        	SGUI_Entry_append(menu->focused_entry, &new);
        }
		break;

	case SDL_KEYDOWN:

		// if menu has a focused entry
		if (menu->focused_entry != NULL)
		{
			// backspace
			if (event->key.keysym.sym == SDLK_BACKSPACE)
			{
				if (menu->focused_entry->text.len > 0)
				{
					menu->focused_entry->text.str[menu->focused_entry->text.len - 1] = '\0';
					menu->focused_entry->text.len--;
				}
			}
		}

		break;
	}
}

void SGUI_Menu_grid( SGUI_Menu *menu )
{
	typedef struct CellData
	{
		SGUI_WidgetId wid;
		u32 width;
		u32 height;
	} CellData ;
	
	CellData table[256][256] = {};
	u32 table_w[256];
	u32 table_h[256];
	
	// get widgets in each cell
	for (u8 i = 0; i < menu->label_count; i++)
    {
		table[menu->labels[i]->rect.x][menu->labels[i]->rect.y].wid.i = i;
		table[menu->labels[i]->rect.x][menu->labels[i]->rect.y].wid.type = WT_Label;
		table[menu->labels[i]->rect.x][menu->labels[i]->rect.y].width = menu->labels[i]->rect.w;
		table[menu->labels[i]->rect.x][menu->labels[i]->rect.y].height = menu->labels[i]->rect.h;
    }

    for (u8 i = 0; i < menu->button_count; i++)
    {
		table[menu->buttons[i]->rect.x][menu->buttons[i]->rect.y].wid.i = i;
		table[menu->buttons[i]->rect.x][menu->buttons[i]->rect.y].wid.type = WT_Button;
		table[menu->buttons[i]->rect.x][menu->buttons[i]->rect.y].width = menu->buttons[i]->rect.w;
		table[menu->buttons[i]->rect.x][menu->buttons[i]->rect.y].height = menu->buttons[i]->rect.h;
    }

    for (u8 i = 0; i < menu->entry_count; i++)
    {
		table[menu->entries[i]->rect.x][menu->entries[i]->rect.y].wid.i = i;
		table[menu->entries[i]->rect.x][menu->entries[i]->rect.y].wid.type = WT_Entry;
		table[menu->entries[i]->rect.x][menu->entries[i]->rect.y].width = menu->entries[i]->rect.w;
		table[menu->entries[i]->rect.x][menu->entries[i]->rect.y].height = menu->entries[i]->rect.h;
    }

	// get col width, row height
	for (u8 x = 0; x < 254; x++)
	{
		for (u8 y = 0; y < 254; y++)
		{
			// if cell has content, skip
			if (table[x][y].wid.type == WT_None)
				continue;
			
			// if cell to the right has no content, increase width if needed
			if (table[x + 1][y].wid.type == WT_None)
			{
				if (table[x][y].width > table_w[x])
					table_w[x] = table[x][y].width;
			}
			
			// if cell below has no content, icrease height if needed
			if (table[x][y + 1].wid.type == WT_None)
			{
				if (table[x][y].height > table_h[y])
					table_h[y] = table[x][y].height;
			}
		}
	}
	
	// change pos of widgets
	#warning impl me
}

void SGUI_Menu_clear( SGUI_Menu *menu )
{
    for (u8 i = 0; i < menu->label_count; i++)
    {
    	SGUI_Sprite_clear(&menu->labels[i]->sprite);
    	SM_String_clear(&menu->labels[i]->text);
    }

    for (u8 i = 0; i < menu->button_count; i++)
    {
    	SGUI_Sprite_clear(&menu->buttons[i]->sprite);
    	SM_String_clear(&menu->buttons[i]->text);
    }

    for (u8 i = 0; i < menu->entry_count; i++)
    {
    	SGUI_Entry_clear_sprites(menu->entries[i]);
    	SM_String_clear(&menu->entries[i]->text);
    }
}
