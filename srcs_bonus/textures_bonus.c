/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:38:28 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/25 16:53:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_textures(t_game *game)
{
	game->texture[0].img = NULL;
	game->texture[1].img = NULL;
	game->texture[2].img = NULL;
	game->texture[3].img = NULL;
}

t_pos	textures_index(t_pos pos, float offset, float height, int side)
{
	double	i_x;
	double	i_y;

	if (side)
		i_x = (fmod(fmod(pos.x, TILE_SIZE), TEXTURES_SIZE));
	else
		i_x = (fmod(fmod(pos.y, TILE_SIZE), TEXTURES_SIZE));
	i_y = (TEXTURES_SIZE * offset / 2) / (height + (offset));
	return (new_pos(i_x, i_y, 0));
}

void	fill_with_texture(t_img *text, t_pos pos, float height, t_pos index)
{
	t_img	*img;
	double	y_step;
	int		bytes;
	int		color;

	img = &g_game.game_img;
	y_step = ((float)text->height - (index.y * 2))
		/ (height + (img->height - height) / TILE_SIZE);
	bytes = (text->bpp / 8);
	color = 0;
	while (pos.y < height + (img->height - height) / 2)
	{
		color = color_get(*text, (int)index.x, (int)index.y);
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		if (pos.x >= 0 && pos.x < img->width)
			my_mlx_pixel_put(*img, pos.x, pos.y + g_game.player.pos.z, color);
		index.y += y_step;
		pos.y++;
	}
}
