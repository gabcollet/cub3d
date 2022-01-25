/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:01:03 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/25 17:11:43 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_map2d(t_map map)
{
	int	x;
	int	y;

	x = -1;
	y = 0;
	while (y < map.height)
	{
		if (++x < map.width)
		{
			if (map.tiles[y * map.width + x] == M_WALL)
				draw_tile(x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else if (map.tiles[y * map.width + x] == M_DOOR)
				draw_tile(x * MINI_TILE_S, y * MINI_TILE_S, DOOR);
			else if (map.tiles[y * map.width + x] == M_EMPTY)
				draw_tile(x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else
				draw_tile(x * MINI_TILE_S, y * MINI_TILE_S, FLOOR);
		}
		else
		{
			x = -1;
			y++;
		}
	}
	draw_player();
}

void	draw_tile(int x, int y, int type)
{
	int	index_x;
	int	index_y;
	int	color;

	index_x = x - 1;
	index_y = y;
	while (index_y < (y + MINI_TILE_S))
	{
		if (++index_x < (x + MINI_TILE_S))
		{
			color = color_get(g_game.game_img, index_x, index_y);
			if (type == WALL)
				color = color_shift_int(color, BLACK, 0.5);
			else if (type == DOOR)
				color = color_shift_int(color, YELLOW, 0.5);
			else if (type == FLOOR)
				color = color_shift_int(color, GRAY, 0.5);
			my_mlx_pixel_put(g_game.game_img, index_x, index_y, color);
		}
		else
		{
			index_x = x - 1;
			index_y++;
		}
	}
}

void	draw_player(void)
{
	double	i;

	i = -(VIEW_ANGLE / 2);
	while (i <= VIEW_ANGLE / 2)
	{
		raycast_draw(g_game.player.rot - i, 10, RED, -1);
		raycast_draw(g_game.player.rot - i, 30, WHITE, 1);
		i += 0.25;
	}
}
