/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:55:56 by fousse            #+#    #+#             */
/*   Updated: 2022/01/01 15:01:47 by gcollet          ###   ########.fr       */
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
	int		*tiles;

	tiles = g_game.map.tiles;
	if (tiles[(x - size) / TILE_SIZE + (y - size) / TILE_SIZE * map] == 1)
		return (1);
	if (tiles[(x - size) / TILE_SIZE + (y + size) / TILE_SIZE * map] == 1)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + (y - size) / TILE_SIZE * map] == 1)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + (y + size) / TILE_SIZE * map] == 1)
		return (1);
	return (0);
}
