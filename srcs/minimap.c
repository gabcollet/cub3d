/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:01:03 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/14 15:06:24 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map2d(t_mlx *mlx, t_map map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < map.height)
	{
		if (x < map.width)
		{
			if (map.tiles[y * map.width + x] == M_WALL)
				draw_tile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else if (map.tiles[y * map.width + x] == M_EMPTY)
				draw_tile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else
				draw_tile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, FLOOR);
				x++;
		}
		else
		{
			x = 0;
			y++;
		}
	}
	draw_player();
}

void	draw_tile(t_mlx *mlx, int x, int y, int type)
{
	int	index_x;
	int	index_y;
	int	color;

	index_x = x;
	index_y = y;
	while (index_y < (y + MINI_TILE_S))
	{
		if (index_x < (x + MINI_TILE_S))
		{
			color = color_get(g_game.game_img, index_x, index_y);
			if (type == WALL)
				color = color_shift_int(color, BLACK, 0.5);
			else if (type == FLOOR)
				color = color_shift_int(color, GRAY, 0.5);
			my_mlx_pixel_put(g_game.game_img, index_x, index_y, color);
			index_x++;
		}
		else
		{
			index_x = x;
			index_y++;
		}
		
	}
}

void	draw_player(void)
{
	t_pos	facing;
	double	i;

	i = -(VIEW_ANGLE / 2);
	while (i <= VIEW_ANGLE / 2)
	{
		raycast_draw(g_game.player.rot - i, 10, RED, -1);
		raycast_draw(g_game.player.rot - i, 30, WHITE, 1);
		i += 0.25;
	}
}
