/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:55:56 by fousse            #+#    #+#             */
/*   Updated: 2022/01/24 18:35:54 by sfournie         ###   ########.fr       */
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
	if (tiles[tile_pos] == M_WALL)
		return (1);
	tile_pos = (x - size) / ts + (y + size) / ts * map;
	if (tiles[tile_pos] == M_WALL)
		return (1);
	tile_pos = (x + size) / ts + (y - size) / ts * map;
	if (tiles[tile_pos] == M_WALL)
		return (1);
	tile_pos = (x + size) / ts + (y + size) / ts * map;
	if (tiles[tile_pos] == M_WALL)
		return (1);
	return (0);
}
