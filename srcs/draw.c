/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/07 12:56:01 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void draw_object(t_mlx *mlx, t_obj *obj)
{
	double		index_x;
	double		index_y;
	double		width;
	double		height;
	t_img		img;

	img = obj->sprite.frames[obj->sprite.active];
	width = (double)img.width / 4;
	height = (double)img.height;
	index_y = obj->pos.y;
	index_x = obj->pos.x;
	while (index_y < obj->pos.y + height)
	{
		index_x = obj->pos.x;
		while (index_x < obj->pos.x + width)
		{
			my_mlx_pixel_put(mlx->img, (int)index_x, (int)index_y, color_get(img, (int)(index_x - obj->pos.x), (int)(index_y - obj->pos.y)));
			index_x++;
		}
		index_y++;
	}
}
