/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:49:36 by fousse            #+#    #+#             */
/*   Updated: 2022/01/16 03:14:53 by fousse           ###   ########.fr       */
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

void	draw_enemy(t_img *text, t_pos pos, float height, t_pos index)
{
	t_img	*img;
	double	y_step;
	int		bytes;
	int		color;

	if (height > WIN_H)
		height = WIN_H;
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
