/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:55:56 by fousse            #+#    #+#             */
/*   Updated: 2022/01/11 13:40:36 by gcollet          ###   ########.fr       */
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

	tiles = g_game.map.tiles;
	ts = (int)TILE_SIZE;
	if (tiles[(x - size) / ts + (y - size) / ts * map] == M_WALL)
		return (1);
	if (tiles[(x - size) / ts + (y + size) / ts * map] == M_WALL)
		return (1);
	if (tiles[(x + size) / ts + (y - size) / ts * map] == M_WALL)
		return (1);
	if (tiles[(x + size) / ts + (y + size) / ts * map] == M_WALL)
		return (1);
	return (0);
}
