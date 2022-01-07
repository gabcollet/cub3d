/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fousse <fousse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/01/07 01:57:42 by fousse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	parse_wall(t_map map, int x, int y)
{
	char	*tiles;

	tiles = map.tiles;
	if (x != 0 && tiles[x - 1 + y * map.width] != M_WALL && x != 0 && tiles[x - 1 + y * map.width] != M_EMPTY)
		return (0);
	if (x < map.width - 1 && tiles[x + 1 + y * map.width] != M_WALL && x < map.width - 1 && tiles[x + 1 + y * map.width] != M_EMPTY)
		return (0);
	if (y != 0 && tiles[x + (y - 1) * map.width] != M_WALL && y != 0 && tiles[x + (y - 1) * map.width] != M_EMPTY)
		return (0);
	if (y < map.height && tiles[x + (y + 1) * map.width] != M_WALL && y < map.height && tiles[x + (y + 1) * map.width] != M_EMPTY)
		return (0);
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
	if (y < map.height && tiles[x + (y + 1) * map.width] == compare)
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
	else if (map.tiles[x + y * map.width] == M_FLOOR)
	{
		if (!parse_floor(map, x, y, M_EMPTY))
			return (parse_error(ERR_SPACE));
	}
	else if (parse_is_player(map.tiles[x + (y * map.width)]))
	{
		 //to be removed!!
		g_game.player.pos.x = x * TILE_SIZE + (TILE_SIZE / 2);
		g_game.player.pos.y = y * TILE_SIZE + (TILE_SIZE / 2);
		//player_set_pos(x * TILE_SIZE + (TILE_SIZE / 2), y * TILE_SIZE + (TILE_SIZE / 2), 0);
		if (*player_found > 0 || !parse_floor(map, x, y, M_EMPTY))
			return (parse_error(ERR_PLAYER));
		*player_found = 1;
	}
	x++;
}

/*
* Check if the entire map is valid.
*
* This includes :
* 1 player only, enclosed map,
* floor surrounded by floor or walls only
*/
int	parse_valid_map(t_map map)
{
	int	player_found;
	int	x;
	int	y;

	y = 0;
	x = 0;
	player_found = 0;
	if (!map.tiles || !parse_map_is_enclosed(map))
		return (parse_error(ERR_WALL));
	while (y < map.height)
	{
		if (!parse_map_pos(map, x, y, &player_found))
			return (0);
		if (++x == map.width)
		{
			x = 0;
			y++;
		}
	}
	if (player_found == 0)
		return (parse_error(ERR_PLAYER));
	return (1);
}

/*
* Check if the read line is valid.
*
* It will set its length as the longest if needed,
* which is used to determine the map's width
*/
int	parse_valid_map_line(char *line, int *len)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (!parse_valid_map_c(line[i]))
			return (parse_error(ERR_MAPC));
		i++;
	}
	if (i > *len)
		*len = i;
	return (1);
}

/*
* Receive the starting line of a map.
*
* From the line, we'll add every lines that
* follows a basic map format into a char**.
* 
* It then merge it all into map_ptr->tiles.
*/
int	parse_map(char *line, t_map *map_ptr, int fd)
{
	char	**rows;
	int		longest;
	int		i;
	int		valid;

	longest = 0;
	i = 0;
	valid = 0;
	rows = (char **)ft_calloc(2000, sizeof(char *)); // to be changed
	if (!rows)
		return (valid);
	while (line && *line)
	{
		valid = parse_valid_map_line(line, &longest);
		if (!valid)
			break ;
		rows[i++] = ft_strdup(line);
		free(line);
		get_next_line(&line, fd);
	}
	if (valid)
		fill_map(rows, map_ptr, longest, i);
	ft_free_array(rows, ft_free);
	return (valid);
}
