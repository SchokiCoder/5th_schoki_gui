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

#ifndef SGUI_DEF_THEMES_H
#define SGUI_DEF_THEMES_H

#include "SGUI_theme.h"

static const SGUI_Theme SGUI_THEME_LIGHT = {
	.menu = {
		 .bg_color = {.r = 200,.g = 200,.b = 200,.a = 255},
		 },

	.label = {
		  .font_color = {.r = 50,.g = 50,.b = 50,.a = 255},
		  .bg_color = {.r = 0,.g = 0,.b = 0,.a = 0},
		  .border_color = {.r = 0,.g = 0,.b = 0,.a = 0},
		  },

	.button = {
		   .font_color = {.r = 0,.g = 0,.b = 0,.a = 255},
		   .bg_color = {.r = 255,.g = 255,.b = 255,.a = 255},
		   .border_color = {.r = 0,.g = 0,.b = 0,.a = 255},
		   .disabled_color = {.r = 0,.g = 0,.b = 0,.a = 50},
		   },

	.entry = {
		  .font_color = {.r = 0,.g = 0,.b = 0,.a = 255},
		  .bg_color = {.r = 240,.g = 240,.b = 240,.a = 255},
		  .border_color = {.r = 0,.g = 0,.b = 0,.a = 255},
		  .disabled_color = {.r = 0,.g = 0,.b = 0,.a = 50},
		  },
};

static const SGUI_Theme SGUI_THEME_DARK = {
	.menu = {
		 .bg_color = {.r = 30,.g = 30,.b = 30,.a = 255},
		 },

	.label = {
		  .font_color = {.r = 200,.g = 200,.b = 200,.a = 255},
		  .bg_color = {.r = 0,.g = 0,.b = 0,.a = 0},
		  .border_color = {.r = 0,.g = 0,.b = 0,.a = 0},
		  },

	.button = {
		   .font_color = {.r = 200,.g = 200,.b = 200,.a = 255},
		   .bg_color = {.r = 50,.g = 50,.b = 50,.a = 255},
		   .border_color = {.r = 70,.g = 70,.b = 70,.a = 255},
		   .disabled_color = {.r = 0,.g = 0,.b = 0,.a = 75},
		   },

	.entry = {
		  .font_color = {.r = 200,.g = 200,.b = 200,.a = 255},
		  .bg_color = {.r = 65,.g = 65,.b = 65,.a = 255},
		  .border_color = {.r = 70,.g = 70,.b = 70,.a = 255},
		  .disabled_color = {.r = 0,.g = 0,.b = 0,.a = 75},
		  },
};

#endif				/* SGUI_DEF_THEMES_H */
