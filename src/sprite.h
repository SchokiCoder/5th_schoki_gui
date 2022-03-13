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

#ifndef SGUI_SPRITE_H
#define SGUI_SPRITE_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct SGUI_Sprite
{
	bool invalid;
	SDL_Surface *surface;
	SDL_Texture *texture;
} SGUI_Sprite ;

SGUI_Sprite SGUI_Sprite_from_file( SDL_Renderer*, const char* );

SGUI_Sprite SGUI_Sprite_from_text( SDL_Renderer*, const char*, TTF_Font*, SDL_Color);

void SGUI_Sprite_create_texture( SGUI_Sprite*, SDL_Renderer* );

void SGUI_Sprite_clear( SGUI_Sprite* );

#endif /* SGUI_SPRITE_H */
