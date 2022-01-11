/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:01:03 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/11 00:59:39 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map2d(t_mlx *mlx, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.tiles[y * map.width + x] == M_WALL)
				draw_tile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else if (map.tiles[y * map.width + x] == M_EMPTY)
				draw_tile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, WALL);
			else
				draw_tile(mlx, x * MINI_TILE_S, y * MINI_TILE_S, FLOOR);
				x++;
		}
		y++;
	}
	draw_player();
}

void	draw_tile(t_mlx *mlx, int x, int y, int type)
{
	int	index_x;
	int	index_y;

	index_x = x;
	index_y = y;
	while (index_y < (y + MINI_TILE_S))
	{
		index_x = x;
		while (index_x < (x + MINI_TILE_S))
		{
			if (type == WALL)
				my_mlx_pixel_put(g_game.game_img, index_x, index_y, 0);
			else if (type == FLOOR)
				my_mlx_pixel_put(g_game.game_img, index_x, index_y, WHITE);
			else if (type == PLAYER)
				my_mlx_pixel_put(g_game.game_img, index_x, index_y, RED);
			index_x++;
		}
		index_y++;
	}
}

void	draw_player(void)
{
	t_pos	facing;
	int		i;
	//x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S) - 1;
	//y = g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S) - 1;
	/* while (y++ < g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S) + 1)
	{
		x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S) - 1;
		while (x++ < g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S) + 1)
		{
			my_mlx_pixel_put(mlx->img, x , y, RED);
		}
	} */

	facing.x = g_game.player.pos.x / (TILE_SIZE / MINI_TILE_S);
	facing.y = g_game.player.pos.y / (TILE_SIZE / MINI_TILE_S);
	i = -(VIEW_ANGLE / 2);
	while (i <= VIEW_ANGLE / 2)
	{
		raycast_draw(facing, g_game.player.rot - i, 10, RED);
		i += 3;
	}
}
