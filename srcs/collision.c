/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:55:56 by fousse            #+#    #+#             */
/*   Updated: 2021/12/31 18:55:58 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

t_coll	new_collider(t_pos pos, int type, int dir)
{
	t_coll	collider;

	collider.pos = pos;
	collider.type = type;
	collider.dir = dir;
	return (collider);
}

int	check_collision_x(int x, int y, int size)
{
	int		map_x;
	int		*tiles;

	tiles = g_game.map.tiles;
	map_x = g_game.map.width;
	if (tiles[(x - size) / TILE_SIZE + ((y - size) / TILE_SIZE * map_x)] == 1)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + ((y - size) / TILE_SIZE * map_x)] == 1)
		return (1);
	if (tiles[(x - size) / TILE_SIZE + ((y + size) / TILE_SIZE * map_x)] == 1)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + ((y + size) / TILE_SIZE * map_x)] == 1)
		return (1);
	return (0);
}

int	check_collision_y(int x, int y, int size)
{
	int		map_y;
	int		*tiles;

	tiles = g_game.map.tiles;
	map_y = g_game.map.height;
	if (tiles[(x - size) / TILE_SIZE + (y - size) / TILE_SIZE * map_y] == 1)
		return (1);
	if (tiles[(x - size) / TILE_SIZE + (y + size) / TILE_SIZE * map_y] == 1)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + (y - size) / TILE_SIZE * map_y] == 1)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + (y + size) / TILE_SIZE * map_y] == 1)
		return (1);
	return (0);
}
