/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 01:54:41 by fousse            #+#    #+#             */
/*   Updated: 2022/01/25 17:05:28 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// need to be reworked so it works with the parse. this is for testing purpose
void	init_interface(t_obj *objs)
{	
	t_img	img;
	int		scaling;

	init_handgun(&objs[UI_GUN].sprite);
	init_enemy_sprite(&objs[ENEMY].sprite);
	img = objs[UI_GUN].sprite.frames[0];
	scaling = objs[UI_GUN].sprite.scaling;
	objs[UI_GUN].pos = new_pos(WIN_W / 2 - (img.width / 8 * scaling), WIN_H, 0);
	img = g_game.enemies[ENEMY].sprite.frames[0];
	scaling = g_game.enemies[ENEMY].sprite.scaling;
}

void	draw_ui(void)
{
	t_obj	*obj;

	obj = g_game.ui_elems;
	draw_ui_element(&obj[UI_GUN]);
}

void	put_ui_pixel(t_obj_draw	d, t_img img, t_obj *obj)
{
	int	color;

	while (d.index_y < img.height)
	{
		if (d.index_x < img.width / 4)
		{
			color = color_get(img, (int)d.index_x, (int)d.index_y);
			my_mlx_pixel_put(g_game.game_img, (int)d.x, (int)d.y, color);
			d.index_x += d.step;
			d.x++;
		}
		else if (d.index_x <= img.width / 4)
		{
			d.y++;
			d.index_y += d.step;
			d.x = obj->pos.x;
			d.index_x = 0;
		}
	}
}

void	draw_ui_element(t_obj *obj)
{
	t_obj_draw	d;
	t_img		img;

	img = obj->sprite.frames[obj->sprite.active];
	d.step = 1.0 / obj->sprite.scaling;
	d.index_y = 0;
	d.index_x = 0;
	d.x = obj->pos.x;
	d.y = obj->pos.y - (double)img.height * obj->sprite.scaling;
	put_ui_pixel(d, img, obj);
}
