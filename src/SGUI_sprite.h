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

#ifndef SGUI_SPRITE_H
#define SGUI_SPRITE_H

#include <SM_types.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct SGUI_Sprite {
	bool invalid;
	SDL_Surface *surface;
	SDL_Texture *texture;
} SGUI_Sprite;

SGUI_Sprite SGUI_Sprite_new(void);

SGUI_Sprite SGUI_Sprite_from_file(SDL_Renderer * renderer,
				  const char *filepath);

SGUI_Sprite SGUI_Sprite_from_text(SDL_Renderer *, const char *text,
				  TTF_Font * font, SDL_Color color);

void SGUI_Sprite_create_texture(SGUI_Sprite * sprite, SDL_Renderer * renderer);

void SGUI_Sprite_clear(SGUI_Sprite * sprite);

#endif				/* SGUI_SPRITE_H */
