/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:55:56 by fousse            #+#    #+#             */
/*   Updated: 2022/01/06 11:46:16 by fousse           ###   ########.fr       */
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
	char		*tiles;

	tiles = g_game.map.tiles;
	if (tiles[(x - size) / TILE_SIZE + (y - size) / TILE_SIZE * map] == M_WALL)
		return (1);
	if (tiles[(x - size) / TILE_SIZE + (y + size) / TILE_SIZE * map] == M_WALL)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + (y - size) / TILE_SIZE * map] == M_WALL)
		return (1);
	if (tiles[(x + size) / TILE_SIZE + (y + size) / TILE_SIZE * map] == M_WALL)
		return (1);
	return (0);
}
