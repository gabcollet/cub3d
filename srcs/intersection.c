/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 11:00:43 by gcollet           #+#    #+#             */
/*   Updated: 2021/12/31 12:04:19 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	apply_tile_coll(int i_x, int i_y, int dir)
{
	int	*tiles_coll;

	tiles_coll = g_game.map.tiles_coll;
	tiles_coll[i_x + i_y] = tiles_coll[i_x + i_y] | dir;
	return (1);
}

int	check_inter_x(t_pos inter, int dir)
{
	t_map	map;
	int		i_x;
	int		i_y;

	map = g_game.map;
	i_x = (int)inter.x / TILE_SIZE;
	i_y = (int)inter.y / TILE_SIZE;
	if (i_x < 0 || i_y < 0 || i_x >= map.width || i_y >= map.height)
		return (1);
	if (map.tiles[i_x + (i_y * map.width)] == 1)
		return (apply_tile_coll(i_x, i_y * map.width, dir));
	if (i_x > 0 && map.tiles[i_x - 1 + (i_y * map.width)] == 1)
		return (apply_tile_coll(i_x, i_x - 1 + i_y * map.width, dir));
	return (0);
}

int	check_inter_y(t_pos inter, int dir)
{
	t_map	map;
	int		i_x;
	int		i_y;

	map = g_game.map;
	i_x = (int)inter.x / TILE_SIZE;
	i_y = (int)inter.y / TILE_SIZE;
	if (i_x < 0 || i_y < 0 || i_x >= map.width || i_y >= map.height)
		return (1);
	if (map.tiles[i_x + (i_y * map.width)] == 1)
		return (apply_tile_coll(i_x, i_y * map.width, dir));
	if (i_y > 0 && map.tiles[i_x + ((i_y - 1) * map.width)] == 1)
		return (apply_tile_coll(i_x, i_x + (i_y - 1) * map.width, dir));
	return (0);
}

t_pos	increment_pos(t_pos inter, int xy, int side, double rot)
{
	int	sign;

	if (side == NORTH || side == EAST)
		sign = 1;
	else if (side == SOUTH || side == WEST)
		sign = -1;
	if (xy == 'y')
	{
		inter.x += (TILE_SIZE / tan(deg_to_rad(rot))) * sign;
		inter.y += -TILE_SIZE * sign;
	}
	else
	{
		inter.x += TILE_SIZE * sign;
		inter.y += (-TILE_SIZE * tan(deg_to_rad(rot))) * sign;
	}
	return (inter);
}

int	parse_s(int side, int xy)
{
	if (xy == 'y')
	{
		if (side == 'NE' || side == 'NW')
			return (NORTH);
		else
			return (SOUTH);
	}
	else if (xy == 'x')
	{
		if (side == 'NE' || side == 'SE')
			return (EAST);
		else
			return (WEST);
	}
	return (0);
}

t_coll	check_dir(t_pos inter_y, t_pos inter_x, int side, double rot)
{
	int	x;
	int	y;

	x = g_game.player.pos.x;
	y = g_game.player.pos.y;
	while (1)
	{	
		if ((pow(inter_y.x - x, 2) + pow(inter_y.y - y, 2))
			< (pow(inter_x.x - x, 2) + pow(inter_x.y - y, 2)))
		{
			if (check_inter_y(inter_y, parse_s(side, 'y')) == 1)
				return (new_collider(inter_y, WALL, parse_s(side, 'y')));
			else
				inter_y = increment_pos(inter_y, 'y', parse_s(side, 'y'), rot);
		}
		else
		{
			if (check_inter_x(inter_x, parse_s(side, 'x')) == 1)
				return (new_collider(inter_x, WALL, parse_s(side, 'x')));
			else
				inter_x = increment_pos(inter_x, 'x', parse_s(side, 'x'), rot);
		}
	}
	return (new_collider(new_pos(0, 0, 0), 0, 0));
}

t_coll	check_intersections(int x, int y, double rot)
{
	t_pos	inter_y_n;
	t_pos	inter_y_s;
	t_pos	inter_x_e;
	t_pos	inter_x_w;

	inter_y_n.x = x + ((y % TILE_SIZE) / tan(deg_to_rad(rot)));
	inter_y_n.y = y - (y % TILE_SIZE);
	inter_y_s.x = x - (TILE_SIZE - (y % TILE_SIZE)) / tan(deg_to_rad(rot));
	inter_y_s.y = y + (TILE_SIZE - (y % TILE_SIZE));
	inter_x_e.x = x - (x % TILE_SIZE) + TILE_SIZE;
	inter_x_e.y = y - ((TILE_SIZE - (x % TILE_SIZE))
			* tan(deg_to_rad(rot)));
	inter_x_w.x = x - (x % TILE_SIZE);
	inter_x_w.y = y + ((TILE_SIZE - (TILE_SIZE - (x % TILE_SIZE)))
			* tan(deg_to_rad(rot)));
	if (rot >= 0 && rot <= 90)
		return (check_dir(inter_y_n, inter_x_e, 'NE', rot));
	else if (rot >= 90 && rot <= 180)
		return (check_dir(inter_y_n, inter_x_w, 'NW', rot));
	else if (rot >= 180 && rot <= 270)
		return (check_dir(inter_y_s, inter_x_w, 'SW', rot));
	else if (rot >= 270 && rot <= 360)
		return (check_dir(inter_y_s, inter_x_e, 'SE', rot));
	return (new_collider(new_pos(0, 0, 0), 0, 0));
}
