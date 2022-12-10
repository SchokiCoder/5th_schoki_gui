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

#include "SGUI_theme.h"
#include "SGUI_menu.h"
#include "SGUI_label.h"

void SGUI_Label_new(SGUI_Label * label,
		    SGUI_Menu * menu,
		    TTF_Font * font, const SGUI_LabelStyle style)
{
	label->menu = menu;
	label->font = font;
	label->text = SM_String_new(SGUI_LABEL_TEXT_INIT_SIZE);
	label->sprite = SGUI_Sprite_new();
	label->visible = true;
	label->style = style;

	menu->labels[menu->label_count] = label;
	menu->label_count++;
}

void SGUI_Label_update_sprite(SGUI_Label * label)
{
	SGUI_Sprite_clear(&label->sprite);
	label->sprite = SGUI_Sprite_from_text(label->menu->renderer,
					      label->text.str,
					      label->font,
					      label->style.font_color);
}

void SGUI_Label_draw(SGUI_Label * label)
{
	// draw bg
	SDL_SetRenderDrawColor(label->menu->renderer,
			       label->style.bg_color.r,
			       label->style.bg_color.g,
			       label->style.bg_color.b,
			       label->style.bg_color.a);
	SDL_RenderFillRect(label->menu->renderer, &label->rect);

	// draw border
	SDL_SetRenderDrawColor(label->menu->renderer,
			       label->style.border_color.r,
			       label->style.border_color.g,
			       label->style.border_color.b,
			       label->style.border_color.a);
	SDL_RenderDrawRect(label->menu->renderer, &label->rect);

	// draw text
	SDL_RenderCopy(label->menu->renderer,
		       label->sprite.texture, NULL, &label->rect);
}

void SGUI_Label_resize(SGUI_Label * label)
{
	label->rect.w = label->sprite.surface->w;
	label->rect.h = label->sprite.surface->h;
}
