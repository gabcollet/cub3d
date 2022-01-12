/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/12 17:23:21 by gcollet          ###   ########.fr       */
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

void	draw_enemy(t_img *text, t_pos pos, float height, t_pos index)
{
	t_img	*img;
	double	y_step;
	int		bytes;
	int		color;

	if (height > WIN_H)
	{
		//offset = (height - WIN_H);
		height = WIN_H;
	}
	img = &g_game.game_img;
	index.x = 0;
	y_step = (((float)text->height - (index.y * 2))
			/ (height + (img->height - height)));
	bytes = (text->bpp / 8);
	while (pos.y < height + (img->height - height) / 2)
	{
		color = *((unsigned int *)(text->addr
					+ ((int)index.y * text->width + (int)index.x * bytes)));
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		if (pos.x >= 0 && pos.x < img->width)
			my_mlx_pixel_put(*img, pos.x, pos.y, color);
		index.y += y_step;
		pos.y++;
	}
	index.x++;
}
