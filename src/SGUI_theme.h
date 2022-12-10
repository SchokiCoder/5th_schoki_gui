/*
 * schoki_gui
 * Copyright (C) 2022  Andy Frank Schoknecht
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not see
 * <https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html>.
 */

#ifndef SGUI_THEME_H
#define SGUI_THEME_H

#include <SDL_pixels.h>
#include "SGUI_menu.h"
#include "SGUI_label.h"
#include "SGUI_button.h"
#include "SGUI_entry.h"

typedef struct SGUI_Theme {
	SGUI_MenuStyle menu;
	SGUI_LabelStyle label;
	SGUI_ButtonStyle button;
	SGUI_EntryStyle entry;
} SGUI_Theme;

#endif				/* SGUI_THEME_H */
