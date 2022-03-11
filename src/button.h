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

#ifndef SGUI_BUTTON_H
#define SGUI_BUTTON_H

#include <stdint.h>
#include "sprite.h"

#define SGUI_BUTTON_MAX_TEXT_LEN 32

typedef struct SGUI_Button
{
	bool visible;
	bool active;
	char text[SGUI_BUTTON_MAX_TEXT_LEN];
	SGUI_Sprite sprite;
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	void (*func_click) (void*);
	void *data_click;
} SGUI_Button ;

SGUI_Button SGUI_Button_new( void );

#endif /* SGUI_BUTTON_H */
