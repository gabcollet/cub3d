/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/24 18:01:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_wall(t_map map, int x, int y)
{
	char	*t;
	int		w;
	int		h;

	w = map.width;
	h = map.height;
	t = map.tiles;
	if (x != 0 && t[x - 1 + y * w] != M_WALL
		&& x != 0 && t[x - 1 + y * w] != M_EMPTY)
		return (0);
	if (x < w - 1 && t[x + 1 + y * w] != M_WALL
		&& x < w - 1 && t[x + 1 + y * w] != M_EMPTY)
		return (0);
	if (y != 0 && t[x + (y - 1) * w] != M_WALL
		&& y != 0 && t[x + (y - 1) * w] != M_EMPTY)
		return (0);
	if (y < h && t[x + (y + 1) * w] != M_WALL
		&& y < h && t[x + (y + 1) * w] != M_EMPTY)
		return (0);
	return (1);
}

int	parse_door(t_map map, int x, int y)
{
	char		*t;
	int			w;
	int			h;
	int			error;
	static int	count;

	w = map.width;
	h = map.height;
	t = map.tiles;
	error = 0;
	if (x == 0 || y == 0 || x >= w - 1 || y >= h - 1)
		error = ERR_DOOR;
	else if (t[x - 1 + y * w] == M_WALL && t[x + 1 + y * w] == M_WALL)
	{
		if (t[x + (y - 1) * w] == M_FLOOR && t[x + (y + 1) * w] == M_FLOOR)
			place_door(&g_game.doors[count], 0, x, y);
	}
	else if (t[x - 1 + y * w] == M_FLOOR && t[x + 1 + y * w] == M_FLOOR)
	{
		if (t[x + (y - 1) * w] == M_WALL && t[x + (y + 1) * w] == M_WALL)
			place_door(&g_game.doors[count], 270, x, y);
	}
	else
		error = ERR_DOOR_ENC;
	if (error)
		return (parse_error_bonus(error));
	g_game.door_count = ++count;
	return (1);
}

// Check if the tile has any EMPTY around it
int	parse_floor(t_map map, int x, int y, int compare)
{
	char	*tiles;
	tiles = map.tiles;
	if (x != 0 && tiles[x - 1 + y * map.width] == compare)
		return (0);
	if (x < map.width - 1 && tiles[x + 1 + y * map.width] == compare)
		return (0);
	if (y != 0 && tiles[x + (y - 1) * map.width] == compare)
		return (0);
	if (y < map.height - 1 && tiles[x + (y + 1) * map.width] == compare)
		return (0);
	return (1);
}

// Check if the code (WALL, FLOOR, etc.) at (x, y) location is valid.
int	parse_map_pos(t_map map, int x, int y, int *player_found)
{
	if (map.tiles[x + y * map.width] == M_WALL)
	{
		if (parse_wall(map, x, y))
			map.tiles[x + y * map.width] = M_EMPTY;
	}
	if (map.tiles[x + y * map.width] == M_DOOR)
	{
		if (!parse_door(map, x, y))
			return (0);
	}
	else if (map.tiles[x + y * map.width] == M_FLOOR)
	{
		if (!parse_floor(map, x, y, M_EMPTY))
			return (parse_error(ERR_SPACE));
	}
	else if (parse_is_player(map.tiles[x + y * map.width]))
	{
		g_game.player.pos.x = x * TILE_SIZE + (TILE_SIZE / 2);
		g_game.player.pos.y = y * TILE_SIZE + (TILE_SIZE / 2);
		if (*player_found > 0 || !parse_floor(map, x, y, M_EMPTY))
			return (parse_error(ERR_PLAYER));
		*player_found = 1;
	}
	return (1);
}
