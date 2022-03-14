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

#ifndef SGUI_DEF_THEMES_H
#define SGUI_DEF_THEMES_H

#include "theme.h"

static const SGUI_Theme SGUI_THEME_LIGHT = {
	.menu_bg_color = {.r = 200, .g = 200, .b = 200, .a = 255},

	.label_font_color = {.r = 50, .g = 50, .b = 50, .a = 255},
    .label_bg_color = {.r = 0, .g = 0, .b = 0, .a = 0},
    .label_border_color = {.r = 0, .g = 0, .b = 0, .a = 0},

    .button_font_color = {.r = 0, .g = 0, .b = 0, .a = 255},
    .button_bg_color = {.r = 255, .g = 255, .b = 255, .a = 255},
    .button_border_color = {.r = 0, .g = 0, .b = 0, .a = 255},
    .button_disabled_color = {.r = 0, .g = 0, .b = 0, .a = 50},

    .entry_font_color = {.r = 0, .g = 0, .b = 0, .a = 255},
    .entry_bg_color = {.r = 240, .g = 240, .b = 240, .a = 255},
    .entry_border_color = {.r = 0, .g = 0, .b = 0, .a = 255},
    .entry_disabled_color = {.r = 0, .g = 0, .b = 0, .a = 50}
};

static const SGUI_Theme SGUI_THEME_DARK = {
	.menu_bg_color = {.r = 30, .g = 30, .b = 30, .a = 255},

	.label_font_color = {.r = 200, .g = 200, .b = 200, .a = 255},
    .label_bg_color = {.r = 0, .g = 0, .b = 0, .a = 0},
    .label_border_color = {.r = 0, .g = 0, .b = 0, .a = 0},

    .button_font_color = {.r = 200, .g = 200, .b = 200, .a = 255},
    .button_bg_color = {.r = 50, .g = 50, .b = 50, .a = 255},
    .button_border_color = {.r = 70, .g = 70, .b = 70, .a = 255},
    .button_disabled_color = {.r = 0, .g = 0, .b = 0, .a = 75},

    .entry_font_color = {.r = 200, .g = 200, .b = 200, .a = 255},
    .entry_bg_color = {.r = 65, .g = 65, .b = 65, .a = 255},
    .entry_border_color = {.r = 70, .g = 70, .b = 70, .a = 255},
    .entry_disabled_color = {.r = 0, .g = 0, .b = 0, .a = 75}
};

#endif /* SGUI_DEF_THEMES_H */
