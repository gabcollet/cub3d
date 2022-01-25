/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:55:56 by fousse            #+#    #+#             */
/*   Updated: 2022/01/20 18:05:11 by gcollet          ###   ########.fr       */
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

int	check_collision(int x, int y, int size, int map)
{
	char	*tiles;
	int		ts;
	int		tile_pos;

	tiles = g_game.map.tiles;
	ts = (int)TILE_SIZE;
	tile_pos = (x - size) / ts + (y - size) / ts * map;
	if (tiles[tile_pos] == M_WALL || (tiles[tile_pos] == M_DOOR
			&& check_door(tile_pos)))
		return (1);
	tile_pos = (x - size) / ts + (y + size) / ts * map;
	if (tiles[tile_pos] == M_WALL || (tiles[tile_pos] == M_DOOR
			&& check_door(tile_pos)))
		return (1);
	tile_pos = (x + size) / ts + (y - size) / ts * map;
	if (tiles[tile_pos] == M_WALL || (tiles[tile_pos] == M_DOOR
			&& check_door(tile_pos)))
		return (1);
	tile_pos = (x + size) / ts + (y + size) / ts * map;
	if (tiles[tile_pos] == M_WALL || (tiles[tile_pos] == M_DOOR
			&& check_door(tile_pos)))
		return (1);
	return (0);
}

int	check_door(int tile_pos)
{
	int		id;
	t_door	*door;

	door = g_game.doors;
	id = 0;
	while (id < g_game.door_count)
	{
		if (door[id].tile_i == tile_pos)
		{
			if (door[id].opened)
				return (0);
			else
				return (1);
		}
		id++;
	}
	return (0);
}
