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

#include <SDL_ttf.h>
#include "SGUI_sprite.h"

SGUI_Sprite SGUI_Sprite_new(void)
{
	SGUI_Sprite result = {
		.invalid = false,
		.surface = NULL,
		.texture = NULL
	};

	return result;
}

void SGUI_Sprite_create_texture(SGUI_Sprite * sprite, SDL_Renderer * renderer)
{
	// create texture
	sprite->texture =
	    SDL_CreateTextureFromSurface(renderer, sprite->surface);

	// check
	if (sprite->texture == NULL) {
		sprite->invalid = true;
	}
}

SGUI_Sprite SGUI_Sprite_from_file(SDL_Renderer * renderer, const char *filepath)
{
	SGUI_Sprite result = {.invalid = false };

	// load image, create texture
	result.surface = IMG_Load(filepath);
	SGUI_Sprite_create_texture(&result, renderer);

	return result;
}

SGUI_Sprite SGUI_Sprite_from_text(SDL_Renderer * renderer, const char *text,
				  TTF_Font * font, SDL_Color color)
{
	SGUI_Sprite result = {.invalid = false };

	// create text, create texture
	result.surface = TTF_RenderText_Solid(font, text, color);
	SGUI_Sprite_create_texture(&result, renderer);

	return result;
}

void SGUI_Sprite_clear(SGUI_Sprite * sprite)
{
	//reset values
	sprite->invalid = false;

	// if surface and texture exist, clear them
	if (sprite->surface != NULL) {
		SDL_FreeSurface(sprite->surface);
		sprite->surface = NULL;
	}

	if (sprite->texture != NULL) {
		SDL_DestroyTexture(sprite->texture);
		sprite->texture = NULL;
	}
}
