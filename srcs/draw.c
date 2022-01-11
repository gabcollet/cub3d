/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/10 21:02:08 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void draw_object(t_mlx *mlx, t_obj *obj)
{
	double		index_x;
	double		index_y;
	double		step;
	int			x;
	int			y;
	int			color;
	t_img		img;

	img = obj->sprite.frames[obj->sprite.active];
	step = 1.0 / obj->sprite.scaling;
	index_y = 0;
	y = obj->pos.y - (double)img.height * obj->sprite.scaling;
	while (index_y < img.height)
	{
		x = obj->pos.x;
		index_x = 0;
		while (index_x < img.width / 4)
		{
			color = color_get(img, (int)index_x, (int)index_y);
			my_mlx_pixel_put(g_game.game_img, (int)x, (int)y, color);
			index_x += step;
			x++;
		}
		y++;
		index_y += step;
	}
}

// void draw_object(t_mlx *mlx, t_obj *obj)
// {
// 	double		index_x;
// 	double		index_y;
// 	double		width;
// 	double		height;
// 	t_img		img;
// 	int			color;

// 	img = obj->sprite.frames[obj->sprite.active];
// 	width = (double)img.width / 4;
// 	height = (double)img.height;
// 	index_y = obj->pos.y;
// 	index_x = obj->pos.x;
// 	while (index_y < obj->pos.y + height)
// 	{
// 		index_x = obj->pos.x;
// 		while (index_x < obj->pos.x + width)
// 		{
// 			color = color_get(img, (int)(index_x - obj->pos.x), (int)(index_y - obj->pos.y));
// 			my_mlx_pixel_put(g_game.game_img, (int)index_x, (int)index_y, color);
// 			//my_mlx_pixel_put(g_game.game_img, (int)index_x, (int)index_y, color_get(img, (int)(index_x - obj->pos.x), (int)(index_y - obj->pos.y)));
// 			index_x++;
// 		}
// 		index_y++;
// 	}
// }
