/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 11:00:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/01/12 16:08:20 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	check_inter_x(t_pos inter)
{
	t_map	map;
	int		i_x;
	int		i_y;

	map = g_game.map;
	i_x = (int)inter.x / TILE_SIZE;
	i_y = (int)inter.y / TILE_SIZE;
	if (i_x < 0 || i_y < 0 || i_x >= map.width || i_y >= map.height)
		return (1);
	if (map.tiles[i_x + (i_y * map.width)] == M_WALL)
		return (1);
	if (i_x > 0 && map.tiles[i_x - 1 + (i_y * map.width)] == M_WALL)
		return (1);
	return (0);
}

int	check_inter_y(t_pos inter)
{
	t_map	map;
	int		i_x;
	int		i_y;

	map = g_game.map;
	i_x = (int)inter.x / TILE_SIZE;
	i_y = (int)inter.y / TILE_SIZE;
	if (i_x < 0 || i_y < 0 || i_x >= map.width || i_y >= map.height)
		return (1);
	if (map.tiles[i_x + (i_y * map.width)] == M_WALL)
		return (1);
	if (i_y > 0 && map.tiles[i_x + ((i_y - 1) * map.width)] == M_WALL)
		return (1);
	return (0);
}

t_coll	check_intersections(double x, double y, double rot)
{
	t_pos	inter_y_n;
	t_pos	inter_y_s;
	t_pos	inter_x_e;
	t_pos	inter_x_w;

	inter_y_n.x = x + ((fmod(y, TILE_SIZE)) / tan(deg_to_rad(rot)));
	inter_y_n.y = y - (fmod(y, TILE_SIZE));
	inter_y_s.x = x - (TILE_SIZE - (fmod(y, TILE_SIZE))) / tan(deg_to_rad(rot));
	inter_y_s.y = y + (TILE_SIZE - (fmod(y, TILE_SIZE)));
	inter_x_e.x = x - (fmod(x, TILE_SIZE)) + TILE_SIZE;
	inter_x_e.y = y - ((TILE_SIZE - (fmod(x, TILE_SIZE)))
			* tan(deg_to_rad(rot)));
	inter_x_w.x = x - (fmod(x, TILE_SIZE));
	inter_x_w.y = y + ((TILE_SIZE - (TILE_SIZE - (fmod(x, TILE_SIZE))))
			* tan(deg_to_rad(rot)));
	if (rot >= 0 && rot <= 90)
		return (check_dir(inter_y_n, inter_x_e, NE, rot));
	else if (rot >= 90 && rot <= 180)
		return (check_dir(inter_y_n, inter_x_w, NW, rot));
	else if (rot >= 180 && rot <= 270)
		return (check_dir(inter_y_s, inter_x_w, SW, rot));
	else if (rot >= 270 && rot <= 360)
		return (check_dir(inter_y_s, inter_x_e, SE, rot));
	return (new_collider(new_pos(0, 0, 0), 0, 0));
}
