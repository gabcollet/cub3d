/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:38:28 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/03 20:23:30 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_with_texture(t_img *win, t_img *text, int x, int y, float height, t_coll coll, float offset, int side)
{
	double	i_x;
	double	i_y;
	double	y_step;
	int		bytes;
	int		color;

	//pourquoi la text->width est de 128????
	if (side)
		i_x = (fmod(fmod(coll.pos.x, TILE_SIZE), (text->width / 4)));
	else
		i_x = (fmod(fmod(coll.pos.y, TILE_SIZE), (text->height)));

	i_y = offset / 32; //c'est pas tout a fait bon
	if (i_y >= 32)
		i_y = fmod(i_y, 32);

	y_step = (((float)text->height - (i_y * 2)) / (height + (win->height - height) / TILE_SIZE));
	
	bytes = (text->bpp / 8);
	while (y < height + (win->height - height) / 2)
	{
		color = *((unsigned int *)(text->addr + ((int)i_y * text->width + (int)i_x * bytes)));
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 1.5);
		if (x >= 0 && x < win->width)
			my_mlx_pixel_put(*win, x, y, color);
		i_y += y_step;
		y++;
	}
}
