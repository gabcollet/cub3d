/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:27:00 by sfournie          #+#    #+#             */
/*   Updated: 2022/02/11 12:56:51 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

/*
* Check if the entire map is valid.
*
* This includes :
* 1 player only, enclosed map,
* floor surrounded by floor or walls only
*/
int	parse_valid_map(t_map *map)
{
	int	player_found;
	int	x;
	int	y;

	y = 0;
	x = 0;
	player_found = 0;
	if (!map->tiles || !parse_map_is_enclosed(*map))
		return (parse_error(ERR_WALL));
	while (y < map->height)
	{
		if (!parse_map_pos(*map, x++, y, &player_found))
			return (0);
		if (x == map->width)
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
	int	i;

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
	rows = (char **)ft_calloc(MAP_MAX_SIZE, sizeof(char *));
	if (!rows)
		return (valid);
	while (line && *line && i < MAP_MAX_SIZE)
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
	ft_free_array((void **)rows, ft_free);
	return (valid);
}
