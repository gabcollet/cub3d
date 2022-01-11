/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/11 00:58:00 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

typedef struct s_obj_draw
{
	double		index_x;
	double		index_y;
	double		step;
	int			x;
	int			y;
}				t_obj_draw;

void	draw_object(t_mlx *mlx, t_obj *obj)
{
	t_obj_draw	d;
	int			color;
	t_img		img;

	img = obj->sprite.frames[obj->sprite.active];
	d.step = 1.0 / obj->sprite.scaling;
	d.index_y = 0;
	d.y = obj->pos.y - (double)img.height * obj->sprite.scaling;
	while (d.index_y < img.height)
	{
		d.x = obj->pos.x;
		d.index_x = 0;
		while (d.index_x < img.width / 4)
		{
			color = color_get(img, (int)d.index_x, (int)d.index_y);
			my_mlx_pixel_put(g_game.game_img, (int)d.x, (int)d.y, color);
			d.index_x += d.step;
			d.x++;
		}
		d.y++;
		d.index_y += d.step;
	}
}
