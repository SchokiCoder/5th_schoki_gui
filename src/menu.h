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

#ifndef SGUI_MENU_H
#define SGUI_MENU_H

#include <stdbool.h>
#include <stdint.h>
#include "label.h"
#include "button.h"

#define SGUI_MENU_MAX_WIDGETS 16 /* per type */

typedef struct SGUI_Menu
{
	bool visible;
	bool active;

	uint8_t label_count;
	SGUI_Label *labels[SGUI_MENU_MAX_WIDGETS];

	uint8_t button_count;
	SGUI_Button *buttons[SGUI_MENU_MAX_WIDGETS];
} SGUI_Menu ;

SGUI_Menu SGUI_Menu_new( void );

void SGUI_Menu_draw( SGUI_Menu*, SDL_Renderer* );

void SGUI_Menu_handle_events( SGUI_Menu*, SDL_Event* );

#endif /* SGUI_MENU_H */
