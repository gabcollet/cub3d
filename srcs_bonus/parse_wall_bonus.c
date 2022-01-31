/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/30 20:16:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

int	parse_col_is_enclosed(t_map map, int x)
{
	int	y;

	if (x >= map.width || x < 0)
		return (0);
	y = 0;
	while (map.tiles[x + y * map.width] == M_EMPTY)
		y++;
	if (map.tiles[x + y * map.width] != M_WALL)
		return (0);
	y = map.height - 1;
	while (map.tiles[x + y * map.width] == M_EMPTY)
		y--;
	if (map.tiles[x + y * map.width] != M_WALL)
		return (0);
	return (1);
}

int	parse_row_is_enclosed(t_map map, int y)
{
	int	x;

	if (y >= map.height || y < 0)
		return (0);
	x = 0;
	while (map.tiles[x + y * map.width] == M_EMPTY)
		x++;
	if (map.tiles[x + y * map.width] != M_WALL)
		return (0);
	x = map.width - 1;
	while (map.tiles[x + y * map.width] == M_EMPTY)
		x--;
	if (map.tiles[x + y * map.width] != M_WALL)
		return (0);
	return (1);
}

int	parse_map_is_enclosed(t_map map)
{
	int	i;

	i = 0;
	while (i < map.height)
	{
		if (!parse_row_is_enclosed(map, i++))
			return (0);
	}
	i = 0;
	while (i < map.width)
	{
		if (!parse_col_is_enclosed(map, i++))
			return (0);
	}
	return (1);
}
